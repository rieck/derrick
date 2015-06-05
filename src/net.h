/*
 * .Oo DERRICK - A Simple Network Stream Recorder
 * Copyright (C) 2011-2012 Konrad Rieck (konrad@mlsec.org)
 * Derrick is licensed under the new BSD License.
 * --
 * LibNIDS callback functions
 */

#ifndef NET_H
#define NET_H

#include "derrick.h"

/* Functions */
void net_init(char *, char *, char *);
void net_tcp(struct tcp_stream *ns, void **param);
void net_udp(struct tuple4 *addr, char *buf, int len, struct ip *iph);
void net_exit();
double net_time();

#endif
