#include <chess.h>

int knight(struct Move mov)
{
    if (mov.nextRow == mov.currRow + 1 && mov.nextCol == mov.currCol + 2) {
        /*move 1 north 2 east*/
        return 1;
    } else if (mov.nextRow == mov.currRow + 2 && mov.nextCol == mov.currCol + 1) {
        /*move 2 north 1 east*/
        return 1;
    } else if (mov.nextRow == mov.currRow + 2 && mov.nextCol == mov.currCol - 1) {
        /*move 2 north 1 west*/
        return 1;
    } else if (mov.nextRow == mov.currRow + 1 && mov.nextCol == mov.currCol - 2) {
        /*move 1 north 2 west*/
        return 1;
    } else if (mov.nextRow == mov.currRow - 1 && mov.nextCol == mov.currCol - 2) {
        /*move 1 south 2 west*/
        return 1;
    } else if (mov.nextRow == mov.currRow - 2 && mov.nextCol == mov.currCol - 1) {
        /*move 2 south 1 west*/
        return 1;
    } else if (mov.nextRow == mov.currRow - 2 && mov.nextCol == mov.currCol + 1) {
        /*move 2 south 1 east*/
        return 1;
    } else if (mov.nextRow == mov.currRow - 1 && mov.nextCol == mov.currCol + 2) {
        /*move 1 south 2 east*/
        return 1;
    }
    /*invalid move*/
    return 0;
}
