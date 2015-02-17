CC      = gcc
OBJDIR  = obj
SRCDIR  = src
INCDIR  = inc
CFLAGS  = -Wall
LDFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

SRCS    = $(wildcard $(SRCDIR)/*.c)
#SRCS  += $(wildcard $(SRCDIR)/*.h)
OBJS		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o) # One objectfile for each source
CLIOBJS = $(filter-out $(OBJDIR)/chessGUI.o,$(OBJS))

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

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(wildcard $(INCDIR)/*.h) Makfile
ifeq ($@, chessGUI)
		$(CC) $(CFLAGS) $< -c -o $@ $(LDFLAGS)
else	
		$(CC) $(CFLAGS) $< -c -o $@
endif

clean:
	rm -r $(OBJDIR)
