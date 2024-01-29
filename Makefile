CC      = gcc
OBJDIR  = obj
SRCDIR  = src
CLIDIR  = cliobj
INCDIR  = inc
LDFLAGS = `pkg-config --libs gtk4`
CFLAGS  = -Wall -Os -s -I${INCDIR} `pkg-config --cflags gtk4`

SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS		= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
GUIOBJS = $(filter-out $(OBJDIR)/chessCLI.o,$(OBJS))
CLIOBJS = $(filter-out $(OBJDIR)/chessGUI.o,$(OBJS))

all: chessGUI chessCLI

chessGUI: $(GUIOBJS)
	$(CC) $(CFLAGS) $(GUIOBJS) -o chessGUI $(LDFLAGS)

chessCLI: $(CLIOBJS) 
	$(CC) $(CFLAGS) $(CLIOBJS) -o chessCLI 

$(OBJS): | $(OBJDIR)
$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/chessGUI.o: $(SRCDIR)/chessGUI.c
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(wildcard $(INCDIR)/*.h) Makefile
	$(CC) $(CFLAGS) $< -c -o $@

install: 
	cp chessGUI $(DESTDIR)
	cp -r style $(DESTDIR)

clean:
	rm -rf $(OBJDIR)
