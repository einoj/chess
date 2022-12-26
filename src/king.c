#include <chess.h>

int king(struct Move mov, int board[][8]) {
	if (mov.nextRow == mov.currRow+1 && mov.nextCol == mov.currCol) {
		/*north*/
		if(!squareUnderAttack(mov,board)) {
			return 1;
		}
		return 1;
	}
	else if (mov.nextRow == mov.currRow && mov.nextCol == mov.currCol-1) {
		/*west*/
		if(!squareUnderAttack(mov,board)) {
			return 1;
		}
		return 1;
	}
	else if (mov.nextRow == mov.currRow-1 && mov.nextCol == mov.currCol) {
		/*move south*/
		if(!squareUnderAttack(mov,board)) {
			return 1;
		}
		return 1;
	}
	else if (mov.nextRow == mov.currRow && mov.nextCol == mov.currCol+1) {
		/*move east*/
		if(!squareUnderAttack(mov,board)) {
			return 1;
		}
		return 1;
	}
	else if (mov.nextRow == mov.currRow+1 && mov.nextCol == mov.currCol+1) {
		/*move north east*/
		if(!squareUnderAttack(mov,board)) {
			return 1;
		}
		return 1;
	}
	else if (mov.nextRow == mov.currRow+1 && mov.nextCol == mov.currCol-1) {
		/*move north west*/
		if(!squareUnderAttack(mov,board)) {
			return 1;
		}
		return 1;
	}
	else if (mov.nextRow == mov.currRow-1 && mov.nextCol == mov.currCol-1) {
		/*move south west*/
		if(!squareUnderAttack(mov,board)) {
			return 0;
		}
		return 1;
	}
	else if (mov.nextRow == mov.currRow-1 && mov.nextCol == mov.currCol+1) {
		/*move south east*/
		if(!squareUnderAttack(mov,board)) {
			return 1;
		}
		return 0;
	}
	/*illeagal move*/
	return 0;
}
