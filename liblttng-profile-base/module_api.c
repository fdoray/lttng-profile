/*
 * Copyright (C) 2015 Francois Doray <francois.doray@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; only
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Inspired from https://github.com/giraldeau/perfuser, by Francis Giraldeau.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>

#include "liblttng-profile-base/module_api.h"
#include "liblttng-profile-base/module_abi.h"
#include "liblttng-profile-base/memory.h"

struct syscall_tracker_module_state {
  int registered;
  FILE* fd;
};

static struct syscall_tracker_module_state* state = NULL;

static int syscall_tracker_module_ioctl(int cmd)
{
  struct syscall_tracker_module_msg info;

  if (!(state && state->fd))
    return -1;
  info.cmd = cmd;
  return ioctl(state->fd->_fileno, SYSCALLS_TRACKER_IOCTL, &info);
}

/*
 * API functions
 */
int syscall_tracker_module_registered()
{
  return (state && state->registered);
}

int syscall_tracker_module_register(long latency_threshold)
{
  int ret = 0;

  /* if initialized, then reset configuration */
  if (syscall_tracker_module_registered()) {
    syscall_tracker_module_unregister();
  }
  state = calloc(1, sizeof(*state));
  if (!state) {
      return -ENOMEM;
  }

  /* open ioctl fd */
  state->fd = fopen(SYSCALL_TRACKER_PATH, "rw");
  if (!state->fd) {
    ret = -ENOENT;
    goto error_fd;
  }

  /* install signal handler before registration */
  ret = syscall_tracker_module_ioctl(
      SYSCALL_TRACKER_MODULE_REGISTER);
  if (ret != 0)
    goto error_ioctl;
  state->registered = 1;
  return ret;

error_ioctl:
  fclose(state->fd);
error_fd:
  FREE(state);
  return ret;
}

int syscall_tracker_module_unregister()
{
  int ret = 0;
  if (syscall_tracker_module_registered()) {
    ret = syscall_tracker_module_ioctl(
        SYSCALL_TRACKER_MODULE_UNREGISTER);
    fclose(state->fd);
    FREE(state);
  }
  return ret;
}
