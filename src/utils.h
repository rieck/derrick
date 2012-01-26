/*
 * .Oo DERRICK - A Simple Network Stream Recorder
 * Copyright (C) 2011-2012 Konrad Rieck (konrad@mlsec.org)
 * Derrick is licensed under the new BSD License.
 * --
 * Utility functions
 */

#ifndef UTILS_H
#define UTILS_H

#include "common.h"

/* Debug message */
#if DEBUG
#ifndef debug
#define debug(...)      {debug_msg(__func__, __VA_ARGS__);}
#endif
#else
#define debug(...)      {}
#endif

/* Fatal message */
#ifndef fatal
#define fatal(...)     {error_msg("Error", __func__, __VA_ARGS__); \
                        exit(EXIT_FAILURE);}
#endif
/* Error message */
#ifndef error
#define error(...)     {error_msg("Error", __func__, __VA_ARGS__);}
#endif
/* Warning message */
#ifndef warning
#define warning(...)   {error_msg("Warning", __func__, __VA_ARGS__);}
#endif

/* Utility functions */
void error_msg(char *, const char *, char *, ...);
void debug_msg(const char *, char *, ...);
char *addr_to_str(struct tuple4 addr);
char *payl_to_str(char *buf, int len);

#endif
