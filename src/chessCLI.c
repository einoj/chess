#include <stdio.h>
#include "letterToInt.h"
#include <chess.h>

void printBoard(int tmpBoard[][8]) {
	/*print out the current board and pieces*/
	int i, j;
	/*print top edge*/
	printf(" _________________________\n");
	/*count down so white is south black is north*/
	for (i = 0; i < 8; ++i) {
		/*print edge of board*/
		printf("%d│", 8-i);
		for (j = 0; j < 8; ++j) {
			if (tmpBoard[i][j] == 1) {
				/*white pawn*/
				printf(" ♙│");
			}
			else if (tmpBoard[i][j] == 7) {
				/*black pawn*/
				printf(" ♟│");
			}
			else if (tmpBoard[i][j] == 2) {
				/*white knight*/
				printf("wN│");
			}
			else if (tmpBoard[i][j] == 8) {
				/*black knight*/
				printf("bN│");
			}
			else if (tmpBoard[i][j] == 3) {
				/*white bishop*/
				printf("wB│");
			}
			else if (tmpBoard[i][j] == 9) {
				/*black knight*/
				printf("bB│");
			}
			else if (tmpBoard[i][j] == 4) {
				/*white Rook*/
				printf("wR│");
			}
			else if (tmpBoard[i][j] == 10) {
				/*black Rook*/
				printf("bR│");
			}
			else if (tmpBoard[i][j] == 5) {
				/*white Queen*/
				printf("wQ│");
			}
			else if (tmpBoard[i][j] == 11) {
				/*black Queen*/
				printf("bQ│");
			}
			else if (tmpBoard[i][j] == 6) {
				/*white King*/
				printf("wK│");
			}
			else if (tmpBoard[i][j] == 12) {
				/*black King*/
				printf("bK│");
			}
			else {
				/*empty square*/
				printf("  │");
			}
		}
		/*new row*/
		if (i > 0) {
			printf("\n ─────────────────────────\n");
		}
		else {
			printf("\n _________________________\n");
		}
	}
	/*print bottom row*/
	printf("   a  b  c  d  e  f  g  h \n");	
}

void getInput(int player, int move[], int b[][8]) {
	char input[10];
	/*get input from player*/
	if(player) {
		/* player = 1 black player*/
		printf("black's move: ");
	}
	else {
		/* player = 0 white player*/
		printf("white's move: ");
	}
	fgets(input, 8, stdin);

	move[0] = ltoi(input[0]);
	move[1] = ltoi(input[1]);
	move[2] = ltoi(input[2]);
	move[3] = ltoi(input[3]);
}

int main(void) {
	int playing = 1;
	int move[4];
	int white = 0;
	int black = 1;
	int board[8][8];	

	initBoard(board);
	printBoard(board);
  
	while (playing) {
		/*0 is white 1 is black*/
		do {
      getInput(white, move, board);
		} while (makemove(white, move, board));
		printBoard(board);
		do {
      getInput(black, move, board);
		} while (makemove(black, move, board));
		printBoard(board);
	}
	return 0;
}
