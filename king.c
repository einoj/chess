extern void makemove(int pos[], int b[][8]);
extern int squareUnderAttack(int move[], int board[][8]);

int king(int pos[], int board[][8]) {
	/*[col][row][col][row]*/
	/*pos[] contains current possitions and new possitions [0][1]=current [2][3] = new*/
	if (pos[3] == pos[1]+1 && pos[2] == pos[0]) {
		/*north*/
		if(!squareUnderAttack(pos,board)) {
			return 0;
		}
		return 1;
	}
	else if (pos[3] == pos[1] && pos[2] == pos[0]-1) {
		/*west*/
		if(!squareUnderAttack(pos,board)) {
			makemove(pos,board);
			return 0;
		}
		return 1;
	}
	else if (pos[3] == pos[1]-1 && pos[2] == pos[0]) {
		/*move south*/
		if(!squareUnderAttack(pos,board)) {
			makemove(pos,board);
			return 0;
		}
		return 1;
	}
	else if (pos[3] == pos[1] && pos[2] == pos[0]+1) {
		/*move east*/
		if(!squareUnderAttack(pos,board)) {
			makemove(pos,board);
			return 0;
		}
		return 1;
	}
	else if (pos[3] == pos[1]+1 && pos[2] == pos[0]+1) {
		/*move north east*/
		if(!squareUnderAttack(pos,board)) {
			makemove(pos,board);
			return 0;
		}
		return 1;
	}
	else if (pos[3] == pos[1]+1 && pos[2] == pos[0]-1) {
		/*move north west*/
		if(!squareUnderAttack(pos,board)) {
			makemove(pos,board);
			return 0;
		}
		return 1;
	}
	else if (pos[3] == pos[1]-1 && pos[2] == pos[0]-1) {
		/*move south west*/
		if(!squareUnderAttack(pos,board)) {
			makemove(pos,board);
			return 0;
		}
		return 1;
	}
	else if (pos[3] == pos[1]-1 && pos[2] == pos[0]+1) {
		/*move south east*/
		if(!squareUnderAttack(pos,board)) {
			makemove(pos,board);
			return 1;
		}
		return 0;
	}
	else {
		/*illeagal move*/
		return 0;
	}
}
