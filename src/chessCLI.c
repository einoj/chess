#include "letterToInt.h"
#include <chess.h>
#include <stdio.h>
#include <string.h>

#define CLEAR "\033[2J\033[1;1H"

int getInput(int player, struct Move* mov, int board[][8])
{
    int alg_input = 1;
    char input[10];
    if (player == black)
        printf("black's move: ");
    else
        printf("white's move: ");
    if (fgets(input, 8, stdin) == NULL) {
        return 1;
        printf("ERROR: Invalid input\n");
    }

    input[strcspn(input, "\n")] = 0;
    if (alg_input) {
        return convertAlgNotation(input, player, board, mov);
    } else {
        mov->currCol = ltoi(input[0]);
        mov->currRow = ltoi(input[1]);
        mov->nextCol = ltoi(input[2]);
        mov->nextRow = ltoi(input[3]);
    }
    return 0;
}

int getPromotionInput(int *input)
{
    printf("Promote pawn to: [N, B, R, Q]");
    *input = fgetc(stdin);
    if (input == NULL) {
        return -1;
        printf("ERROR: Invalid input\n");
    }
    if (*input == 'N' || *input == 'B' || *input  == 'R' || *input == 'Q')
        return 0;
    return -1;
}

int convertPromotionInput(int *input, int player)
{
    switch (*input) {
    case 'N':
        if (player == white)
            *input = wKnight;
        else if (player == black)
            *input = bKnight;
        return 1;
    case 'B':
        if (player == white)
            *input = wBishop;
        else if (player == black)
            *input = bBishop;
        return 1;
    case 'R':
        if (player == white)
            *input = wRook;
        else if (player == black)
            *input = bRook;
        return 1;
    case 'Q':
        if (player == white)
            *input = wQueen;
        else if (player == black)
            *input = bQueen;
        return 1;
    }
    return -1;
}

void playerLoop(int player, int board[][8])
{
    struct Move mov;
    struct Square sq;
    int ret;
    int promote_to_piece;
    printf(CLEAR);
    printBoard(board);
    do {
        while (getInput(player, &mov, board))
            ;
       ret = makemove(player, mov, board);
       if (ret == 3) {
           sq.row=mov.nextRow;
           sq.col=mov.nextCol;
           while(getPromotionInput(&promote_to_piece))
               ;
           convertPromotionInput(&promote_to_piece, player);
           promotePawn(player, sq, promote_to_piece, board);
       }
    } while (!ret);
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
