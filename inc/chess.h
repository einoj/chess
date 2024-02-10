// clang-format off
enum pieces { emptySquare,
    wPawn, wKnight, wBishop, wRook, wQueen, wKing,
    bPawn, bKnight, bBishop, bRook, bQueen, bKing
};
// clang-format on
enum players { white,
    black };
struct Square {
    unsigned char row;
    unsigned char col;
};
struct Move {
    unsigned char currRow;
    unsigned char currCol;
    unsigned char nextRow;
    unsigned char nextCol;
};
int makemove(int player, struct Move mov, int board[][8]);
int rook(struct Move mov, int board[][8]);
int knight(struct Move mov, int board[][8]);
int bishop(struct Move mov, int board[][8]);
int queen(struct Move mov, int board[][8]);
int king(int player, struct Move mov, int board[][8]);
int pawn(struct Move mov, int player, int board[][8]);
void initBoard(int tmpBoard[][8]);
int checkPosition(int row, int col, int b[][8]);
void setPassant(int column, int player);
int checkPassant(int row, int column, int player);
int squareUnderAttack(int player, struct Move mov, int board[][8]);
void resetPassantArrays();
void printBoard(int board[][8]);
void completemove(struct Move mov, int b[][8]);
int checkInput(struct Move mov);
int checkColor(struct Move mov, int player, int b[][8]);
