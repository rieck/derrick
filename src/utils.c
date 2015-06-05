/*
 * .Oo DERRICK - A Simple Network Stream Recorder
 * Copyright (C) 2011-2012 Konrad Rieck (konrad@mlsec.org)
 * Derrick is licensed under the new BSD License.
 * --
 * Utility functions
 */

#include "config.h"
#include "common.h"
#include "utils.h"
#include "derrick.h"

/* External variables */
extern dmode_t dmode;

/**
 * Print an error message. See macros in utils.h
 * @param p Prefix string, e.g. "Error"
 * @param f Function name, e.g. __func__ macro
 * @param m Format string
 */
void error_msg(char *p, const char *f, char *m, ...)
{
    va_list ap;
    char s[256] = { " " };

    va_start(ap, m);
    vsnprintf(s, 256, m, ap);
    va_end(ap);

    fprintf(stderr, "%s(%s): %s ", p, f, s);
    if (errno)
        fprintf(stderr, "[%s] ", strerror(errno));
    fprintf(stderr, "\n");
    errno = 0;
}


/**
 * Print a debug message. See macros in utils.h
 * @param f Function name, e.g. __func__ macro
 * @param m Format string
 */
void debug_msg(const char *f, char *m, ...)
{
    va_list ap;
    char s[256] = { " " };

    va_start(ap, m);
    vsnprintf(s, 256, m, ap);
    va_end(ap);

    fprintf(stdout, "DBG[%s]: %s ", f, s);
}

static char *inet_ntoa2(u_int addr)
{
    struct in_addr a;
    a.s_addr = addr;
    return inet_ntoa(a);
}

/**
 * Converts a LibNIDS address tuple to a string.
 * @param addr Address tuple
 * @return static string
 */
char *addr_to_str(struct tuple4 addr)
{
    static char buf[256];
    char *ptr = buf;
    int len = sizeof(buf);

    snprintf(ptr, len, "%s:%d ", inet_ntoa2(addr.saddr), addr.source);
    len -= strlen(ptr);
    ptr += strlen(ptr);
    snprintf(ptr, len, "%s:%d", inet_ntoa2(addr.daddr), addr.dest);

    return buf;
}

/**
 * Converts a Payload to a string
 * @param payl Payload buffer
 * @param len Length of payload
 * @param show Number of bytes to show
 * @return string on heap
 */
char *payl_to_str(char *payl, int len)
{
    int i, j = 0;
    char *buf, hex[4];

    buf = malloc(len * 3 + 1);
    if (!buf) {
        error("Could not allocate memory of %d bytes", len * 3 + 1);
        return "";
    }

    for (i = 0; i < len; i++) {
        unsigned char c = payl[i];

        switch (dmode) {
        case HEX:
            snprintf(hex, 4, " %.2x", c);
            memcpy(buf + j, hex, 3);
            j += 3;
            break;
        case ASCII:
            if (isprint(c) && c != '%') {
                buf[j++] = c;
            } else {
                buf[j++] = '.';
            }
            break;
        default:
        case URLENC:
            if (isprint(c) && c != '%') {
                buf[j++] = c;
            } else {
                snprintf(hex, 4, "%%%.2x", c);
                memcpy(buf + j, hex, 3);
                j += 3;
            }
        }
    }
    buf[j] = 0;

    return buf;
}
