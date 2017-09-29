include $(top_srcdir)/Makefile.Common.am
		 
# ======================================================================================================================
# Tests program
# ----------------------------------------------------------------------------------------------------------------------
# TESTS -- Programs run automatically by "make check"
# check_PROGRAMS -- Programs built by "make check" but not necessarily run
TESTS = 
check_PROGRAMS = 

# ==== Decoder Encoder Test
TESTS += cern_vme_test
check_PROGRAMS += cern_vme_test
cern_vme_test_SOURCES =	 							\
	main.cpp										\
	cern/VmeTest.cpp

cern_vme_test_LDADD =                               \
	@top_builddir@/src/libcern_vme.la
