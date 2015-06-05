/*
 * .Oo DERRICK - A Simple Network Stream Recorder
 * Copyright (C) 2011-2012 Konrad Rieck (konrad@mlsec.org)
 * Derrick is licensed under the new BSD License.
 * --
 * Compressed log format
 */

#ifndef LOG_H
#define LOG_H

#define SYNC_INTERVAL   512

void log_open(char *);
void log_write(double, char *, struct tuple4, char *, int);
void log_close();


#endif
