## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = foreign

includedir = $(prefix)/include/cgreen

include_HEADERS = cgreen.h unit.h assertions.h breadcrumb.h constraint.h messaging.h \
mocks.h parameters.h reporter.h slurp.h vector.h text_reporter.h collector_test_list.h

#EXTRA_DIST = dbi.h.in

install-exec-hook:
	ln -s $(includedir)/cgreen.h $(prefix)/include/cgreen.h

uninstall-hook:
	rm -f $(prefix)/include/cgreen.h
