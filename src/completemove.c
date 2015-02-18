extern void resetPassantArrays();
/* 
 This method will move a piece from its
 current position to a new one
*/
void completemove(int pos[], int b[][8]) {
	/*[0] = curCol, [1] curRow, [2] nexCol, [3] nexRow*/
/*
	printf("%d,%d,%d,%d\n",pos[0], pos[1], pos[2], pos[3]);*/
	int tempPiece = b[pos[1]][pos[0]];
	b[pos[1]][pos[0]] = 0;
	b[pos[3]][pos[2]] = tempPiece;
	resetPassantArrays();
}
