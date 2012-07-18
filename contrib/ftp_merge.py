#!/usr/bin/python
# Dirty script to merge FTP control and data channels
# (c) 2012 Konrad Rieck

import sys
import gzip

# Simple configuration
ftp_port = "21"
# Commands whose output should be merged
ftp_cmds = [ 'LIST' ]

if len(sys.argv) != 2:
    print 'usage: %s: derrick-file' % sys.argv[0]
    sys.exit(0)
    
for line in gzip.open(sys.argv[1]).readlines():
    tokens = line.split(' ')

    # Extract some fields
    mode = tokens[1]
    (saddr, sport) = tokens[2].split(':')
    (daddr, dport) = tokens[3].split(':')

    # Determine command from client
    if dport == ftp_port:
        cmd = tokens[4]
        cmd = cmd.replace('%0a%0d', '')

    # Determine session endpoints
    if sport == ftp_port:
        serv_addr = saddr
        clnt_port = dport
    elif dport == ftp_port:
        serv_addr = daddr
        clnt_port = sport

    # Check for data channel
    data = (sport != ftp_port and dport != ftp_port)

    # Skip start and end of data channel
    if data and (mode == 'T+' or mode == 'T-'):
        continue

    # Merge only selected data into session
    if data and not cmd in ftp_cmds:
        continue

    # Fix remaining communication
    if data:
        if daddr == serv_addr:
            dport = ftp_port
            sport = clnt_port
        elif saddr == serv_addr:
            sport = ftp_port
            dport = clnt_port

    # Print fixed session to stdout
    tokens[2] = '%s:%s' % (saddr, sport)
    tokens[3] = '%s:%s' % (daddr, dport)
    print ' '.join(tokens),
