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
#ifndef LTTNG_PROFILE_PROFILING_TIMER_H_
#define LTTNG_PROFILE_PROFILING_TIMER_H_

#include <signal.h>

namespace lttng_profile
{

typedef void (*ProfilingTimerCallback)(int, siginfo_t*, void *);

bool StartProfilingTimer(long period, ProfilingTimerCallback callback);

}  // namespace lttng_profile

#endif  // LTTNG_PROFILE_PROFILING_TIMER_H_
