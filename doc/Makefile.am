# .Oo DERRICK - A Simple Network Stream Recorder
# Copyright (C) 2011-2012 Konrad Rieck (konrad@mlsec.org)

man1_MANS = derrick.man 

EXTRA_DIST = derrick.pod doxygen.cfg

derrick.man: derrick.pod
	pod2man -c "User Manual" -s 1 -r "derrick $(VERSION)" $< > $@

distclean-local:
	rm -f derrick.man
		
dist-hook: distclean-local derrick.man
