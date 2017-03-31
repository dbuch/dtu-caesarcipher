bin_PROGRAMS = dtu-caesarcipher

resources_file = $(top_builddir)/data/dtu-caesarcipher.gresources.xml
BUILT_SOURCES = resources.c

resources.c: $(resources_file) $(shell $(GLIB_COMPILE_RESOURCES) --generate-dependencies --sourcedir=$(top_srcdir)/data/ $(top_srcdir)/data/dtu-caesarcipher.gresources.xml)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(top_srcdir)/data/ --generate-source $<

dtu_caesarcipher_SOURCES =  \
	$(BUILT_SOURCES)    \
	dtu-caesarcipher.c \
	dtu-caesarcipher.h \
	dtu-caesarcipher-crackbutton.c \
	dtu-caesarcipher-crackbutton.h \
	dtu-caesarcipher-language.c \
	dtu-caesarcipher-language.h \
	dtu-caesarcipher-app.c \
	dtu-caesarcipher-app.h \
	dtu-caesarcipher-app-win.c \
	dtu-caesarcipher-app-win.h \
	main.c
dtu_caesarcipher_CFLAGS = $(DTU_CAESARCIPHER_CFLAGS)

dtu_caesarcipher_LDADD = $(DTU_CAESARCIPHER_LIBS)

-include $(top_srcdir)/git.mk
