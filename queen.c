#include <stdlib.h>
extern void makemove(int pos[], int b[][8]);
extern int checkPosition(int row, int col, int b[][8]);

int queen(int pos[], int board[][8]) {
	/*[col][row][col][row]*/
	/*pos[] contains current possitions and new possitions [0][1]=current [2][3] = new*/
	int i, j;
	if (pos[3] > pos[1] && pos[2] == pos[0]) {
		/*move north*/
		for(i = pos[1]+1; i < pos[3]; ++i) {
			if (checkPosition(i,pos[0],board)) {
				/*if piece at intermediate possition move is illeagl*/
				return 0;
			}
		}
		/*reached new position*/
		makemove(pos,board);
		return 1;
	}
	else if (pos[3] == pos[1] && pos[2] < pos[0]) {
		/*west*/
		for(i = pos[0]-1; i > pos[2]; --i) {
			if (checkPosition(pos[1],i,board)) {
				/*if piece at intermediate possition move is illeagl*/
				return 0;
			}
		}
		/*reached new position*/
		makemove(pos,board);
		return 1;
	}
	else if (pos[3] < pos[1] && pos[2] == pos[0]) {
		/*move south*/
		for(i = pos[1]-1; i > pos[3]; --i) {
			if (checkPosition(i,pos[0],board)) {
				/*if piece at intermediate possition move is illeagl*/
				return 0;
			}
		}
		/*reached new position*/
		makemove(pos,board);
		return 1;
	}
	else if (pos[3] == pos[1] && pos[2] > pos[0]) {
		/*move east*/
		for(i = pos[0]+1; i < pos[2]; ++i) {
			if (checkPosition(pos[1],i,board)) {
				/*if piece at intermediate possition move is illeagl*/
				return 0;
			}
		}
		/*reached new position*/
		makemove(pos,board);
		return 1;
	}
	else if (pos[3] > pos[1] && pos[2] > pos[0]) {
		/*move north east*/
		/*if move is not horizontal, return 0*/
		/*change in x-axis must equal change in y-axis*/
		if (!(abs(pos[0]-pos[2])==abs(pos[1]-pos[3]))){
			return 0;
		}
		j = pos[1];
		for(i = pos[0]+1; i < pos[2]; ++i) {
			j++;
			if (checkPosition(j,i,board)) {
				/*if piece at intermediate possition move is illegal*/
				return 0;
			}
		}
		/*reached new position*/
		makemove(pos,board);
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
		for(i = pos[0]-1; i > pos[2]; --i) {
			++j;
			if (checkPosition(j,i,board)) {
				/*if piece at intermediate possition move is illegal*/
				return 0;
			}
		}
		/*reached new position*/
		makemove(pos,board);
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
		for(i = pos[0]-1; i > pos[2]; --i) {
			--j;
			if (checkPosition(j,i,board)) {
				/*if piece at intermediate possition move is illegal*/
				return 0;
			}
		}
		/*reached new position*/
		makemove(pos,board);
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
		for(i = pos[0]+1; i < pos[2]; ++i) {
			--j;
			if (checkPosition(j,i,board)) {
				/*if piece at intermediate possition move is illegal*/
				return 0;
			}
		}
		/*reached new position*/
		makemove(pos,board);
		return 1;
	}
	else {
		/*illeagal move*/
		return 0;
	}
}
