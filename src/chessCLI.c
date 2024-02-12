#include "letterToInt.h"
#include <chess.h>
#include <stdio.h>

#define CLEAR "\033[2J\033[1;1H"

int getInput(int player, struct Move* mov)
{
    char input[10];
    if (player == black)
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

void playerLoop(int player, int board[][8])
{
    struct Move mov;
    printf(CLEAR);
    printBoard(board);
    do {
        while (getInput(player, &mov))
            ;
    } while (!makemove(player, mov, board));
}

int main(void)
{
    int board[8][8];
    initBoard(board);
    while (1) {
        playerLoop(white, board);
        playerLoop(black, board);
    }
    return 0;
}
