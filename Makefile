CC       = gcc
BUILDDIR = build
SRCDIR   = src
CLIDIR   = cliobj
INCDIR   = inc
TESTDIR  = tests
UNITYDIR = $(TESTDIR)/Unity/src
LDFLAGS  = `pkg-config --libs gtk4`
GUIFLAGS = `pkg-config --cflags gtk4`
CFLAGS   = -Wall -Os -s -I${INCDIR}

SRCS     = $(wildcard $(SRCDIR)/*.c)
OBJS	 = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
GUIOBJS  = $(filter-out $(BUILDDIR)/chessCLI.o,$(OBJS))
CLIOBJS  = $(filter-out $(BUILDDIR)/chessGUI.o,$(OBJS))
TESTOBJS = $(filter-out $(BUILDDIR)/chessCLI.o $(BUILDDIR)/chessGUI.o,$(OBJS))
TESTOBJS += $(BUILDDIR)/unity.o

all: $(BUILDDIR)/chessGUI $(BUILDDIR)/chessCLI

$(BUILDDIR)/chessGUI: $(GUIOBJS)
	$(CC) $(CFLAGS) $(GUIOBJS) $(LDFLAGS) -o $@

$(BUILDDIR)/chessCLI: $(CLIOBJS)
	$(CC) $(CFLAGS) $(CLIOBJS) -o $@

test: $(TESTOBJS)
	$(CC) $(CFLAGS) $(TESTOBJS) -I$(UNITYDIR) $(TESTDIR)/TestChess.c -o $(BUILDDIR)/testChess

$(BUILDDIR)/unity.o: $(UNITYDIR)/unity.c
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJS): | $(BUILDDIR)
$(BUILDDIR):
	mkdir -p $@

$(BUILDDIR)/chessGUI.o: $(SRCDIR)/chessGUI.c
	$(CC) $(CFLAGS) $(GUIFLAGS) $< -c -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(wildcard $(INCDIR)/*.h) Makefile
	$(CC) $(CFLAGS) $< -c -o $@

install: 
	cp chessGUI $(DESTDIR)
	cp -r style $(DESTDIR)

clean:
	rm -rf $(BUILDDIR)
