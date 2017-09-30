include $(top_srcdir)/Makefile.Common.am

# ======================================================================================================================
# Tests program
# ----------------------------------------------------------------------------------------------------------------------
# TESTS -- Programs run automatically by "make check"
# check_PROGRAMS -- Programs built by "make check" but not necessarily run
TESTS = 
check_PROGRAMS = 

# ==== Cern Challange Test
check_PROGRAMS += cern_vme_test
TESTS += $(check_PROGRAMS)
EXTRA_DIST = $(TESTS)

cern_vme_test_SOURCES =	 							\
	main.cpp										\
	cern/VmeTest.cpp

cern_vme_test_LDFLAGS =                             \
	-L/opt/local/lib

cern_vme_test_LDADD =                               \
	@top_builddir@/src/libvme.la					\
	$(BOOST_SYSTEM_LIB)
