#include <stdlib.h>
#include <chess.h>

int bishop(struct Move mov, int board[][8]) {
	int i,j;
	if (mov.nextRow > mov.currRow && mov.nextCol > mov.currCol) {
		/*move down right*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(mov.currCol-mov.nextCol)==abs(mov.currRow-mov.nextRow))){
			return 0;
		}
		j = mov.currCol;
		for(i = mov.currRow+1; i < mov.nextRow; i++) {
				j++;
				if (checkPosition(i,j,board)) {
					/*if piece at intermediate possition move is illegal*/
					return 0;
				}
		}
		/*reached new position*/
		return 1;
	}
	else if (mov.nextRow > mov.currRow && mov.nextCol < mov.currCol) {
		/*move down left*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(mov.currCol-mov.nextCol)==abs(mov.currRow-mov.nextRow))){
			return 0;
		}
		j = mov.currCol;
		for(i = mov.currRow+1; i < mov.nextRow; i++) {
				j--;
				if (checkPosition(i,j,board)) {
					/*if piece at intermediate possition move is illegal*/
					return 0;
				}
		}
		/*reached new position*/
		return 1;
	}
	else if (mov.nextRow < mov.currRow && mov.nextCol < mov.currCol) {
		/*move up left*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(mov.currCol-mov.nextCol)==abs(mov.currRow-mov.nextRow))){
			return 0;
		}
		j = mov.currCol;
		for(i = mov.currRow-1; i > mov.nextRow; i--) {
				j--;
				if (checkPosition(i,j,board)) {
					/*if piece at intermediate possition move is illegal*/
					return 0;
				}
		}
		/*reached new position*/
		return 1;
	}
	else if (mov.nextRow < mov.currRow && mov.nextCol > mov.currCol) {
		/*move up right*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(mov.currCol-mov.nextCol)==abs(mov.currRow-mov.nextRow))){
			return 0;
		}
		j = mov.currCol;
		for(i = mov.currRow-1; i > mov.nextRow; i--) {
				j++;
				if (checkPosition(i,j,board)) {
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
