AC_INIT([lttng-profile], [1.0.0], [francois.doray@gmail.com])
AC_CANONICAL_TARGET
AC_CANONICAL_HOST
AC_CONFIG_MACRO_DIR([config])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_HEADERS([config.h])

AC_LANG(C++)

# For _GNU_SOURCES
AC_GNU_SOURCE

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
LT_INIT

# Check for LTTng-UST.
AC_CHECK_LIB([lttng-ust], [lttng_probe_register], [],
    [AC_MSG_ERROR([LTTng-UST is not available])])

# Check for libunwind.
AC_CHECK_HEADERS(libunwind.h)
AC_CHECK_LIB(unwind, backtrace, [],
    [AC_MSG_ERROR([libunwind is not available])])

# Checks for header files.
AC_CHECK_HEADERS([errno.h], , [AC_MSG_ERROR([couldn't find header errno.h])])
AC_CHECK_HEADERS([iostream], , [AC_MSG_ERROR([couldn't find header iostream])])
AC_CHECK_HEADERS([signal.h], , [AC_MSG_ERROR([couldn't find header signal.h])])
AC_CHECK_HEADERS([stddef.h], , [AC_MSG_ERROR([couldn't find header stddef.h])])
AC_CHECK_HEADERS([stdio.h], , [AC_MSG_ERROR([couldn't find header stdio.h])])
AC_CHECK_HEADERS([stdlib.h], , [AC_MSG_ERROR([couldn't find header stdlib.h])])
AC_CHECK_HEADERS([string.h], , [AC_MSG_ERROR([couldn't find header string.h])])
AC_CHECK_HEADERS([sys/ioctl.h], , [AC_MSG_ERROR([couldn't find header sys/ioctl.h])])
AC_CHECK_HEADERS([sys/time.h], , [AC_MSG_ERROR([couldn't find header sys/time.h])])

####
####

AC_CONFIG_FILES([
    Makefile \
    include/Makefile \
    liblttng-profile-base/Makefile \
    liblttng-profile/Makefile
])

AC_OUTPUT