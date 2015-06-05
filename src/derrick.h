/*
 * .Oo DERRICK - A Simple Network Stream Recorder
 * Copyright (C) 2011-2012 Konrad Rieck (konrad@mlsec.org)
 * Derrick is licensed under the new BSD License.
 * --
 * Main header
 */

#ifndef DERRICK_H
#define DERRICK_H

#define MAX_TCP_BYTES       100000
#define MAX_LOG_LINES       100000
#define PCAP_FILTER         "tcp or udp"

/* Display mode */
typedef enum {
   URLENC, ASCII, HEX, 
} dmode_t;

#endif
