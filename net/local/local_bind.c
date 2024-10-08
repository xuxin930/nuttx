/****************************************************************************
 * net/local/local_bind.c
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

#include <nuttx/config.h>

#include <sys/socket.h>
#include <string.h>
#include <assert.h>

#include <nuttx/net/net.h>

#include "local/local.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: psock_local_bind
 *
 * Description:
 *   This function implements the low-level parts of the standard local
 *   bind()operation.
 *
 ****************************************************************************/

int psock_local_bind(FAR struct socket *psock,
                     FAR const struct sockaddr *addr, socklen_t addrlen)
{
  FAR struct local_conn_s *conn = psock->s_conn;
  FAR const struct sockaddr_un *unaddr =
    (FAR const struct sockaddr_un *)addr;
  int index;

  DEBUGASSERT(unaddr->sun_family == AF_LOCAL);

  if (addrlen <= sizeof(sa_family_t) + 1)
    {
      return -EINVAL;
    }

  conn = psock->s_conn;

  /* Check if local address is already in use */

  net_lock();
  if (local_findconn(conn, unaddr) != NULL)
    {
      net_unlock();
      return -EADDRINUSE;
    }

  net_unlock();

  /* Save the address family */

  conn->lc_instance_id = -1;

  /* Now determine the type of the Unix domain socket by comparing the size
   * of the address description.
   */

  if (unaddr->sun_path[0] == '\0')
    {
      /* Zero-length sun_path... This is an abstract Unix domain socket */

      conn->lc_type = LOCAL_TYPE_ABSTRACT;
      index = 1;
    }
  else
    {
      /* This is an normal, pathname Unix domain socket */

      conn->lc_type = LOCAL_TYPE_PATHNAME;
      index = 0;
    }

  strlcpy(conn->lc_path, &unaddr->sun_path[index], sizeof(conn->lc_path));

  conn->lc_state = LOCAL_STATE_BOUND;
  return OK;
}
