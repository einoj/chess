#include <stdio.h>
#include "letterToInt.h"
#include <chess.h>

int getInput(int player, struct Move *mov) {
	char input[10];
	if(player == black)
		printf("black's move: ");
	else
		printf("white's move: ");
	if (fgets(input, 8, stdin) == NULL) {
        return 1;
        printf("ERROR: Invalid input\n");
    }

	mov->currCol = ltoi(input[0]);
	mov->currRow = ltoi(input[1]);
	mov->nextCol = ltoi(input[2]);
	mov->nextRow = ltoi(input[3]);
    return 0;
}

int main(void) {
	int playing = 1;
    struct Move mov;
	int white = 0;
	int black = 1;
	int board[8][8];	

	initBoard(board);
	printBoard(board);
  
	while (playing) {
		/*0 is white 1 is black*/
		do {
            while (getInput(white, &mov));
		} while (!makemove(white, mov, board));
		printBoard(board);
		do {
            while (getInput(black, &mov));
		} while (!makemove(black, mov, board));
		printBoard(board);
	}
	return 0;
}
