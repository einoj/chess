#include <stdlib.h>
#include <chess.h>

int queen(struct Move mov, int board[][8]) {
	int i, j;
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
	else if (mov.nextRow > mov.currRow && mov.nextCol > mov.currCol) {
		/*move north east*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(mov.currCol-mov.nextCol)==abs(mov.currRow-mov.nextRow))){
			return 0;
		}
		j = mov.currRow;
		for(i = mov.currCol+1; i < mov.nextCol; ++i) {
			j++;
			if (checkPosition(j,i,board)) {
				/*if piece at intermediate possition move is illegal*/
				return 0;
			}
		}
		/*reached new position*/
		return 1;
	}
	else if (mov.nextRow > mov.currRow && mov.nextCol < mov.currCol) {
		/*move north west*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(mov.currCol-mov.nextCol)==abs(mov.currRow-mov.nextRow))){
			return 0;
		}
		j = mov.currRow;
		for(i = mov.currCol-1; i > mov.nextCol; --i) {
			++j;
			if (checkPosition(j,i,board)) {
				/*if piece at intermediate possition move is illegal*/
				return 0;
			}
		}
		/*reached new position*/
		return 1;
	}
	else if (mov.nextRow < mov.currRow && mov.nextCol < mov.currCol) {
		/*move south west*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(mov.currCol-mov.nextCol)==abs(mov.currRow-mov.nextRow))){
			return 0;
		}
		j = mov.currRow;
		for(i = mov.currCol-1; i > mov.nextCol; --i) {
			--j;
			if (checkPosition(j,i,board)) {
				/*if piece at intermediate possition move is illegal*/
				return 0;
			}
		}
		/*reached new position*/
		return 1;
	}
	else if (mov.nextRow < mov.currRow && mov.nextCol > mov.currCol) {
		/*move south east*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(mov.currCol-mov.nextCol)==abs(mov.currRow-mov.nextRow))){
			return 0;
		}
		j = mov.currRow;
		for(i = mov.currCol+1; i < mov.nextCol; ++i) {
			--j;
			if (checkPosition(j,i,board)) {
				/*if piece at intermediate possition move is illegal*/
				return 0;
			}
		}
		/*reached new position*/
		return 1;
	}
	/*illeagal move*/
	return 0;
}
