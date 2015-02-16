CC     = gcc
CFLAGS = -Wall 

all: chessGUI chessCLI

chessGUI: CFLAGS += -DGUI
chessGUI: chessGui.o chessG.o pawn.o rook.o knight.o bishop.o queen.o king.o makemove.o checkPosition.o squareUnderAttack.o letterToInt.h
	$(CC) $(CFLAGS) chessGui.o chess.o pawn.o queen.o king.o knight.o rook.o bishop.o checkPosition.o makemove.o squareUnderAttack.o -o chessGUI `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

chessCLI: CFLAGS += -DCLI
chessCLI: chessC.o pawn.o rook.o knight.o bishop.o queen.o king.o makemove.o checkPosition.o squareUnderAttack.o letterToInt.h
	$(CC)  chess.o pawn.o queen.o king.o knight.o rook.o bishop.o checkPosition.o makemove.o squareUnderAttack.o -o chessCLI 

chessGUI.o: chessGUI.c 
	$(CC) $(CFLAGS) -c chessGui.c  

chessG.o: chess.c
	$(CC) $(CFLAGS) -c chess.c

chessC.o: chess.c
	$(CC) $(CFLAGS) -c chess.c

pawn.o: pawn.c
	$(CC) $(CFLAGS) -c pawn.c

rook.o: rook.c
	$(CC) $(CFLAGS) -c rook.c

knight.o: knight.c
	$(CC) $(CFLAGS) -c knight.c

bishop.o: bishop.c
	$(CC) $(CFLAGS) -c bishop.c

queen.o: queen.c
	$(CC) $(CFLAGS) -c queen.c

king.o: king.c
	$(CC) $(CFLAGS) -c king.c

makemove.o: makemove.c
	$(CC) $(CFLAGS) -c makemove.c

checkPosition.o: checkPosition.c
	$(CC) $(CFLAGS) -c checkPosition.c

squareUnderAttack.o: squareUnderAttack.c
	$(CC) $(CFLAGS) -c squareUnderAttack.c

clean:
	rm *.o
