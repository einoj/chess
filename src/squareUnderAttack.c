#include <chess.h>
#include <stdio.h>
#include <string.h>

int squareUnderAttack(int player, struct Move mov, int board[][8]) {
    struct Square next_square = { .row = mov.nextRow, .col = mov.nextCol };
    struct Square curr_square = { .row = mov.currRow, .col = mov.currCol };

    /* Make a temporary board for two reasons
     * 1. The makemove() function moves pieces around the board, and we do not want that
     * 2. Pawns can only take diagonally when there is a piece on the destination square
     * */
    int tmp_board[8][8];
    memcpy(tmp_board, board, 64*sizeof(int));
    // move piece to new square so potential pawns can attack it
    tmp_board[mov.nextRow][mov.nextCol] = tmp_board[mov.currRow][mov.currCol];
	tmp_board[mov.currRow][mov.currCol] = 0;
    struct Move tmp_mov = { .currRow = 0, .currCol = 0, .nextRow = next_square.row, .nextCol = next_square.col };
    /* for now just be stupid and loop over the whole board.
     in the future this can be changed to only check the pieces on the board
     but before optimizing like that there should be lots of test so it can be
     verified whether the optimization actually makes the game faster */
	for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tmp_mov = (struct Move) { .currRow = i, .currCol = j, .nextRow = next_square.row, .nextCol = next_square.col };
            if ( tmp_board[i][j] == emptySquare )
                continue;
            if ( i == curr_square.row && curr_square.col == j )
                continue;
            if (checkColor(tmp_mov, !player, tmp_board) == 0)
                continue;
            if (makemove(!player, tmp_mov, tmp_board) == 1) {
                return 1;
            }
        }
    }
    return 0;
}
