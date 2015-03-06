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

#include <iostream>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>

#include "liblttng-profile-base/profiling_timer.h"
#include "liblttng-profile-base/signal_handler.h"

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

// Signal used by LTTng-profile.
const int kSignal = SIGPROF;

bool InstallSignalHandler()
{
  struct sigaction sigact;
  struct sigaction sigact_old;

  memset(&sigact, 0, sizeof(sigact));
  sigact.sa_sigaction = &lttng_profile::SignalHandler;
  sigact.sa_flags = SA_RESTART | SA_SIGINFO;
  int ret = sigaction(kSignal, &sigact, &sigact_old);

  if (ret != 0)
  {
    sigaction(kSignal, &sigact_old, &sigact);
    return false;
  }

  return true;
}

}  // namespace

void StartLttngProfile()
{
  // Use thread-local storage for libunwind caches, in order to avoid locks.
  unw_set_caching_policy(unw_local_addr_space, UNW_CACHE_PER_THREAD);

  // Install the signal handler.
  if (!InstallSignalHandler())
  {
    std::cerr << "LTTng-profile: "
              << "Unable to install a SIGPROF signal handler. "
              << "LTTng-profile will not be enabled." << std::endl;
    return;
  }

  /*
  // Start profiling timer.
  if (!lttng_profile::StartProfilingTimer(kTimerPeriod))
  {
    std::cerr << "LTTng-profile: "
              << "Unable to start profiling timer. "
              << "No CPU profiling events will be generated." << std::endl;
  }
  */

  // Start sched kernel module.
  if (lttngprofile_module_register(kMinSyscallDuration) != 0)
  {
    std::cerr << "LTTng-profile: "
              << "Unable to communicate with the kernel module. "
              << "No stack trace events will be generated on long syscalls."
              << std::endl;
  }
}
