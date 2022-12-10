CC      = x86_64-w64-mingw32-gcc
RELEASEDIR = release
OBJDIR  = obj
SRCDIR  = src
CLIDIR  = cliobj
INCDIR  = inc
CFLAGS  = -Wall -Os -s -mwindows
LDFLAGS = `mingw64-pkg-config --static --cflags gtk+-3.0` `mingw64-pkg-config --static --libs gtk+-3.0` -L/usr/x86_64-w64-mingw32/sys-root/mingw/lib -l:libgtk-3.dll.a -lz

SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS		= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
GUIOBJS = $(filter-out $(OBJDIR)/chessCLI.o,$(OBJS))
CLIOBJS = $(filter-out $(OBJDIR)/chessGUI.o,$(OBJS))
DLLS = iconv.dll libatk-1.0-0.dll libbz2-1.dll libcairo-2.dll \
		libcairo-gobject-2.dll libepoxy-0.dll libexpat-1.dll libffi-8.dll \
		libfontconfig-1.dll libfreetype-6.dll libfribidi-0.dll libgcc_s_seh-1.dll \
		libgdk-3-0.dll libgdk_pixbuf-2.0-0.dll libgio-2.0-0.dll libglib-2.0-0.dll \
		libgmodule-2.0-0.dll libgobject-2.0-0.dll libgtk-3-0.dll libharfbuzz-0.dll \
		libintl-8.dll libjpeg-62.dll libpango-1.0-0.dll libpangocairo-1.0-0.dll \
		libpangoft2-1.0-0.dll libpangowin32-1.0-0.dll libpcre2-8-0.dll \
		libpixman-1-0.dll libpng16-16.dll libssp-0.dll libtiff-5.dll \
		libwinpthread-1.dll zlib1.dll

all: chessGUI chessCLI

chessGUI: $(GUIOBJS)
	$(CC) $(CFLAGS) $(GUIOBJS) -o chessGUI $(LDFLAGS)

chessCLI: $(CLIOBJS) 
	$(CC) $(CFLAGS) $(CLIOBJS) -o chessCLI 

$(OBJS): | $(OBJDIR)
$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/chessGUI.o: $(SRCDIR)/chessGUI.c
	$(CC) $(CFLAGS) $< -c -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(wildcard $(INCDIR)/*.h) Makefile
	$(CC) $(CFLAGS) $< -c -o $@

install: 
	cp chessGUI $(DESTDIR)
	cp -r style $(DESTDIR)

release: chessGUI
	mkdir -p $(RELEASEDIR)
	cp chessGUI.exe $(RELEASEDIR)
	cp -r style $(RELEASEDIR)
	for dll in $(DLLS); \
		do cp /usr/x86_64-w64-mingw32/sys-root/mingw/bin/$$dll $(RELEASEDIR); \
	done

clean:
	rm -rf $(OBJDIR)
	rm -rf $(RELEASEDIR)
