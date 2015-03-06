AM_CPPFLAGS = -I.. -I../include
AM_CFLAGS = -fno-omit-frame-pointer
AM_CXXFLAGS = -fno-omit-frame-pointer

lib_LTLIBRARIES = liblttng-profile.la

liblttng_profile_la_SOURCES = \
    profiler.cc
liblttng_profile_la_LIBADD = \
    -L../liblttng-profile-base/.libs \
    -llttng-profile-base
