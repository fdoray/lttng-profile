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
#ifndef LTTNG_PROFILE_MODULE_API_H_
#define LTTNG_PROFILE_MODULE_API_H_

#include <signal.h>

/*
 * lttng-profile module configuration
 */
struct lttngprofile_module_config {
    /* Signal sent to a thread after a long syscall. */
    int signo;
    /* Latency threshold to identify long syscalls. */
    long latency_threshold;
    /* Signal handler. */
    void (*callback)(void* context);
};

/*
 * Test if the lttng-profile module is enabled.
 *
 * Return: 1 if initialized, 0 otherwise
 */
int lttngprofile_module_registered();

/*
 * Register the current process (and all its threads) to the lttng-profile
 * module. If already registered, then it resets the configuration. Open
 * the required file descriptor and install the signal handler.
 *
 * The signal handler may be called before this function returns. Therefore,
 * any required setup must be performed prior to registration.
 *
 * Supported signals are SIGUSR1 and SIGUSR2.
 *
 * @config: pointer to struct lttngprofile configuration
 *
 * Return: 0 in case of success, error code otherwise
 */
int lttngprofile_module_register(
    struct lttngprofile_module_config* config);

/*
 * Unregister the calling process from the lttng-profile module. The
 * previous signal handler is restored.
 *
 * Return: 0 in case of success, error code otherwise
 */
int lttngprofile_module_unregister();

#endif  // LTTNG_PROFILE_MODULE_API_H_
