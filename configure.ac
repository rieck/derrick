AC_INIT([derrick], [0.3], [konrad@mlsec.org])
AM_INIT_AUTOMAKE
AC_PREFIX_DEFAULT("/usr/local")
AM_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

echo
echo " .Oo DERRICK - A Simple Network Stream Recorder"
echo " Copyright (C) 2011-2012 Konrad Rieck (konrad@mlsec.org)"
echo

# Check for important programs
AC_PROG_CC
AC_PROG_LD
AC_PROG_INSTALL

# Libtool stuff
AC_PROG_LIBTOOL

# Set GCC and C99 flags if present
if test "$GCC" = "yes" ; then
   CFLAGS="$CFLAGS -std=c99 -D_GNU_SOURCE -Wall -fPIC"
fi

# libz
AC_CHECK_HEADERS([zlib.h], HEADER_LIBZ="yes")
AC_CHECK_LIB([z], gzopen, LIBRARY_LIBZ="yes")
if test "x$LIBRARY_LIBZ" != "x" && test "x$HEADER_LIBZ" != "x" ; then
    LIBS="-lz $LIBS"
else
    AC_MSG_ERROR([The library libz is required for compilation])
fi

# libpcap
AC_ARG_WITH(libpcap, 
   AS_HELP_STRING([--with-libpcap=DIR], [Installation path of libpcap]),
                  [with_libpcap="$withval"],[with_libpcap=no]
)
if test "$with_libpcap" != "no"; then
    CFLAGS="$CFLAGS -I${with_libpcap}/include"
    CPPFLAGS="$CPPFLAGS -I${with_libpcap}/include"
    LIBS="$LIBS -L${with_libpcap}/lib"
fi
AC_CHECK_HEADERS([pcap.h], HEADER_LIBPCAP="yes")
AC_CHECK_LIB([pcap], pcap_open_live, LIBRARY_LIBPCAP="yes")
if test "x$LIBRARY_LIBPCAP" != "x" && test "x$HEADER_LIBPCAP" != "x" ; then
    LIBS="-lpcap $LIBS"
else
    AC_MSG_ERROR([The library libpcap is required for compilation])
fi

# libnet
AC_ARG_WITH(libnet, 
   AS_HELP_STRING([--with-libnet=DIR], [Installation path of libnet]),
                  [with_libnet="$withval"],[with_libnet=no]
)
if test "$with_libnet" != "no"; then
    CFLAGS="$CFLAGS -I${with_libnet}/include"
    CPPFLAGS="$CPPFLAGS -I${with_libnet}/include"
    LIBS="$LIBS -L${with_libnet}/lib"
fi
AC_CHECK_HEADERS([libnet.h], HEADER_LIBNET="yes")
AC_CHECK_LIB([net], libnet_build_tcp, LIBRARY_LIBNET="yes")
if test "x$LIBRARY_LIBNET" != "x" && test "x$HEADER_LIBNET" != "x" ; then
    LIBS="-lnet $LIBS"
else
    AC_MSG_ERROR([The library libnet is required for compilation])
fi

# libnids
AC_ARG_WITH(libnids, 
   AS_HELP_STRING([--with-libnids=DIR], [Installation path of libnids]),
                  [with_libnids="$withval"],[with_libnids=no]
)
if test "$with_libnids" != "no"; then
    CFLAGS="$CFLAGS -I${with_libnids}/include"
    CPPFLAGS="$CPPFLAGS -I${with_libnids}/include"
    LIBS="$LIBS -L${with_libnids}/lib"
fi
AC_CHECK_HEADERS([nids.h], HEADER_LIBNIDS="yes")
AC_CHECK_LIB([nids], nids_init, LIBRARY_LIBNIDS="yes")
if test "x$LIBRARY_LIBNIDS" != "x" && test "x$HEADER_LIBNIDS" != "x" ; then
    LIBS="-lnids $LIBS"
else
    AC_MSG_ERROR([The library libnids is required for compilation])
fi

# Check headers
AC_CHECK_HEADERS([getopt.h string.h strings.h stdarg.h errno.h])
AC_CHECK_HEADERS([uthash.h uthash/uthash.h], HEADER_UTHASH="yes")

AC_SUBST([AM_CPPFLAGS])
AC_CONFIG_FILES([ 
   Makefile \
   src/Makefile \
   doc/Makefile \
   contrib/Makefile \
])
AC_OUTPUT
