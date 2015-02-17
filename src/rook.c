extern int checkPosition(int row, int col, int b[][8]);

int rook(int pos[], int board[][8]) {
	/*[col][row][col][row]*/
	/*pos[] contains current possitions and new possitions [0][1]=current [2][3] = new*/
	int i;
	if (pos[3] > pos[1] && pos[2] == pos[0]) {
		/*move north*/
		for(i = pos[1]+1; i < pos[3]; ++i) {
			if (checkPosition(i,pos[0],board)) {
				/*if piece at intermediate possition move is illeagl*/
				return 0;
			}
		}
		/*reached new position*/
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
		return 1;
	}
	else {
		/*illeagal move*/
		return 0;
	}
}
