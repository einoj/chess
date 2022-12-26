#include <chess.h>

int pawn(struct Move mov, int player, int board[][8]) {
	if (player) {
		/*player is black*/
		if (mov.nextRow == mov.currRow+1 && mov.nextCol == mov.currCol+1) {
			/*move north east*/
			if (checkPosition(mov.nextRow, mov.nextCol, board)) {
				/*piece at position, therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;
			/*a pawn was at new pos the previous round, therfore move is leagal*/
			} else if(checkPassant(mov.currRow,mov.nextCol,player)) {
				/*remove the pawn that moved last round*/
				board[mov.nextRow-1][mov.nextCol] = 0;
				return 1;
			}
		}
		else if (mov.nextRow == mov.currRow+1 && mov.nextCol == mov.currCol-1) {
			/*move north west*/
			if (checkPosition(mov.nextRow, mov.nextCol, board)) {
				/*piece at position, therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;
			/*a pawn was at new pos the previous round, therfore move is leagal*/
			} else if(checkPassant(mov.currRow,mov.nextCol,player)) {
				/*remove the pawn that moved last round*/
				board[mov.nextRow-1][mov.nextCol] = 0;
				return 1;
			}
			/*illegal move*/
			return 0;
		}
		else if (mov.nextRow == mov.currRow+1 && mov.nextCol == mov.currCol) {
			/*Move one step north*/
			if (!checkPosition(mov.nextRow, mov.nextCol, board)) {
				/*piece not at position therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;
			}
			/*legal move*/
			return 0;
		}
		else if (mov.nextRow == mov.currRow+2 && mov.nextCol == mov.currCol) {
			/*Move two steps north*/
			if (!checkPosition(mov.nextRow, mov.nextCol, board) && !checkPosition(mov.nextRow-1, mov.nextCol, board) && (mov.currRow == 1 || mov.currRow == 6)) {
				/*No piece at new position, middle position, and not moved, therfore move is leagal*/
				completemove(mov, board);
				/*set the previous collumn position to the 
				* pessant array. This is done after the move is made
				* because completemove resets the pessant arrays.*/
				setPassant(mov.currCol,player);
				return 2;
			}
			/*illegal move*/
			return 0;
		}
		/*illeagal move*/
		return 0;
	} else {
		/*player is white*/
		if (mov.nextRow == mov.currRow-1 && mov.nextCol == mov.currCol+1) {
			/*move south east*/
			if (checkPosition(mov.nextRow, mov.nextCol, board)) {
				/*piece at position, therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;

			/*a pawn was at new pos the previous round, therfore move is leagal*/
			} else if(checkPassant(mov.currRow,mov.nextCol,player)) {
				/*remove the pawn that moved last round*/
				board[mov.nextRow+1][mov.nextCol] = 0;
				return 1;
			}
		}
		else if (mov.nextRow == mov.currRow-1 && mov.nextCol == mov.currCol-1) {
			/*move south west*/
			if (checkPosition(mov.nextRow, mov.nextCol, board)) {
				/*piece at position, therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;
			/*a pawn was at new pos the previous round, therfore move is leagal*/
			} else if(checkPassant(mov.currRow,mov.nextCol,player)) {
				/*remove the pawn that moved last round*/
				board[mov.nextRow+1][mov.nextCol] = 0;
				return 1;
			}
			/*illegal move*/
			return 0;
		}
		else if (mov.nextRow == mov.currRow-1 && mov.nextCol == mov.currCol) {
			/*Move one step south*/
			if (!checkPosition(mov.nextRow, mov.nextCol, board)) {
				/*piece not at position therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;
			}
			/*illegal move*/
			return 0;
		}
		else if (mov.nextRow == mov.currRow-2 && mov.nextCol == mov.currCol) {
			/*Move two steps south*/
			if (!checkPosition(mov.nextRow, mov.nextCol, board) && !checkPosition(mov.nextRow+1, mov.nextCol, board) && (mov.currRow == 1 || mov.currRow == 6)) {
				/*No piece at new position, middle position, and not moved, therfore move is leagal*/
				completemove(mov, board);
				/*set the previous collumn position to the 
				* pessant array. This is done after the move is made
				* because completemove resets the pessant arrays.*/
				setPassant(mov.currCol,player);
				return 2;
			}
			/*illegal move*/
			return 0;
		}
		/*illeagal move*/
		return 0;
	}
	/*illegal move*/
	return 0;
}
