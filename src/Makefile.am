# preamble
NULL =
BUILT_SOURCES =
CLEANFILES =
EXTRA_DIST =
DISTCLEANFILES =
lib_LTLIBRARIES =
DIST_SUBDIRS = . tests bench

# always build this directory before building the tests suite
SUBDIRS = . tests

if BUILD_BENCHMARKS
# conditionally recurse only if we build the benchmarks suite
SUBDIRS += bench
endif

# source
source_h = \
	graphene-macros.h \
	graphene-matrix.h \
	graphene-point.h \
	graphene-point3d.h \
	graphene-quad.h \
	graphene-quaternion.h \
	graphene-rect.h \
	graphene-vec2.h \
	graphene-vec3.h \
	graphene-vec4.h \
	graphene-types.h \
	graphene-version-macros.h \
	$(NULL)
source_c = \
	graphene-matrix.c \
	graphene-point.c \
	graphene-point3d.c \
	graphene-quad.c \
	graphene-quaternion.c \
	graphene-rect.c \
	graphene-size.c \
	graphene-vectors.c \
	$(NULL)

source_h_priv = \
	graphene-line-segment.h \
	graphene-simd4f.h \
	graphene-simd4f-common.h \
	graphene-simd4f-gcc.h \
	graphene-simd4f-neon.h \
	graphene-simd4f-scalar.h \
	graphene-simd4f-sse.h \
	graphene-simd4x4f.h \
	graphene-simd4x4f-common.h \
	graphene-simd4x4f-gcc.h \
	graphene-simd4x4f-neon.h \
	graphene-simd4x4f-scalar.h \
	graphene-simd4x4f-sse.h \
	graphene-vectors-private.h \
	$(NULL)
source_c_priv =

if BUILD_GOBJECT
source_h += graphene-gobject.h
source_c += graphene-gobject.c
endif

# config header
DISTCLEANFILES += graphene-config-stamp graphene-config.h
BUILT_SOURCES += graphene-config-stamp
graphene-config-stamp: ../config.status
	$(AM_V_GEN) cd $(top_builddir) && \
	  $(SHELL) ./config.status src/graphene-config.h
	@touch graphene-config-stamp

# version header
DISTCLEANFILES += graphene-version.h
EXTRA_DIST += graphene-version.h.in

shared_cflags = $(GRAPHENE_CFLAGS) $(MAINTAINER_CFLAGS)
shared_libadd = $(GRAPHENE_LIBS)

if BUILD_WITH_SSE2
shared_cflags += $(SSE2_CFLAGS)
shared_libadd += $(SSE2_LDFLAGS)
endif

if BUILD_WITH_ARM_NEON
shared_cflags += $(NEON_CFLAGS)
endif

# main library
libgraphene_1_0_la_CPPFLAGS = \
	-DGRAPHENE_COMPILATION=1 \
	-DG_LOG_DOMAIN=\"Graphene\" \
	-I$(top_srcdir)/src \
	-I$(top_builddir)/src \
	$(GRAPHENE_DEBUG_CFLAGS)
libgraphene_1_0_la_CFLAGS = $(shared_cflags)
libgraphene_1_0_la_LIBADD = $(shared_libadd)
libgraphene_1_0_la_LDFLAGS = $(GRAPHENE_LDFLAGS) -export-dynamic
libgraphene_1_0_la_SOURCES = $(source_h) $(source_h_priv) $(source_c) $(source_c_priv) $(BUILT_SOURCES)

lib_LTLIBRARIES += libgraphene-1.0.la

# headers
grapheneincludedir = $(includedir)/graphene-1.0
grapheneinclude_HEADERS = $(source_h) graphene.h
nodist_grapheneinclude_HEADERS = \
	$(top_builddir)/src/graphene-config.h \
	$(top_builddir)/src/graphene-version.h \
	$(NULL)

# pkg-config files
graphene-1.0.pc: graphene.pc
	$(AM_V_GEN)cp -f $< $@

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = graphene-1.0.pc
CLEANFILES += graphene-1.0.pc
EXTRA_DIST += graphene.pc.in

if BUILD_GOBJECT
graphene-gobject-1.0.pc: graphene.pc
	$(AM_V_GEN)cp -f $< $@

pkgconfig_DATA += graphene-gobject-1.0.pc
CLEANFILES += graphene-gobject-1.0.pc
endif
