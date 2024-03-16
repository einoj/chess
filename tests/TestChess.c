#include "chess.h"
#include "letterToInt.h"
#include "unity.h"

static int board[8][8];
void setUp(void)
{
    /* This is run before EACH TEST */
    initBoard(board);
}

void tearDown(void)
{
}

void test_d2d4_opening(void)
{
    struct Move w_mov = {
        .currCol = ltoi('d'), .currRow = ltoi('2'), .nextCol = ltoi('d'), .nextRow = ltoi('4')
    };
    struct Move b_mov = {
        .currCol = ltoi('d'), .currRow = ltoi('7'), .nextCol = ltoi('d'), .nextRow = ltoi('5')
    };
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    int expected_board[8][8] = {
        { bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight, bRook },
        { bPawn, bPawn, bPawn, 0, bPawn, bPawn, bPawn, bPawn },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, bPawn, 0, 0, 0, 0 },
        { 0, 0, 0, wPawn, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { wPawn, wPawn, wPawn, 0, wPawn, wPawn, wPawn, wPawn },
        { wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight, wRook }
    };
    TEST_ASSERT_EQUAL_MEMORY(expected_board, board, 64);
}

void test_scholars_mate_wc2023_gangulyVmadaminow(void)
{
    struct Move w_mov = { .currCol = ltoi('e'), .currRow = ltoi('2'), .nextCol = ltoi('e'), .nextRow = ltoi('4') };
    struct Move b_mov = { .currCol = ltoi('e'), .currRow = ltoi('7'), .nextCol = ltoi('e'), .nextRow = ltoi('5') };
    TEST_ASSERT_EQUAL(1, checkInput(w_mov));
    TEST_ASSERT_EQUAL(1, checkInput(b_mov));
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) { .currCol = ltoi('g'), .currRow = ltoi('1'), .nextCol = ltoi('f'), .nextRow = ltoi('3') };
    b_mov = (struct Move) { .currCol = ltoi('b'), .currRow = ltoi('8'), .nextCol = ltoi('c'), .nextRow = ltoi('6') };
    TEST_ASSERT_EQUAL(1, checkInput(w_mov));
    TEST_ASSERT_EQUAL(1, checkInput(b_mov));
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) { .currCol = ltoi('d'), .currRow = ltoi('2'), .nextCol = ltoi('d'), .nextRow = ltoi('4') };
    b_mov = (struct Move) { .currCol = ltoi('e'), .currRow = ltoi('5'), .nextCol = ltoi('d'), .nextRow = ltoi('4') };
    TEST_ASSERT_EQUAL(1, checkInput(w_mov));
    TEST_ASSERT_EQUAL(1, checkInput(b_mov));
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) { .currCol = ltoi('f'), .currRow = ltoi('3'), .nextCol = ltoi('d'), .nextRow = ltoi('4') };
    b_mov = (struct Move) { .currCol = ltoi('d'), .currRow = ltoi('8'), .nextCol = ltoi('f'), .nextRow = ltoi('6') };
    TEST_ASSERT_EQUAL(1, checkInput(w_mov));
    TEST_ASSERT_EQUAL(1, checkInput(b_mov));
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) { .currCol = ltoi('d'), .currRow = ltoi('4'), .nextCol = ltoi('f'), .nextRow = ltoi('3') };
    b_mov = (struct Move) { .currCol = ltoi('f'), .currRow = ltoi('8'), .nextCol = ltoi('b'), .nextRow = ltoi('4') };
    TEST_ASSERT_EQUAL(1, checkInput(w_mov));
    TEST_ASSERT_EQUAL(1, checkInput(b_mov));
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) { .currCol = ltoi('c'), .currRow = ltoi('2'), .nextCol = ltoi('c'), .nextRow = ltoi('3') };
    b_mov = (struct Move) { .currCol = ltoi('b'), .currRow = ltoi('4'), .nextCol = ltoi('c'), .nextRow = ltoi('5') };
    TEST_ASSERT_EQUAL(1, checkInput(w_mov));
    TEST_ASSERT_EQUAL(1, checkInput(b_mov));
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) { .currCol = ltoi('f'), .currRow = ltoi('1'), .nextCol = ltoi('d'), .nextRow = ltoi('3') };
    b_mov = (struct Move) { .currCol = ltoi('c'), .currRow = ltoi('6'), .nextCol = ltoi('e'), .nextRow = ltoi('5') };
    TEST_ASSERT_EQUAL(1, checkInput(w_mov));
    TEST_ASSERT_EQUAL(1, checkInput(b_mov));
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) { .currCol = ltoi('f'), .currRow = ltoi('3'), .nextCol = ltoi('e'), .nextRow = ltoi('5') };
    b_mov = (struct Move) { .currCol = ltoi('f'), .currRow = ltoi('6'), .nextCol = ltoi('e'), .nextRow = ltoi('5') };
    TEST_ASSERT_EQUAL(1, checkInput(w_mov));
    TEST_ASSERT_EQUAL(1, checkInput(b_mov));
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    int expected_board[8][8] = {
        { bRook, 0, bBishop, 0, bKing, 0, bKnight, bRook },
        { bPawn, bPawn, bPawn, bPawn, 0, bPawn, bPawn, bPawn },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, bBishop, 0, wKnight, 0, 0, 0 },
        { 0, 0, 0, 0, wPawn, 0, 0, 0 },
        { 0, 0, wPawn, wBishop, 0, 0, 0, 0 },
        { wPawn, wPawn, 0, 0, 0, bQueen, wPawn, wPawn },
        { wRook, wKnight, wBishop, wQueen, wKing, 0, 0, wRook }
    };
    TEST_ASSERT_EQUAL_MEMORY(expected_board, board, 64);
}

