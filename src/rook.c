#include <chess.h>

int rook(struct Move mov, int board[][8]) {
	int i;
	if (mov.nextRow > mov.currRow && mov.nextCol == mov.currCol) {
		/*move north*/
		for(i = mov.currRow+1; i < mov.nextRow; ++i) {
			if (checkPosition(i,mov.currCol,board)) {
				/*if piece at intermediate possition move is illeagl*/
				return 0;
			}
		}
		/*reached new position*/
		return 1;
	}
	else if (mov.nextRow == mov.currRow && mov.nextCol < mov.currCol) {
		/*west*/
		for(i = mov.currCol-1; i > mov.nextCol; --i) {
			if (checkPosition(mov.currRow,i,board)) {
				/*if piece at intermediate possition move is illeagl*/
				return 0;
			}
		}
		/*reached new position*/
		return 1;
	}
	else if (mov.nextRow < mov.currRow && mov.nextCol == mov.currCol) {
		/*move south*/
		for(i = mov.currRow-1; i > mov.nextRow; --i) {
			if (checkPosition(i,mov.currCol,board)) {
				/*if piece at intermediate possition move is illeagl*/
				return 0;
			}
		}
		/*reached new position*/
		return 1;
	}
	else if (mov.nextRow == mov.currRow && mov.nextCol > mov.currCol) {
		/*move east*/
		for(i = mov.currCol+1; i < mov.nextCol; ++i) {
			if (checkPosition(mov.currRow,i,board)) {
				/*if piece at intermediate possition move is illeagl*/
				return 0;
			}
		}
		/*reached new position*/
		return 1;
	}
	else {
		/*illeagal move*/
		return 0;
	}
}
