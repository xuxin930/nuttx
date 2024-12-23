/****************************************************************************
 * arch/risc-v/src/litex/hardware/litex_clint.h
 *
 * SPDX-License-Identifier: Apache-2.0
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

#ifndef __ARCH_RISCV_SRC_LITEX_HARDWARE_LITEX_CLINT_H
#define __ARCH_RISCV_SRC_LITEX_HARDWARE_LITEX_CLINT_H

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#ifdef CONFIG_LITEX_CORE_VEXRISCV_SMP

#define LITEX_CLINT_MSIP      (LITEX_CLINT_BASE + 0x0000)
#define LITEX_CLINT_MTIMECMP  (LITEX_CLINT_BASE + 0x4000)
#define LITEX_CLINT_MTIME     (LITEX_CLINT_BASE + 0xbff8)

#else

#define LITEX_CLINT_LATCH      (LITEX_CPUTIMER_BASE)
#define LITEX_CLINT_MTIME      (LITEX_CPUTIMER_BASE + 0x04)
#define LITEX_CLINT_MTIMECMP   (LITEX_CPUTIMER_BASE + 0x0C)

#endif /* CONFIG_LITEX_CORE_VEXRISCV_SMP */

#endif /* __ARCH_RISCV_SRC_LITEX_HARDWARE_LITEX_CLINT_H */
