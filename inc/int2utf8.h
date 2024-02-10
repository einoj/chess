/*takes a number 0-12 and converts it to unicode chess piece or blank square*/
char* convertClipieceToGuiPiece(int cliPiece)
{
    if (cliPiece == 1) {
        return "♙";
    } else if (cliPiece == 2) {
        return "♘";
    } else if (cliPiece == 3) {
        return "♗";
    } else if (cliPiece == 4) {
        return "♖";
    }
    /*queen*/
    else if (cliPiece == 5) {
        return "♕";
    }
    /*king*/
    else if (cliPiece == 6) {
        return "♔";
    } else if (cliPiece == 7) {
        return "♟";
    } else if (cliPiece == 8) {
        return "♞";
    } else if (cliPiece == 9) {
        return "♝";
    } else if (cliPiece == 10) {
        return "♜";
    }
    /*queen*/
    else if (cliPiece == 11) {
        return "♛";
    }
    /*king*/
    else if (cliPiece == 12) {
        return "♚";
    } else {
        return "";
    }
}
