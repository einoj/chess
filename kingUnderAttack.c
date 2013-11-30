/* This function first checks if the king is currently under attack
* If the king is under attack, check if it is possible to save it
*/
int kingUnderAttack(int player, int move[], int board[][8]) {
	/*if player is white*/
	if (!player) {
		int i, j;
		int kingPos[2];
		/*find the white king*/
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {

				if (board[i][j] == 6) {
					kingPos[0] =i;
					kingPos[1] =j;

			}
		}

		/*check if any black pieces can move to that square*/

		/*if black pieces can move to king square, check if any white pieces can block or the king can be moved*/

		/*if not, check mate*/

	}
	/*Pawn attacker*/

}
