#!/bin/bash

sudo dmesg -c > /dev/null

sudo control-addons.sh load

lttng create

lttng enable-event -k sched_ttwu
lttng enable-event -k sched_switch
lttng enable-event -k sched_process_fork
lttng enable-event -k sched_process_exec
lttng enable-event -k sched_process_exit
lttng enable-event -k softirq_entry
lttng enable-event -k softirq_exit
lttng enable-event -k hrtimer_expire_entry
lttng enable-event -k hrtimer_expire_exit
lttng enable-event -k irq_handler_entry
lttng enable-event -k irq_handler_exit
lttng enable-event -k lttng_statedump_end
lttng enable-event -k lttng_statedump_process_state
lttng enable-event -k lttng_statedump_start
lttng enable-event -k --syscall -a
lttng add-context -k -t vtid
lttng add-context -k -t procname

lttng enable-event -u -a
lttng add-context -u -t vtid
lttng add-context -u -t procname

lttng start

# Run the application.
LD_PRELOAD=/usr/local/lib/liblttng-profile.so $@

lttng destroy
