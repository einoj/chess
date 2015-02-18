extern int checkPosition(int row, int col, int b[][8]);
extern void completemove(int pos[], int b[][8]);
extern void setPassant(int column, int player);
extern int checkPassant(int row, int column, int player);

int pawn(int pos[], int player, int board[][8]) {
	/*[col][row][col][row]*/
	/*pos[] contains current possitions and new possitions [0][1]=current [2][3] = new*/
	if (player) {
		/*player is black*/
		if (pos[3] == pos[1]+1 && pos[2] == pos[0]+1) {
			/*move north east*/
			if (checkPosition(pos[3], pos[2], board)) {
				/*piece at position, therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;
			/*a pawn was at new pos the previous round, therfore move is leagal*/
			} else if(checkPassant(pos[1],pos[2],player)) {
				/*remove the pawn that moved last round*/
				board[pos[3]-1][pos[2]] = 0;
				return 1;
			}
		}
		else if (pos[3] == pos[1]+1 && pos[2] == pos[0]-1) {
			/*move north west*/
			if (checkPosition(pos[3], pos[2], board)) {
				/*piece at position, therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;
			/*a pawn was at new pos the previous round, therfore move is leagal*/
			} else if(checkPassant(pos[1],pos[2],player)) {
				/*remove the pawn that moved last round*/
				board[pos[3]-1][pos[2]] = 0;
				return 1;
			}
			else {
				/*illegal move*/
				return 0;
			}
		}
		else if (pos[3] == pos[1]+1 && pos[2] == pos[0]) {
			/*Move one step north*/
			if (!checkPosition(pos[3], pos[2], board)) {
				/*piece not at position therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;
			}
			else {
				/*legal move*/
				return 0;
			}
		}
		else if (pos[3] == pos[1]+2 && pos[2] == pos[0]) {
			/*Move two steps north*/
			if (!checkPosition(pos[3], pos[2], board) && !checkPosition(pos[3]-1, pos[2], board) && (pos[1] == 1 || pos[1] == 6)) {
				/*No piece at new position, middle position, and not moved, therfore move is leagal*/
				completemove(pos, board);
				/*set the previous collumn position to the 
				* pessant array. This is done after the move is made
				* because completemove resets the pessant arrays.*/
				setPassant(pos[0],player);
				return 2;
			}
			else {
				/*illegal move*/
				return 0;
			}
		}
		else {
			/*illeagal move*/
			return 0;
		}
	}

	else {
		/*player is white*/
		if (pos[3] == pos[1]-1 && pos[2] == pos[0]+1) {
			/*move south east*/
			if (checkPosition(pos[3], pos[2], board)) {
				/*piece at position, therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;

			/*a pawn was at new pos the previous round, therfore move is leagal*/
			} else if(checkPassant(pos[1],pos[2],player)) {
				/*remove the pawn that moved last round*/
				board[pos[3]+1][pos[2]] = 0;
				return 1;
			}
		}
		else if (pos[3] == pos[1]-1 && pos[2] == pos[0]-1) {
			/*move south west*/
			if (checkPosition(pos[3], pos[2], board)) {
				/*piece at position, therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;
			/*a pawn was at new pos the previous round, therfore move is leagal*/
			} else if(checkPassant(pos[1],pos[2],player)) {
				/*remove the pawn that moved last round*/
				board[pos[3]+1][pos[2]] = 0;
				return 1;
			}
			else {
				/*illegal move*/
				return 0;
			}
		}
		else if (pos[3] == pos[1]-1 && pos[2] == pos[0]) {
			/*Move one step south*/
			if (!checkPosition(pos[3], pos[2], board)) {
				/*piece not at position therfore move is leagal*/
				/*add method to check if reached end of board to swap piece*/
				return 1;
			}
			else {
				/*illegal move*/
				return 0;
			}
		}
		else if (pos[3] == pos[1]-2 && pos[2] == pos[0]) {
			/*Move two steps south*/
			if (!checkPosition(pos[3], pos[2], board) && !checkPosition(pos[3]+1, pos[2], board) && (pos[1] == 1 || pos[1] == 6)) {
				/*No piece at new position, middle position, and not moved, therfore move is leagal*/
				completemove(pos, board);
				/*set the previous collumn position to the 
				* pessant array. This is done after the move is made
				* because completemove resets the pessant arrays.*/
				setPassant(pos[0],player);
				return 2;
			}
			else {
				/*illegal move*/
				return 0;
			}
		}
		else {
			/*illeagal move*/
			return 0;
		}
	}
    /*illegal move*/
    return 0;
}
