/*
 * .Oo DERRICK - A Simple Network Stream Recorder
 * Copyright (C) 2011-2012 Konrad Rieck (konrad@mlsec.org)
 * Derrick is licensed under the new BSD License.
 * --
 * Network functions
 */

#include "config.h"
#include "common.h"
#include "utils.h"
#include "derrick.h"
#include "net.h"
#include "log.h"

/*  External variables */
extern int verbose;
extern int max_tcp_bytes;
extern int merge_tcp_payloads;

/**
 * Init the network monitoring
 * @param device Device 
 * @param dump PCAP file
 * @param pcap PCAP filter
 */
void net_init(char *device, char *dump, char *pcap)
{
    static struct nids_chksum_ctl ctl;

    nids_params.n_tcp_streams = 4096;   /* Streams to track for re-assembly */
    nids_params.n_hosts = 1024; /* Hosts to track for defrag */
    nids_params.scan_num_hosts = 0;     /* Disable portscan detection */

    nids_params.device = device;
    nids_params.filename = dump;
    nids_params.pcap_filter = pcap;

    if (!nids_init())
        fatal("Initialization of libnids failed");

    /* Register callbacks */
    nids_register_udp((void *) net_udp);
    nids_register_tcp((void *) net_tcp);

    /* Disable checksum control */
    ctl.netaddr = 0;
    ctl.mask = 0;
    ctl.action = NIDS_DONT_CHKSUM;
    nids_register_chksum_ctl(&ctl, 1);
}

static void swap_addr(struct tuple4 *addr)
{
    u_short p;
    uint a;

    /* Save source */
    p = addr->source;
    a = addr->saddr;

    /* Swap dest to source */
    addr->source = addr->dest;
    addr->saddr = addr->daddr;

    /* Restore source */
    addr->dest = p;
    addr->daddr = a;
}

/**
 * Return the timestamp of the last packet
 */
double net_time()
{
    return ((double) nids_last_pcap_header->ts.tv_sec) +
        ((double) nids_last_pcap_header->ts.tv_usec) / 1e6;
}

/**
 * Callback for TCP data assembled by LibNIDS
 * @param tcp Pointer to stream struct
 * @param param Additional parameter associated with TCP stream
 */
void net_tcp(struct tcp_stream *tcp, void **param)
{
    struct half_stream *hlf = NULL;
    struct tuple4 addr;

    /* Local copy of address */
    memcpy(&addr, &tcp->addr, sizeof(struct tuple4));

    /* TCP connection established */
    if (tcp->nids_state == NIDS_JUST_EST) {
        /* Enable monitoring of data */
        tcp->client.collect++;
        tcp->server.collect++;

        if (!merge_tcp_payloads)
            log_write(net_time(), "T+", addr, "", 0);
        return;
    }

    /* Disable monitoring if stream too long */
    if (max_tcp_bytes
        && tcp->client.count + tcp->server.count > max_tcp_bytes) {
        /* Disable monitoring */
        tcp->client.collect = 0;
        tcp->server.collect = 0;
    }

    /* New data is available */
    if (tcp->nids_state == NIDS_DATA) {
        /* Skip if payloads should be merged */
        if (merge_tcp_payloads) {
            nids_discard(tcp, 0);
            return;
        }

        /* Check which end has sent data */
        if (tcp->client.count_new) {
            hlf = &tcp->client;
            swap_addr(&addr);
        } else {
            hlf = &tcp->server;
        }

        log_write(net_time(), "T", addr, hlf->data, hlf->count_new);
        return;
    }

    /* TCP connection closed */
    if (tcp->nids_state == NIDS_CLOSE || tcp->nids_state == NIDS_RESET ||
        tcp->nids_state == NIDS_TIMED_OUT) {
        /* Skip if payloads should not be merged */
        if (!merge_tcp_payloads) {
            log_write(net_time(), "T-", addr, "", 0);
            return;
        }

        /* Log merged payloads */
        if (tcp->server.count)
            log_write(net_time(), "T", addr, tcp->server.data,
                      tcp->server.count);
        swap_addr(&addr);
        if (tcp->client.count)
            log_write(net_time(), "T", addr, tcp->client.data,
                      tcp->client.count);
        return;
    }
}

/**
 * Callback for UDP data called by LibNIDS
 * @param addr Address data (2x IP:port)
 * @param buf UDP payload
 * @param len Length of UDP payload
 * @param iph IP header
 */
void net_udp(struct tuple4 *addr, char *buf, int len, struct ip *iph)
{
    log_write(net_time(), "U", *addr, buf, len);
}

/**
 * Exit network stuff
 */
void net_exit()
{
    /* hmm */
}
