lib_LTLIBRARIES = libopenosc.la
if HAS_SAFEC
libopenosc_la_SOURCES = openosc_map.c openosc_support.c openosc_package_info.c openosc_support_priv.h openosc_common.h openosc_fortify_map.c openosc_safec_map.c
else
libopenosc_la_SOURCES = openosc_map.c openosc_support.c openosc_package_info.c openosc_support_priv.h openosc_common.h openosc_fortify_map.c
endif
libopenosc_la_CFLAGS = $(OPENOSC_CFLAGS)
libopenosc_la_LDFLAGS = -version-info $(LT_VERSION_NUMBER) --allow-shlib-undefined
include_HEADERS = $(top_srcdir)/include/*.h

install-exec-hook:
	cd $(DESTDIR)$(libdir) && rm $(lib_LTLIBRARIES)

uninstall-local:
	cd $(DESTDIR)$(libdir) && rm libopenosc.a libopenosc.so*
