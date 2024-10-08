/****************************************************************************
 * libs/libc/obstack/lib_obstack_malloc.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "lib_obstack_malloc.h"
#include <stdlib.h>
#include <nuttx/lib/lib.h>
#include <assert.h>
#include <debug.h>
#include <obstack.h>

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static void default_alloc_failed_handler(void);

/****************************************************************************
 * Public Data
 ****************************************************************************/

void (*obstack_alloc_failed_handler)(void) = default_alloc_failed_handler;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static void default_alloc_failed_handler(void)
{
  lerr("Failed to allocate to grow obstack");
  abort();
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

FAR void *lib_obstack_malloc(size_t size)
{
  FAR void *res;

  res = lib_malloc(size);

  if (res)
      return res;

  obstack_alloc_failed_handler();
  PANIC();
  return NULL;
}

FAR void *lib_obstack_realloc(FAR void *ptr, size_t size)
{
  FAR void *res;

  res = lib_realloc(ptr, size);

  if (res)
      return res;

  obstack_alloc_failed_handler();
  PANIC();
  return NULL;
}
