AM_CPPFLAGS = -I.. -I../include
AM_CFLAGS = -fno-omit-frame-pointer
AM_CXXFLAGS = -std=c++11 -fno-omit-frame-pointer

lib_LTLIBRARIES = liblttng-profile-base.la

liblttng_profile_base_la_SOURCES = \
    handlers.cc \
    handlers.h \
    lttng_profile.cc \
    memory.h \
    module_abi.h \
    module_api.c \
    module_api.h \
    profiling_timer.cc \
    profiling_timer.h \
    stacktrace.h \
    tp.cc \
    tp.h
liblttng_profile_base_la_LIBADD = \
    -ldl \
    -llttng-ust \
    -lunwind
