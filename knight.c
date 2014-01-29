int knight(int pos[], int board[][8]) {
	/* pos is the input player is the color of player*/
	if (pos[3] == pos[1]+1 && pos[2] == pos[0]+2) {
		/*move 1 north 2 east*/
		return 1;
	}
	else if (pos[3] == pos[1]+2 && pos[2] == pos[0]+1) {
		/*move 2 north 1 east*/
		return 1;
	}
	else if (pos[3] == pos[1]+2 && pos[2] == pos[0]-1) {
		/*move 2 north 1 west*/
		return 1;
	}
	else if (pos[3] == pos[1]+1 && pos[2] == pos[0]-2) {
		/*move 1 north 2 west*/
		return 1;
	}
	else if (pos[3] == pos[1]-1 && pos[2] == pos[0]-2) {
		/*move 1 south 2 west*/
		return 1;
	}
	else if (pos[3] == pos[1]-2 && pos[2] == pos[0]-1) {
		/*move 2 south 1 west*/
		return 1;
	}
	else if (pos[3] == pos[1]-2 && pos[2] == pos[0]+1) {
		/*move 2 south 1 east*/
		return 1;
	}
	else if (pos[3] == pos[1]-1 && pos[2] == pos[0]+2) {
		/*move 1 south 2 east*/
		return 1;
	}
	else {
		/*invalid move*/
		return 0;
	}
}
