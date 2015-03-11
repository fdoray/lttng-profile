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
#include "liblttng-profile-base/signal_handler.h"

#include <algorithm>
#include <execinfo.h>

#include "liblttng-profile-base/get_monotonic_time.h"
#include "liblttng-profile-base/module_api.h"
#include "liblttng-profile-base/stacktrace.h"
#include "liblttng-profile-base/tp.h"

namespace lttng_profile
{

namespace
{

// Maximum stack size to capture.
const size_t kMaxStackSize = 60;

// Size of the stack string.
const size_t kStackStringSize = 512;

}  // namespace

void SignalHandler(int sig_nr, siginfo_t* info, void* context)
{
  uint64_t start = GetMonotonicTime();

  // Capture the call stack.
  void* stack[kMaxStackSize];
  size_t size = StackTrace(stack, kMaxStackSize, context);

  // Get the function names.
  char** symbols = backtrace_symbols(stack, kMaxStackSize);
  char symbols_string[kStackStringSize];
  int pos = 0;

  for (size_t i = 0; i < size && pos < kStackStringSize; ++i)
  {
    snprintf(symbols_string + pos, kStackStringSize - pos, "%s\n", symbols[i]);
    pos += strlen(symbols[i]) + 1;
  }

  free(symbols);

  // Generate the event.
  uint64_t overhead = GetMonotonicTime() - start;

  if (info->si_code == SI_USER)
  {
    tracepoint(lttng_profile,
               off_cpu_sample,
               symbols_string,
               overhead);

    syscall_tracker_module_stack();
  }
  else
  {
    tracepoint(lttng_profile,
               on_cpu_sample,
               symbols_string,
               overhead);
  }
}

}  // namespace lttng_profile
