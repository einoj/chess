#include <chess.h>
#include <letterToInt.h>
#include <stdio.h>
#include <string.h>

int enPassantW[8], enPassantB[8];

void initBoard(int tmpBoard[][8])
{
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
void resetPassantArrays(void)
{
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
void setPassant(int column, int player)
{
    if (player == black) {
        enPassantB[column] = 1;
    } else {
        enPassantW[column] = 1;
    }
}

/* check if pessant jumped over the position last round.
 * Check the opposite color of the current player
 * Pawn must be on its fifth rank*/
int checkPassant(int row, int column, int player)
{
    if (player == white) {
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

int checkColor(struct Move mov, int player, int b[][8])
{
    int aPiece = b[mov.currRow][mov.currCol];
    int dPiece = b[mov.nextRow][mov.nextCol];
    if (dPiece == emptySquare)
        /* checkMove() checks if a piece is being moved so we chan return true from here */
        return 1;
    if ((player == white) && (wPawn <= aPiece && aPiece < bPawn) && (wKing < dPiece && dPiece <= bKing))
        /* player is white and attacking piece is white, and defending piece is black */
        return 1;
    if ((player == black) && (wKing < aPiece && aPiece <= bKing) && (wPawn <= dPiece && dPiece < bPawn))
        /* or player is black and attacking piece is black, and defending piece is white */
        return 1;
    return 0;
}

int checkMove(struct Move mov, int player, int board[][8])
{
    /*get the piece at the given coordinate*/
    int piece = board[mov.currRow][mov.currCol];
    if (piece == wPawn || piece == bPawn) {
        return pawn(mov, player, board);
    } else if (piece == wKnight || piece == bKnight) {
        return knight(mov);
    } else if (piece == wBishop || piece == bBishop) {
        return bishop(mov, board);
    } else if (piece == wRook || piece == bRook) {
        return rook(mov, board);
    } else if (piece == wQueen || piece == bQueen) {
        return queen(mov, board);
    } else if (piece == wKing || piece == bKing) {
        return king(player, mov, board);
    }
    /* invalid move */
    return 0;
}

int checkInput(struct Move mov)
{
    /*check if the input coordinates is on board*/
    if (mov.currRow > 8)
        return 0;
    if (mov.currCol > 8)
        return 0;
    if (mov.nextRow > 8)
        return 0;
    if (mov.nextCol > 8)
        return 0;
    return 1;
}

int makemove(int player, struct Move mov, int board[][8])
{
    if (checkInput(mov) == 0)
        return 0;
    if (checkColor(mov, player, board) == 0)
        return 0;
    int ret = checkMove(mov, player, board);
    if (ret == 0)
        return 0;
    completemove(mov, board);
    /* Set passant after the move is made
     * because completemove resets the passant arrays. */
    if (ret == 2)
        setPassant(mov.currCol, player);
    return 1;
}

/*
 This method will move a piece from its
 current position to a new one
*/
void completemove(struct Move mov, int b[][8])
{
    b[mov.nextRow][mov.nextCol] = b[mov.currRow][mov.currCol];
    b[mov.currRow][mov.currCol] = 0;
    resetPassantArrays();
}

void printBoard(int tmpBoard[][8])
{
    /*print out the current board and pieces*/
    int i, j;
    printf("\n ─────────────────────────\n");
    /*count down so white is south black is north*/
    for (i = 0; i < 8; ++i) {
        /*print edge of board*/
        printf("%d│", 8 - i);
        for (j = 0; j < 8; ++j) {
            switch (tmpBoard[i][j]) {
            case wPawn:
                printf(" ♙│");
                break;
            case bPawn:
                printf(" ♟│");
                break;
            case wKnight:
                printf("wN│");
                break;
            case bKnight:
                printf("bN│");
                break;
            case wBishop:
                printf("wB│");
                break;
            case bBishop:
                printf("bB│");
                break;
            case wRook:
                printf("wR│");
                break;
            case bRook:
                printf("bR│");
                break;
            case wQueen:
                printf("wQ│");
                break;
            case bQueen:
                printf("bQ│");
                break;
            case wKing:
                printf("wK│");
                break;
            case bKing:
                printf("bK│");
                break;
            default:
                printf("  │");
            }
        }
        printf("\n ─────────────────────────\n");
    }
    printf("   a  b  c  d  e  f  g  h \n");
}

int pgnParser(char* pathname)
{
    FILE* pgn_file = fopen(pathname, "r");
    char line[1024];
    char* p = NULL;
    char* white_move = NULL;
    char* black_move = NULL;
    while (fgets(line, 1024, pgn_file) != NULL) {
        p = strtok(line, " ");
        if (p[0] == '[')
            continue;
        while (p != NULL) {
            printf("%s ", p); /* your word */
            white_move = strtok(NULL, " ");
            if (white_move == NULL) {
                p = NULL;
                continue;
            }
            printf("white move: %s ", white_move);
            black_move = strtok(NULL, " ");
            if (black_move == NULL) {
                p = NULL;
                continue;
            }
            printf("black move: %s\n", black_move);
            p = strtok(NULL, " ");
        }
    }
    printf("\n "); /* your word */
}

int convertAlgNotation(char* token, int player, int board[][8], struct Move* mov)
{
    if (token[2] == 0) {
        // pawn move
        mov->nextCol = ltoi(token[0]);
        mov->nextRow = ltoi(token[1]);
        if (mov->nextCol == 42 || mov->nextRow == 42) {
            return -1;
        }
        if (player == white) {
            if (board[mov->nextRow + 1][mov->nextCol] == wPawn) {
                mov->currRow = mov->nextRow + 1;
                mov->currCol = mov->nextCol;
                return 0;
            } else if (board[mov->nextRow + 2][mov->nextCol] == wPawn) {
                mov->currRow = mov->nextRow + 2;
                mov->currCol = mov->nextCol;
                return 0;
            }
            return -1;
        } else {
            if (board[mov->nextRow - 1][mov->nextCol] == bPawn) {
                mov->currRow = mov->nextRow - 1;
                mov->currCol = mov->nextCol;
                return 0;
            } else if (board[mov->nextRow - 2][mov->nextCol] == bPawn) {
                mov->currRow = mov->nextRow - 2;
                mov->currCol = mov->nextCol;
                return 0;
            }
            return -1;
        }
        printf("%s\n", token);
    }

    int piece = emptySquare;
    if (token[0] == 'N') {
        if (player == white)
            piece = wKnight;
        else
            piece = bKnight;
    } else if (token[0] == 'Q') {
        if (player == white)
            piece = wQueen;
        else
            piece = bQueen;
    } else if (token[0] == 'K') {
        if (player == white)
            piece = wKing;
        else
            piece = bKing;
    } else if (token[0] == 'B') {
        if (player == white)
            piece = wBishop;
        else
            piece = bBishop;
    } else if (token[0] == 'R') {
        if (player == white)
            piece = wRook;
        else
            piece = bRook;
    } else if (token[1] == 'x') {
        // pawn capture
        mov->currCol = ltoi(token[0]);
        if (mov->currCol == 42)
            return -1;
        mov->nextCol = ltoi(token[2]);
        mov->nextRow = ltoi(token[3]);
        if (mov->nextCol == 42 || mov->nextRow == 42) {
            return -1;
        }
        if (player == white) {
            mov->currRow = mov->nextRow + 1;
        } else {
            mov->currRow = mov->nextRow - 1;
        }
    } else if (token[2] == '=') {
        // pawn promotion
    } else if (strncmp(token, "O-O", 3)) {
        // kingside castle
    } else if (strncmp(token, "O-O-O", 5)) {
    }

    // King, Queen, Rook, Knight or Bishop moving
    mov->nextCol = ltoi(token[1]);
    mov->nextRow = ltoi(token[2]);
    if (mov->nextCol == 42 || mov->nextRow == 42)
        return -1;
    // Looking through the whole board for now
    // Should probably optimize this at some point.
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == piece) {
                mov->currRow = i;
                mov->currCol = j;
                if (checkMove(*mov, player, board))
                    return 0;
            }
        }
    }
    return -1;
}
