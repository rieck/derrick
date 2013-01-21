# .Oo DERRICK - A Simple Network Stream Recorder
# Copyright (C) 2011-2012 Konrad Rieck (konrad@mlsec.org)
    
AUTOMAKE_OPTIONS = foreign
SUBDIRS = src doc contrib .
EXTRA_DIST = README.md COPYING CHANGES bootstrap pedantic
ACLOCAL_AMFLAGS = -I m4

clean-local:
	rm -f *~

CHANGES:
	$(srcdir)/git2changes.py                
        
distclean-local:
	rm -f CHANGES        