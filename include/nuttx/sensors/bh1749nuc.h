/****************************************************************************
 * include/nuttx/sensors/bh1749nuc.h
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

#ifndef __INCLUDE_NUTTX_SENSORS_BH1749NUC_H
#define __INCLUDE_NUTTX_SENSORS_BH1749NUC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <nuttx/i2c/i2c_master.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

struct bh1749nuc_data_s
{
  uint16_t red;
  uint16_t green;
  uint16_t blue;
  uint16_t ir;
  uint16_t green2;
};

struct bh1749nuc_config_s
{
  FAR struct i2c_master_s *i2c;
  uint8_t addr;
};

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

/****************************************************************************
 * Name: bh1749nuc_register
 *
 * Description:
 *   Register the BH1749NUC character device as 'devpath'
 *
 * Input Parameters:
 *   devpath - The full path to the driver to register. E.g., "/dev/color0"
 *   i2c     - An instance of the I2C interface to use to communicate with
 *             BH1749NUC
 *   addr    - I2C address
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

#ifndef CONFIG_SENSORS_BH1749NUC_UORB
int bh1749nuc_register(FAR const char *devpath, FAR struct i2c_master_s *i2c,
                       uint8_t addr);
#else
int bh1749nuc_register_uorb(int devno,
                            FAR struct bh1749nuc_config_s *config);
#endif

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __INCLUDE_NUTTX_SENSORS_BH1749NUC_H */
