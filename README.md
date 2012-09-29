
Derrick - A Simple Network Stream Recorder
==

Derrick is a simple tool for recording data streams of TCP and UDP traffic.
It shares similarities with other network recorders, such as tcpflow and
wireshark, where it is more advanced than the first and clearly inferior to
the latter.

Derrick has been specifically designed to monitor application-layer
communication.  In contrast to other tools the application data is logged in
a line-based ASCII format.  Common UNIX tools, such as grep, sed & awk, can
be directly applied.  Even replay of recorded communication is straight
forward using netcat.

Derrick supports on-the-fly compression and rotation of log files.  The
payloads of TCP sessions are re-assembled using Libnids and can be merged or
truncated.  UDP payloads are logged as-is.  Details of lower network layers
are omitted.

A shortened example log of Derrick looks like this:

    05.699 T+ 10.100.163.103:58443 91.198.174.233:80 
    05.832 T 10.100.163.103:58445 91.198.174.233:80 GET /en.wikipedia...%0d%0a
    05.931 T 91.198.174.233:80 10.100.163.103:58445 HTTP/1.1 304 Not ...%0d%0a 
    06.227 U 10.100.163.103:53213 134.76.10.46:53 ~%9a%01%00%00%01%00...%00%01 
    19.819 T- 10.100.163.103:58445 91.198.174.233:80 

Dependencies
--
    >= libpcap-1.1.1
    >= libnet-1.1.4
    >= libnids-1.23

Ubuntu packages: libz-dev libpcap-dev libnet1-dev libnids-dev
(Development packages: automake, libtool)  

Compilation & Installation
--

From GIT repository first run

    $ ./bootstrap

From tarball run

    $ ./configure [options]
    $ make
    $ make check
    $ make install

Configuration Options
--
    --prefix=PATH           Set directory prefix for installation

By default Derrick is installed into /usr/local. If you prefer a different
location, use this option to select an installation directory.

    --with-libpcap=DIR      Installation path of libpcap 
    --with-libnet=DIR       Installation path of libnet 
    --with-libnids=DIR      Installation path of libnids 

If the configure script does not automatically detect the libraries and
their headers, these options can be used to provide the respective
installation paths.

Copyright (C) 2011-2012 Konrad Rieck (konrad@mlsec.org)