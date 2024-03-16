CC       = gcc
BUILDDIR = build
SRCDIR   = src
CLIDIR   = cliobj
INCDIR   = inc
TESTDIR  = tests
DBGDIR   = $(BUILDDIR)/debug
UNITYDIR = $(TESTDIR)/Unity/src
LDFLAGS  = `pkg-config --libs gtk4`
GUIFLAGS = `pkg-config --cflags gtk4`
CFLAGS   = -Wall -Wextra -Os -s -I${INCDIR}
DBGFLAGS = -Wall -Wextra -Os -ggdb -I${INCDIR}

SRCS     = $(wildcard $(SRCDIR)/*.c)
OBJS	 = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
GUIOBJS  = $(filter-out $(BUILDDIR)/chessCLI.o,$(OBJS))
CLIOBJS  = $(filter-out $(BUILDDIR)/chessGUI.o,$(OBJS))
DBGOBJS  = $(patsubst $(BUILDDIR)%,$(DBGDIR)%,$(CLIOBJS))
TESTOBJS = $(filter-out $(BUILDDIR)/chessCLI.o $(BUILDDIR)/chessGUI.o,$(OBJS))
TESTOBJS += $(BUILDDIR)/unity.o
DBGTESTOBJS = $(patsubst $(BUILDDIR)%,$(DBGDIR)%,$(TESTOBJS))

all: $(BUILDDIR)/chessGUI $(BUILDDIR)/chessCLI

debug: $(DBGDIR)/chessCLI debugtest

$(BUILDDIR)/chessGUI: $(GUIOBJS)
	$(CC) $(CFLAGS) $(GUIOBJS) $(LDFLAGS) -o $@

$(BUILDDIR)/chessCLI: $(CLIOBJS)
	$(CC) $(CFLAGS) $(CLIOBJS) -o $@

debugtest: $(DBGTESTOBJS)
	$(CC) $(DBGFLAGS) $(DBGTESTOBJS) -I$(UNITYDIR) $(TESTDIR)/TestChess.c -o $(DBGDIR)/testChess

test: $(TESTOBJS)
	$(CC) $(CFLAGS) $(TESTOBJS) -I$(UNITYDIR) $(TESTDIR)/TestChess.c -o $(BUILDDIR)/testChess

$(BUILDDIR)/unity.o: $(UNITYDIR)/unity.c
	$(CC) $(CFLAGS) $< -c -o $@

$(DBGDIR)/unity.o: $(UNITYDIR)/unity.c
	$(CC) $(DBGFLAGS) $< -c -o $@

$(OBJS): | $(BUILDDIR)
$(BUILDDIR):
	mkdir -p $@

$(BUILDDIR)/chessGUI.o: $(SRCDIR)/chessGUI.c
	$(CC) $(CFLAGS) $(GUIFLAGS) $< -c -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(wildcard $(INCDIR)/*.h) Makefile
	$(CC) $(CFLAGS) $< -c -o $@

$(DBGDIR)/chessCLI: $(DBGOBJS)
	$(CC) $(DBGFLAGS) $(DBGOBJS) -o $@

$(DBGDIR)/%.o: $(SRCDIR)/%.c $(wildcard $(INCDIR)/*.h) Makefile
		$(CC) $(DBGFLAGS) $< -c -o $@

$(DBGOBJS): | $(DBGDIR)
$(DBGDIR):
	mkdir -p $@

install: 
	cp chessGUI $(DESTDIR)
	cp -r style $(DESTDIR)

clean:
	rm -rf $(BUILDDIR)
