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
#include "lttng-profile/profiling_timer.h"

#include <string.h>
#include <sys/time.h>

namespace lttng_profile
{

bool StartProfilingTimer(long period, ProfilingTimerCallback callback)
{
  // Register a SIGPROF signal handler. 
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_sigaction = callback;
  sa.sa_flags = SA_RESTART | SA_SIGINFO;
  sigemptyset(&sa.sa_mask);
  if (sigaction(SIGPROF, &sa, NULL) != 0)
    return false;

  // Start profiling timer.
  struct itimerval timer;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = period;
  timer.it_value = timer.it_interval;

  if (setitimer(ITIMER_PROF, &timer, NULL) != 0)
    return false;

  return true;
}

}  // namespace lttng_profile
