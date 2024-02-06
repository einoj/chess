#include <chess.h>

int king(int player, struct Move mov, int board[][8]) {
	if(squareUnderAttack(player, mov, board)) {
		return 0;
	}

	if (mov.nextRow == mov.currRow+1 && mov.nextCol == mov.currCol) {
		/*north*/
		return 1;
	}
	else if (mov.nextRow == mov.currRow && mov.nextCol == mov.currCol-1) {
		/*west*/
		return 1;
	}
	else if (mov.nextRow == mov.currRow-1 && mov.nextCol == mov.currCol) {
		/*move south*/
		return 1;
	}
	else if (mov.nextRow == mov.currRow && mov.nextCol == mov.currCol+1) {
		/*move east*/
		return 1;
	}
	else if (mov.nextRow == mov.currRow+1 && mov.nextCol == mov.currCol+1) {
		/*move north east*/
		return 1;
	}
	else if (mov.nextRow == mov.currRow+1 && mov.nextCol == mov.currCol-1) {
		/*move north west*/
		return 1;
	}
	else if (mov.nextRow == mov.currRow-1 && mov.nextCol == mov.currCol-1) {
		/*move south west*/
		return 1;
	}
	else if (mov.nextRow == mov.currRow-1 && mov.nextCol == mov.currCol+1) {
		/*move south east*/
		return 1;
	}
	/*illeagal move*/
	return 0;
}
