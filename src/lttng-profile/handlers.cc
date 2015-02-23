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
#include "lttng-profile/handlers.h"

#include <atomic>

#include "lttng-profile/stacktrace.h"
#include "lttng-profile/time.h"
#include "lttng-profile/tp.h"

namespace lttng_profile
{

namespace
{

// Maximum stack size to capture.
const size_t kMaxStackSize = 60;

// Indicates whether we are in a signal handler.
thread_local std::atomic_bool is_handling_signal(false);

bool CanExecuteHandler()
{
  bool expected = false;
  return is_handling_signal.compare_exchange_strong(
      expected, true,
      std::memory_order_relaxed,
      std::memory_order_relaxed);
}

void DidExecuteHandler()
{
  is_handling_signal.store(false, std::memory_order_relaxed);
}

}  // namespace

void OnCpuHandler(int sig_nr, siginfo_t* info, void* context)
{
  if (!CanExecuteHandler())
    return;

  uint64_t start = GetMonotonicTime();

  void* buffer[kMaxStackSize];
  size_t size = StackTrace(buffer, kMaxStackSize, context);

  uint64_t overhead = GetMonotonicTime() - start;

  tracepoint(lttng_profile,
             on_cpu_sample,
             size,
             buffer,
             overhead);

  DidExecuteHandler();
}

void OffCpuHandler(void* context)
{
  if (!CanExecuteHandler())
    return;

  uint64_t start = GetMonotonicTime();

  void* buffer[kMaxStackSize];
  size_t size = StackTrace(buffer, kMaxStackSize, context);

  uint64_t overhead = GetMonotonicTime() - start;

  tracepoint(lttng_profile,
             off_cpu_sample,
             size,
             buffer,
             overhead);

  DidExecuteHandler();
}

}  // namespace lttng_profile
