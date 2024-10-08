/****************************************************************************
 * arch/xtensa/src/esp32/chip_memory.h
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

#ifndef __ARCH_XTENSA_SRC_ESP32_CHIP_MEMORY_H
#define __ARCH_XTENSA_SRC_ESP32_CHIP_MEMORY_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#ifndef __ASSEMBLY__
#include "hardware/esp32_soc.h"
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define XTENSA_INSTUCTION_REGION 0x40000000

/****************************************************************************
 * Inline Functions
 ****************************************************************************/

#ifndef __ASSEMBLY__
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: xtensa_sp_sane
 ****************************************************************************/

static inline bool xtensa_sp_sane(uint32_t sp)
{
  return esp32_sp_dram(sp);
}

/****************************************************************************
 * Name: xtensa_ptr_extram
 ****************************************************************************/

static inline bool xtensa_ptr_exec(const void *p)
{
  return esp32_ptr_exec(p);
}

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_XTENSA_SRC_ESP32_CHIP_MEMORY_H */

