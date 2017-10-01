include $(top_srcdir)/Makefile.Common.am

# Initialisation
BUILT_SOURCES      = 
EXTRA_DIST         =
lib_LTLIBRARIES    =
bin_PROGRAMS       =

# ======================================================================================================================
# Definition of base directories
# ----------------------------------------------------------------------------------------------------------------------
vme_includedir = $(includedir)
nobase_vme_include_HEADERS =

# ======================================================================================================================
# clib library
# ----------------------------------------------------------------------------------------------------------------------

# Library
clib_headers =                               \
	cern/ext/vmod.h

nobase_vme_include_HEADERS += $(clib_headers)

clib_sources =                               \
	cern/ext/vmod.c

noinst_LIBRARIES = libvmod.a
#a_AR = $(CXX) -ar -o
libvmod_a_SOURCES = $(clib_sources)

# ======================================================================================================================
# vme library
# ----------------------------------------------------------------------------------------------------------------------
# Library
vme_headers =                   	            \
	cern/vme/SensorState.h    		            \
	cern/vme/Encoder.h    		                \
	cern/vme/SafeQueue.hpp                      \
	cern/vme/Sensor.h                      		\
	cern/vme/Supervisable.h                		\
	cern/vme/VMESensorsManager.h               	\
	cern/vme/XmlEncoder.h

nobase_vme_include_HEADERS += $(vme_headers)

vme_sources =                               	\
	cern/vme/Sensor.cpp                      	\
	cern/vme/VMESensorsManager.cpp              \
	cern/vme/XmlEncoder.cpp

lib_LTLIBRARIES += libvme.la
libvme_la_SOURCES = $(vme_sources)
libvme_la_LDFLAGS = -no-undefined
libvme_la_LIBADD  = libvmod.a