void test_false_moves(void)
{
    int expected_board[8][8];
    initBoard(expected_board);
    struct Move w_mov = { .currCol = ltoi('e'), .currRow = ltoi('1'), .nextCol = ltoi('d'), .nextRow = ltoi('3') };
    struct Move b_mov = { .currCol = ltoi('h'), .currRow = ltoi('8'), .nextCol = ltoi('h'), .nextRow = ltoi('4') };
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White king e1 to d3 two squares through pawn");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black rook h8 to h4 through pawn");
    w_mov = (struct Move) { .currCol = ltoi('b'), .currRow = ltoi('1'), .nextCol = ltoi('a'), .nextRow = ltoi('9') };
    b_mov = (struct Move) { .currCol = ltoi('d'), .currRow = ltoi('8'), .nextCol = ltoi('b'), .nextRow = ltoi('6') };
    TEST_ASSERT_EQUAL_MESSAGE(0, checkInput(w_mov), "White move outside board.");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White knight v1 to a9 outside board.");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black queen d8 to b6 through pawn.");
    w_mov = (struct Move) { .currCol = ltoi('c'), .currRow = ltoi('1'), .nextCol = ltoi('c'), .nextRow = ltoi('4') };
    b_mov = (struct Move) { .currCol = ltoi('f'), .currRow = ltoi('7'), .nextCol = ltoi('f'), .nextRow = ltoi('4') };
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White bishop c1 to c4 moves like a rook through pawn");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black pawn f7 to f4 moves one square too far");
    w_mov = (struct Move) { .currCol = ltoi('e'), .currRow = ltoi('1'), .nextCol = ltoi('e'), .nextRow = ltoi('2') };
    b_mov = (struct Move) { .currCol = ltoi('e'), .currRow = ltoi('8'), .nextCol = ltoi('e'), .nextRow = ltoi('7') };
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White king e1 to e2 captures white pawn");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black king e8 to e7 captures black pawn");

    TEST_ASSERT_EQUAL_MEMORY(expected_board, board, 64);
}

void test_moves_outside_board(void)
{
    struct Move currRow_outside = { .currCol = ltoi('a'), .currRow = -1, .nextCol = ltoi('a'), .nextRow = ltoi('1') };
    struct Move currCol_outside = { .currCol = 9, .currRow = ltoi('8'), .nextCol = ltoi('h'), .nextRow = ltoi('4') };
    struct Move nextRow_outside = { .currCol = ltoi('a'), .currRow = ltoi('1'), .nextCol = ltoi('a'), .nextRow = 12 };
    struct Move nextCol_outside = { .currCol = ltoi('a'), .currRow = ltoi('8'), .nextCol = -1, .nextRow = ltoi('8') };
    TEST_ASSERT_EQUAL(0, checkInput(currRow_outside));
    TEST_ASSERT_EQUAL(0, checkInput(currCol_outside));
    TEST_ASSERT_EQUAL(0, checkInput(nextRow_outside));
    TEST_ASSERT_EQUAL(0, checkInput(nextCol_outside));
}

void test_king_cannot_move_to_square_uder_attack(void)
{
    int custom_board[8][8] = {
        { bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight, bRook },
        { bPawn, bPawn, bPawn, 0, bPawn, bPawn, bPawn, bPawn },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, wKing, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { wPawn, wPawn, wPawn, 0, wPawn, wPawn, wPawn, wPawn },
        { wRook, wKnight, wBishop, wQueen, 0, wBishop, wKnight, wRook }
    };
    struct Move mov = { .currCol = ltoi('d'), .currRow = ltoi('5'), .nextCol = ltoi('d'), .nextRow = ltoi('6') };
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(white, mov, custom_board), "White king moved to d6 which is under attack");
    mov = (struct Move) { .currCol = ltoi('d'), .currRow = ltoi('5'), .nextCol = ltoi('c'), .nextRow = ltoi('5') };
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, makemove(white, mov, custom_board), "White king can't move to d4.");
    mov = (struct Move) { .currCol = ltoi('c'), .currRow = ltoi('5'), .nextCol = ltoi('c'), .nextRow = ltoi('6') };
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(white, mov, custom_board), "White king moved to c4, which is under attack by a pawn");
}

void test_checkInput(void)
{
    struct Move move = { .currCol = -1, .currRow = -2, .nextCol = -3, .nextRow = -4 };
    TEST_ASSERT_EQUAL_MESSAGE(0, checkInput(move), "Negative numbers are illegal, but were excepted");
}

void test_pgnParser(void)
{
    pgnParser("gameDB/wang_arngrimsson_2008.pgn");
}

void test_black_attacking_black(void)
{
    struct Move mov;
    convertAlgNotation("Ra7", black, board, &mov);
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(black, mov, board), "Black rook killed a black pawn.");
}

void test_white_attacking_white(void)
{
    struct Move mov;
    convertAlgNotation("Ra2", white, board, &mov);
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(white, mov, board), "White rook killed a white pawn.");
}

int main(void)
{
    UnityBegin("Test chess.c");
    RUN_TEST(test_d2d4_opening, 1);
    RUN_TEST(test_scholars_mate_wc2023_gangulyVmadaminow, 2);
    RUN_TEST(test_false_moves, 3);
    RUN_TEST(test_moves_outside_board, 4);
    RUN_TEST(test_king_cannot_move_to_square_uder_attack, 5);
    RUN_TEST(test_checkInput, 6);
    RUN_TEST(test_pgnParser, 6);
    RUN_TEST(test_black_attacking_black, 7);
    RUN_TEST(test_white_attacking_white, 8);

    return (UnityEnd());
}
