all: chessGui

chessGui: chessGui.o chess.o pawn.o rook.o knight.o bishop.o queen.o king.o makemove.o checkPosition.o squareUnderAttack.o convCoordinates.h letterToInt.h
	gcc -g -Wall chessGui.o chess.o pawn.o queen.o king.o knight.o rook.o bishop.o checkPosition.o makemove.o squareUnderAttack.o -o chessGUI `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

chessGui.o: chessGui.c
	gcc -g -Wall chessGui.c -c `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

chess.o: chess.c
	gcc -c chess.c

pawn.o: pawn.c
	gcc -c pawn.c

rook.o: rook.c
	gcc -c rook.c

knight.o: knight.c
	gcc -c knight.c

bishop.o: bishop.c
	gcc -c bishop.c

queen.o: queen.c
	gcc -c queen.c

king.o: king.c
	gcc -c king.c

makemove.o: makemove.c
	gcc -c makemove.c

checkPosition.o: checkPosition.c
	gcc -c checkPosition.c

squareUnderAttack.o: squareUnderAttack.c
	gcc -c squareUnderAttack.c

clean:
	rm *.o
