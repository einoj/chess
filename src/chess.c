#include <stdio.h>
#include <string.h>
#include <chess.h>

/*
struct wChessPieces {
	int type;
	struct wChessPieces next;
	struct wChessPieces prev;
}

struct bChessPieces {
	int type;
	struct bChessPieces next;
	struct bChessPieces prev;
}
*/
/*bChessPieces nodeB;
wChessPieces nodeW;
*/
/*int board[8][8]; for use with cmd chess*/
enum pieces { emptySquare,
    wPawn, wKnight, wBishop, wRook, wQueen, wKing,
    bPawn, bKnight, bBishop, bRook, bQueen, bKing
};
int enPassantW[8], enPassantB[8];

void initBoard(int tmpBoard[][8]){
	tmpBoard[7][7] = wRook;
	tmpBoard[7][6] = wKnight;
	tmpBoard[7][5] = wBishop;
	tmpBoard[7][3] = wQueen;
	tmpBoard[7][4] = wKing;
	tmpBoard[7][2] = wBishop;
	tmpBoard[7][1] = wKnight;
	tmpBoard[7][0] = wRook;
	tmpBoard[0][7] = bRook;
	tmpBoard[0][6] = bKnight;
	tmpBoard[0][5] = bBishop;
	tmpBoard[0][3] = bQueen;
	tmpBoard[0][4] = bKing;
	tmpBoard[0][2] = bBishop;
	tmpBoard[0][1] = bKnight;
	tmpBoard[0][0] = bRook;
	
	int i, j;
	for (j = 0; j < 8; ++j) {
		/*black row of pawns*/
		tmpBoard[1][j] = bPawn;
	}

	for (j = 0; j < 8; ++j) {
		/*white row of pawns*/
		tmpBoard[6][j] = wPawn;
	}

	for (i = 2; i < 6; ++i) {
		for (j = 0; j < 8; ++j) {
			/*setup empty squares*/
			tmpBoard[i][j] = emptySquare;
		}
	}
}

/*set the en pessant arrays to 0
* this should be called whenever a move
* is made, except if a pawn is moved two
* squares */
void resetPassantArrays(void) {
	int i;
	for (i = 0; i < 8; ++i) {
		enPassantW[i] = 0;
		enPassantB[i] = 0;
	}
}

/*set the a index of the enPessantArray
* the first parameter is the index,
* it corresponds to a column on the board.
* The second is the player color 0 = white
* 1 = black.*/
void setPassant(int column, int player) {
	if (player) {
		enPassantB[column] = 1;
	} else {
		enPassantW[column] = 1;
	}
}

/* check if pessant jumped over the position last round.
* Check the opposite color of the current player
* Pawn must be on its fifth rank*/
int checkPassant(int row,int column, int player) {
	if (!player) { // white player
		if (row == 3) {
			return enPassantB[column];
		}
        return 0;
	}
	// black palyer
	if (row == 4) {
		return enPassantW[column];
	}
	return 0;
}


int checkColor(struct Move mov, int player, int b[][8]) {
	int aPiece = b[mov.currRow][mov.currCol];
	int dPiece = b[mov.nextRow][mov.nextCol];
	if (((player == 0) && ((aPiece > 0 && aPiece < 7) && ((dPiece > 6 && dPiece < 13) || (dPiece == 0)))) || ((player == 1) && ((aPiece > 6 && aPiece < 13) && ((dPiece > 0 && dPiece < 7) || (dPiece == 0))))) {
		/* player is white and attacking piece is white, and defending piece is black or empty*/
		/* or player is black and attacking piece is black, and defending piece is white or empty*/
		return 1;
	}
    return 0;
}

int checkMove(struct Move mov, int player, int board[][8]) {
	/*get the piece at the given coordinate*/
	int piece = board[mov.currRow][mov.currCol];
    /*hack for making 2 step pawn work*/
    int tmp;
	if (piece == wPawn || piece == bPawn) {
        tmp = pawn(mov, player, board);
		if (tmp == 1) {
            /*The move is also made if pawn() returns 2*/
            /*some extra processing is needed and therefore pawn makes the move itself*/
            /*This is because of how pawn always called complete before*/
            completemove(mov, board);
			/*move completed*/
			return 1;
		}
        else if (tmp == 2)
        {
            /*two step move*/
            return 1;
        }
		/*invalid move*/
		return 0;
	}
	else if (piece == wKnight || piece == bKnight) {
		if (knight(mov, board)) {
            completemove(mov, board);
			/*move completed*/
			return 1;
		}
		/*invalid move*/
		return 0;
	}
	else if (piece == wBishop || piece == bBishop) {
		if (bishop(mov, board)) {
            completemove(mov, board);
			/*move completed*/
			return 1;
		}
        /*invalid move*/
        return 0;
	}
	else if (piece == wRook || piece == bRook) {
		if (rook(mov, board)) {
            completemove(mov, board);
			/*move completed*/
			return 1;
		}
        /*invalid move*/
        return 0;
	}
	else if (piece == wQueen || piece == bQueen) {
		if (queen(mov, board)) {
            completemove(mov, board);
			/*move completed*/
			return 1;
		}
        /*invalid move*/
        return 0;
	}
	else if (piece == wKing || piece == bKing) {
		if (king(mov, board)) {
            completemove(mov, board);
			/*move completed*/
			return 1;
		}
        /*invalid move*/
        return 0;
	}
    /* invalid move */
    return 0;
}

int checkInput(struct Move mov) {
	/*check if the input coordinates is on board*/
	if ((mov.currRow >= 0 && mov.currRow < 8) ) {
		if (mov.currCol >= 0 && mov.currCol < 8) {
			if ((mov.nextRow >= 0 && mov.nextRow < 8) ) {
				if (mov.nextCol >= 0 && mov.nextCol < 8) {
					return 1;
				}
			}
		}
	}
	return 0;
}

int makemove(int player, struct Move mov, int board[][7])
{
	if (checkInput(mov)) {
		if (checkColor(mov, player, board)) {
			if (checkMove(mov, player, board)) {
				return 0;
			}
		}
	} 
	return 1;
}

/* 
 This method will move a piece from its
 current position to a new one
*/
void completemove(struct Move mov, int b[][8]) {
	b[mov.nextRow][mov.nextCol] = b[mov.currRow][mov.currCol];
	b[mov.currRow][mov.currCol] = 0;
	resetPassantArrays();
}
