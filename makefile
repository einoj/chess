all: chessGui

chessGui: chessGui.o chess.o pawn.o rook.o knight.o bishop.o queen.o king.o makemove.o checkPosition.o squareUnderAttack.o convCoordinates.h letterToInt.h
	gcc chessGui.o chess.o pawn.o queen.o king.o knight.o rook.o bishop.o checkPosition.o makemove.o squareUnderAttack.o -o chessGUI `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

chessGui.o: chessGui.c
	gcc -Wall -g chessGui.c -c `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

chess.o: chess.c
	gcc -Wall -c chess.c

pawn.o: pawn.c
	gcc -Wall -c pawn.c

rook.o: rook.c
	gcc -Wall -c rook.c

knight.o: knight.c
	gcc -Wall -c knight.c

bishop.o: bishop.c
	gcc -Wall -c bishop.c

queen.o: queen.c
	gcc -Wall -c queen.c

king.o: king.c
	gcc -Wall -c king.c

makemove.o: makemove.c
	gcc -Wall -c makemove.c

checkPosition.o: checkPosition.c
	gcc -Wall -c checkPosition.c

squareUnderAttack.o: squareUnderAttack.c
	gcc -Wall -c squareUnderAttack.c

clean:
	rm *.o
