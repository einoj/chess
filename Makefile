CC      = gcc
OBJDIR  = obj
SRCDIR  = src
CLIDIR  = cliobj
INCDIR  = inc
CFLAGS  = -Wall
LDFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS		= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
CLIOBJS = $(filter-out $(OBJDIR)/chessGUI.o $(OBJDIR)/chess.o,$(OBJS))
CLIOBJS += $(CLIDIR)/chess.o

all: chessGUI chessCLI

chessGUI: CFLAGS += -DGUI
chessGUI: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o chessGUI $(LDFLAGS)

chessCLI: CFLAGS := -DCLI
chessCLI: $(CLIOBJS) 
	$(CC) $(CFLAGS) $(CLIOBJS) -o chessCLI 

$(OBJS): | $(OBJDIR)
$(OBJDIR):
	mkdir -p $@

$(CLIOBJS): | $(CLIDIR)
$(CLIDIR):
	mkdir -p $@

$(OBJDIR)/chessGUI.o: $(SRCDIR)/chessGUI.c
	$(CC) $(CFLAGS) $< -c -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(wildcard $(INCDIR)/*.h) Makefile
	$(CC) $(CFLAGS) $< -c -o $@

$(CLIDIR)/%.o: $(SRCDIR)/%.c $(wildcard $(INCDIR)/*.h) Makefile
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(OBJDIR)
