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
#include <lttng_profile.h>

#include <atomic>
#include <iostream>
#include <signal.h>
#include <stddef.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>

#include "liblttng-profile-base/handlers.h"
#include "liblttng-profile-base/profiling_timer.h"

extern "C" {
#include "liblttng-profile-base/module_api.h"
}

namespace
{

// Profiling timer period (microseconds).
const long kTimerPeriod = 1000;  // 1 ms

// Minimum duration that a thread must spend in a system call in order to
// generate an off_cpu_sample event (nanoseconds).
const long kMinSyscallDuration = 100000; // 0.1 ms

}  // namespace

void StartLttngProfile()
{
  // Use thread-local storage for libunwind caches, in order to avoid locks.
  unw_set_caching_policy(unw_local_addr_space, UNW_CACHE_PER_THREAD);

  // Start profiling timer.
  if (!lttng_profile::StartProfilingTimer(
          kTimerPeriod, &lttng_profile::OnCpuHandler))
  {
    std::cerr << "LTTng-profile: "
              << "Unable to start profiling timer. "
              << "No profiling events will be generated." << std::endl;
  }

  // Start sched kernel module.
  lttngprofile_module_config config;
  config.signo = SIGUSR1;
  config.latency_threshold = kMinSyscallDuration;
  config.callback = &lttng_profile::OffCpuHandler;

  if (lttngprofile_module_register(&config) != 0)
  {
    std::cerr << "LTTng-profile: "
              << "Unable to communicate with the kernel module. "
              << "No stack trace events will be generated on long syscalls."
              << std::endl;
  }
}
