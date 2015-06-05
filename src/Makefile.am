# .Oo DERRICK - A Simple Network Stream Recorder
# Copyright (C) 2011-2012 Konrad Rieck (konrad@mlsec.org)

bin_PROGRAMS		= derrick
derrick_SOURCES		= derrick.c derrick.h utils.c utils.h \
			  net.c net.h log.c log.h common.h \
			  common.h

beautify:
	gindent -i4 -npsl -di0 -br -d0 -cli0 -npcs -ce -nfc1 -nut \
		-T FILE *.c *.h
