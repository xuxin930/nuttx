/****************************************************************************
 * arch/x86_64/src/intel64/intel64_initialstate.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <string.h>

#include <nuttx/arch.h>
#include <arch/arch.h>

#ifdef CONFIG_SCHED_THREAD_LOCAL
#  include <nuttx/tls.h>
#endif

#include "x86_64_internal.h"
#include "sched/sched.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#if XCPTCONTEXT_SIZE % XCPTCONTEXT_ALIGN != 0
#  error XCPTCONTEXT_SIZE must be aligned to XCPTCONTEXT_ALIGN !
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_initial_state
 *
 * Description:
 *   A new thread is being started and a new TCB has been created. This
 *   function is called to initialize the processor specific portions of the
 *   new TCB.
 *
 *   This function must setup the intial architecture registers and/or stack
 *   so that execution will begin at tcb->start on the next context switch.
 *
 ****************************************************************************/

void up_initial_state(struct tcb_s *tcb)
{
  struct xcptcontext *xcp = &tcb->xcp;

  /* Initialize the idle thread stack */

  if (tcb->pid == IDLE_PROCESS_ID)
    {
      char *stack_ptr = (char *)(g_idle_topstack[0] -
                                 CONFIG_IDLETHREAD_STACKSIZE);
      tcb->stack_alloc_ptr = stack_ptr;
      tcb->stack_base_ptr  = stack_ptr;
      tcb->adj_stack_size  = CONFIG_IDLETHREAD_STACKSIZE;
#ifdef CONFIG_STACK_COLORATION
      /* If stack debug is enabled, then fill the stack with a
       * recognizable value that we can use later to test for high
       * water marks.
       */

      x86_64_stack_color(tcb->stack_alloc_ptr, 0);
#endif /* CONFIG_STACK_COLORATION */
    }

  /* Initialize the initial exception register context structure */

  memset(xcp, 0, sizeof(struct xcptcontext));

  /* Allocate area for XCPTCONTEXT */

  xcp->regs = (uint64_t *)XCP_ALIGN_DOWN((uintptr_t)tcb->stack_base_ptr +
                                         tcb->adj_stack_size -
                                         XCPTCONTEXT_SIZE);

  /* Reset the xcp registers */

  memset(xcp->regs, 0, XCPTCONTEXT_SIZE);

#ifndef CONFIG_ARCH_X86_64_HAVE_XSAVE
  /* Set the FCW to 1f80 */

  xcp->regs[1]          = (uint64_t)0x0000037f00000000;

  /* Set the MXCSR to 1f80 */

  xcp->regs[3]          = (uint64_t)0x0000000000001f80;
#else
  /* Initialize XSAVE region with a valid state */

  __asm__ volatile("xsave %0"
                   : "=m" (*xcp->regs)
                   : "a" (XSAVE_STATE_COMPONENTS), "d" (0)
                   : "memory");
#endif

  /* Save the initial stack pointer... the value of the stackpointer before
   * the "interrupt occurs."
   */

  xcp->regs[REG_RSP]    = (uint64_t)xcp->regs - 8;
  xcp->regs[REG_RBP]    = 0;

  /* Save the task entry point */

  xcp->regs[REG_RIP]    = (uint64_t)tcb->start;

  /* Set up the segment registers... assume the same segment as the caller.
   * That is not a good assumption in the long run.
   */

  xcp->regs[REG_DS]     = up_getds();
  xcp->regs[REG_CS]     = up_getcs();
  xcp->regs[REG_SS]     = up_getss();
  xcp->regs[REG_ES]     = up_getes();

/* FS used by for TLS
 * used by some libc for TLS and segment reference
 */

#ifdef CONFIG_SCHED_THREAD_LOCAL
  xcp->regs[REG_FS]     = (uintptr_t)tcb->stack_alloc_ptr
                          + sizeof(struct tls_info_s)
                          + (_END_TBSS - _START_TDATA);

  *(uint64_t *)(xcp->regs[REG_FS]) = xcp->regs[REG_FS];

  write_fsbase(xcp->regs[REG_FS]);
#else
  xcp->regs[REG_FS]     = 0;
#endif

  /* GS used for CPU private data */

  xcp->regs[REG_GS]     = 0;

  /* Set supervisor- or user-mode, depending on how NuttX is configured and
   * what kind of thread is being started.  Disable FIQs in any event
   *
   * If the kernel build is not selected, then all threads run in
   * supervisor-mode.
   */

#ifdef CONFIG_BUILD_KERNEL
#  error "Missing logic for the CONFIG_BUILD_KERNEL build"
#endif

  /* Enable or disable interrupts, based on user configuration.  If the IF
   * bit is set, maskable interrupts will be enabled.
   */

#ifndef CONFIG_SUPPRESS_INTERRUPTS
  xcp->regs[REG_RFLAGS] = X86_64_RFLAGS_IF;
#endif
}

