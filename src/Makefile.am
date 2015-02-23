AM_CPPFLAGS = -I..
AM_CXXFLAGS = -std=c++11 -fno-omit-frame-pointer

lib_LTLIBRARIES = liblttng-profile.la

liblttng_profile_la_SOURCES = \
    lttng-profile/handlers.cc \
    lttng-profile/handlers.h \
    lttng-profile/memory.h \
    lttng-profile/module_abi.h \
    lttng-profile/module_api.c \
    lttng-profile/module_api.h \
    lttng-profile/profiler.cc \
    lttng-profile/profiler.h \
    lttng-profile/profiling_timer.cc \
    lttng-profile/profiling_timer.h \
    lttng-profile/stacktrace.h \
    lttng-profile/tp.cc \
    lttng-profile/tp.h
liblttng_profile_la_LIBADD = \
    -ldl \
    -llttng-ust \
    -lunwind
