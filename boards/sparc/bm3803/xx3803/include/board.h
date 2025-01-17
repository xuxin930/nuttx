/****************************************************************************
 * boards/sparc/bm3803/xx3803/include/board.h
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

#ifndef __BOARDS_SPARC_BM3803_XX3803_INCLUDE_BOARD_H
#define __BOARDS_SPARC_BM3803_XX3803_INCLUDE_BOARD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-Processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

/* Clocking *****************************************************************/

/* Assume default CLKDIV8 fuse setting is overridden to CLKDIV1 */

#define BOARD_XTAL_FREQ        60000000         /* 60MHz crystal */
#define BOARD_CPU_CLOCK        BOARD_XTAL_FREQ  /* F_CPU = 60MHz */
#define CHIP_NUARTS            3

#define BOARD_TIM1_FREQUENCY   BOARD_CPU_CLOCK
#define BOARD_TIM2_FREQUENCY   BOARD_CPU_CLOCK

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Inline Functions
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __BOARDS_SPARC_BM3803_XX3803_INCLUDE_BOARD_H */
