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
 */
#ifndef LTTNG_PROFILE_STACKTRACE_H_
#define LTTNG_PROFILE_STACKTRACE_H_

#include <stddef.h>
#include <stdio.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>

namespace lttng_profile
{

inline size_t StackTrace(void** stack, size_t size, void* context)
{
  /*
  unw_context_t unwind_context =
    *(static_cast<unw_context_t *>(const_cast<void *>(context)));

  unw_cursor_t cursor;
  int ret = unw_init_local(&cursor, &unwind_context);
  if (ret != 0)
    return 0;

  size_t i = 0;
  for (; i < size; ++i)
  {
    void* ip = NULL;
    if (unw_get_reg(&cursor, UNW_REG_IP, (unw_word_t*)&ip) < 0)
      break;

    stack[i] = ip;
    if (unw_step(&cursor) <= 0)
      break;
  }

  return i;
  */
  return unw_backtrace(stack, size);
}

}  // namespace lttng_profile

#endif  // LTTNG_PROFILE_STACKTRACE_H_
