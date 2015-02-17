#include <stdlib.h>

extern int checkPosition(int row, int col, int b[][8]);

int bishop(int pos[], int board[][8]) {
	/*[col][row][col][row]*/
	/*pos[] contains current possitions and new possitions [0][1]=current [2][3] = new*/
	int i,j;
	if (pos[3] > pos[1] && pos[2] > pos[0]) {
		/*move north east*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(pos[0]-pos[2])==abs(pos[1]-pos[3]))){
			return 0;
		}
		j = pos[1];
		for(i = pos[0]+1; i < pos[2]; i++) {
				j++;
				if (checkPosition(i,j,board)) {
					/*if piece at intermediate possition move is illegal*/
					return 0;
				}
			}
		/*reached new position*/
		return 1;
	}
	else if (pos[3] > pos[1] && pos[2] < pos[0]) {
		/*move north west*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(pos[0]-pos[2])==abs(pos[1]-pos[3]))){
			return 0;
		}
		j = pos[1];
		for(i = pos[0]-1; i > pos[2]; i--) {
				j++;
				if (checkPosition(i,j,board)) {
					/*if piece at intermediate possition move is illegal*/
					return 0;
				}
			}
		/*reached new position*/
		return 1;
	}
	else if (pos[3] < pos[1] && pos[2] < pos[0]) {
		/*move south west*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(pos[0]-pos[2])==abs(pos[1]-pos[3]))){
			return 0;
		}
		j = pos[1];
		for(i = pos[0]-1; i > pos[2]; i--) {
				--j;
				if (checkPosition(i,j,board)) {
					/*if piece at intermediate possition move is illegal*/
					return 0;
				}
			}
		/*reached new position*/
		return 1;
	}
	else if (pos[3] < pos[1] && pos[2] > pos[0]) {
		/*move south east*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(pos[0]-pos[2])==abs(pos[1]-pos[3]))){
			return 0;
		}
		j = pos[1];
		for(i = pos[0]+1; i < pos[2]; i++) {
				--j;
				if (checkPosition(i,j,board)) {
					/*if piece at intermediate possition move is illegal*/
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
