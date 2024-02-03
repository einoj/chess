#include <stdio.h>
#include "letterToInt.h"
#include <chess.h>

void printBoard(int tmpBoard[][8]) {
	/*print out the current board and pieces*/
	int i, j;
    printf("\n ─────────────────────────\n");
	/*count down so white is south black is north*/
	for (i = 0; i < 8; ++i) {
		/*print edge of board*/
		printf("%d│", 8-i);
		for (j = 0; j < 8; ++j) {
            switch (tmpBoard[i][j]) {
            case wPawn:
				printf(" ♙│");
                break;
            case bPawn:
				printf(" ♟│");
                break;
            case wKnight:
				printf("wN│");
                break;
            case bKnight:
				printf("bN│");
                break;
            case wBishop:
				printf("wB│");
                break;
            case bBishop:
				printf("bB│");
                break;
            case wRook:
				printf("wR│");
                break;
            case bRook:
				printf("bR│");
                break;
            case wQueen:
				printf("wQ│");
                break;
            case bQueen:
				printf("bQ│");
                break;
            case wKing:
				printf("wK│");
                break;
            case bKing:
				printf("bK│");
                break;
            default:
				printf("  │");
            }
		}
        printf("\n ─────────────────────────\n");
	}
	printf("   a  b  c  d  e  f  g  h \n");	
}

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
