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
#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER lttng_profile

#undef TRACEPOINT_INCLUDE_FILE
#define TRACEPOINT_INCLUDE_FILE liblttng-profile-base/tp.h

#if !defined(LTTNG_PROFILE_TP_H_) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define LTTNG_PROFILE_TP_H_

#include <lttng/tracepoint.h>
#include <pthread.h>
#include <stdint.h>

TRACEPOINT_EVENT(
    lttng_profile,
    on_cpu_sample,
    TP_ARGS(size_t, size,
            void*, stack,
            uint64_t, overhead),
    TP_FIELDS(
        ctf_sequence(void*, stack, stack, size_t, size)
        ctf_integer(uint64_t, overhead, overhead)
    )
)

TRACEPOINT_LOGLEVEL(lttng_profile, on_cpu_sample,
    TRACE_DEBUG_FUNCTION)

TRACEPOINT_EVENT(
    lttng_profile,
    off_cpu_sample,
    TP_ARGS(size_t, size,
            void*, stack,
            uint64_t, overhead),
    TP_FIELDS(
        ctf_sequence(void*, stack, stack, size_t, size)
        ctf_integer(uint64_t, overhead, overhead)
    )
)

TRACEPOINT_LOGLEVEL(lttng_profile, off_cpu_sample,
    TRACE_DEBUG_FUNCTION)

#endif /* LTTNG_PROFILE_TP_H_ */
#include <lttng/tracepoint-event.h>
