/****************************************************************************
 * binfmt/libnxflat/libnxflat_read.c
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

#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <nxflat.h>
#include <debug.h>
#include <errno.h>

#include <arpa/inet.h>

#include <nuttx/fs/fs.h>
#include <nuttx/binfmt/nxflat.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#undef NXFLAT_DUMP_READDATA    /* Define to dump all file data read */

/****************************************************************************
 * Private Constant Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: nxflat_dumpreaddata
 ****************************************************************************/

#if defined(NXFLAT_DUMP_READDATA)
static inline void nxflat_dumpreaddata(FAR char *buffer, int buflen)
{
  FAR uint32_t *buf32 = (FAR uint32_t *)buffer;
  int i;
  int j;

  for (i = 0; i < buflen; i += 32)
    {
      syslog(LOG_DEBUG, "%04x:", i);
      for (j = 0; j < 32; j += sizeof(uint32_t))
        {
          syslog(LOG_DEBUG, "  %08x", *buf32++);
        }

      syslog(LOG_DEBUG, "\n");
    }
}
#else
#  define nxflat_dumpreaddata(b,n)
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: nxflat_read
 *
 * Description:
 *   Read 'readsize' bytes from the object file at 'offset'
 *
 * Returned Value:
 *   0 (OK) is returned on success and a negated errno is returned on
 *   failure.
 *
 ****************************************************************************/

int nxflat_read(FAR struct nxflat_loadinfo_s *loadinfo, FAR char *buffer,
                int readsize, int offset)
{
  ssize_t   nbytes;      /* Number of bytes read */
  off_t     rpos;        /* Position returned by lseek */
  FAR char *bufptr;      /* Next buffer location to read into */
  int       bytesleft;   /* Number of bytes of .data left to read */
  int       bytesread;   /* Total number of bytes read */

  binfo("Read %d bytes from offset %d\n", readsize, offset);

  /* Seek to the position in the object file where the initialized
   * data is saved.
   */

  bytesread = 0;
  bufptr    = buffer;
  bytesleft = readsize;
  do
    {
      rpos = file_seek(&loadinfo->file, offset, SEEK_SET);
      if (rpos != offset)
        {
          berr("Failed to seek to position %d: %d\n", offset, (int)rpos);
          return rpos;
        }

      /* Read the file data at offset into the user buffer */

      nbytes = file_read(&loadinfo->file, bufptr, bytesleft);
      if (nbytes < 0)
        {
          if (nbytes != -EINTR)
            {
              berr("Read from offset %d failed: %d\n",
                   offset, (int)nbytes);
              return nbytes;
            }
        }
      else if (nbytes == 0)
        {
          berr("Unexpected end of file\n");
          return -ENODATA;
        }
      else
        {
          bytesread += nbytes;
          bytesleft -= nbytes;
          bufptr    += nbytes;
          offset    += nbytes;
        }
    }
  while (bytesread < readsize);

  nxflat_dumpreaddata(buffer, readsize);
  return OK;
}
