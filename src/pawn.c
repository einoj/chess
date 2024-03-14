#include <chess.h>

int pawn(struct Move mov, int player, int board[][8])
{
    int dir = -1;
    int retval = 0; // returning 0 means it's an illegal move
    if (player == black)
        dir = 1;
    if (mov.nextRow == mov.currRow + dir && mov.nextCol == mov.currCol + 1) {
        /*move north east*/
        if (checkPosition(mov.nextRow, mov.nextCol, board)) {
            /*piece at position, therfore move is leagal*/
            /*add method to check if reached end of board to swap piece*/
            retval = 1;
            /*a pawn was at new pos the previous round, therfore move is leagal*/
        } else if (checkPassant(mov.currRow, mov.nextCol, player)) {
            /*remove the pawn that moved last round*/
            board[mov.nextRow - dir][mov.nextCol] = 0;
            retval = 1;
        }
    } else if (mov.nextRow == mov.currRow + dir && mov.nextCol == mov.currCol - 1) {
        /*move north west*/
        if (checkPosition(mov.nextRow, mov.nextCol, board)) {
            /*piece at position, therfore move is leagal*/
            /*add method to check if reached end of board to swap piece*/
            retval = 1;
            /*a pawn was at new pos the previous round, therfore move is leagal*/
        } else if (checkPassant(mov.currRow, mov.nextCol, player)) {
            /*remove the pawn that moved last round*/
            board[mov.nextRow - dir][mov.nextCol] = 0;
            retval = 1;
        }
    } else if (mov.nextRow == mov.currRow + dir && mov.nextCol == mov.currCol) {
        /*Move one step north*/
        if (!checkPosition(mov.nextRow, mov.nextCol, board)) {
            /*piece not at position therfore move is leagal*/
            /*add method to check if reached end of board to swap piece*/
            retval = 1;
        }
    } else if (mov.nextRow == mov.currRow + 2 * dir && mov.nextCol == mov.currCol) {
        /*Move two steps north*/
        if (!checkPosition(mov.nextRow, mov.nextCol, board) && !checkPosition(mov.nextRow - dir, mov.nextCol, board) && (mov.currRow == 1 || mov.currRow == 6)) {
            /*No piece at new position, middle position, and not moved, therfore move is leagal*/
            /* return 2 for setting enpassant array */
            retval = 2;
        }
    }
    if (retval > 0) {
        if (player == white && mov.nextRow == 0)
            retval = 3;
        else if (player == black && mov.nextRow == 7)
            retval = 3;
    }
    return retval;
}
