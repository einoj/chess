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
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    int expected_board[8][8] = {
        {bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight, bRook},
        {bPawn, bPawn, bPawn, 0, bPawn, bPawn, bPawn, bPawn},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, bPawn, 0, 0, 0, 0},
        {0, 0, 0, wPawn, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {wPawn, wPawn, wPawn, 0, wPawn, wPawn, wPawn, wPawn},
        {wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight, wRook}
    };
    TEST_ASSERT_EQUAL_MEMORY(expected_board, board, 64);
}

void test_scholars_mate_wc2023_gangulyVmadaminow(void)
{
    struct Move w_mov = {.currCol = ltoi('e'), .currRow = ltoi('2'), .nextCol = ltoi('e'), .nextRow = ltoi('4')};
    struct Move b_mov = {.currCol = ltoi('e'), .currRow = ltoi('7'), .nextCol = ltoi('e'), .nextRow = ltoi('5')};
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) {.currCol = ltoi('g'), .currRow = ltoi('1'), .nextCol = ltoi('f'), .nextRow = ltoi('3')};
    b_mov = (struct Move) {.currCol = ltoi('b'), .currRow = ltoi('8'), .nextCol = ltoi('c'), .nextRow = ltoi('6')};
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) {.currCol = ltoi('d'), .currRow = ltoi('2'), .nextCol = ltoi('d'), .nextRow = ltoi('4')};
    b_mov = (struct Move) {.currCol = ltoi('e'), .currRow = ltoi('5'), .nextCol = ltoi('d'), .nextRow = ltoi('4')};
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) {.currCol = ltoi('f'), .currRow = ltoi('3'), .nextCol = ltoi('d'), .nextRow = ltoi('4')};
    b_mov = (struct Move) {.currCol = ltoi('d'), .currRow = ltoi('8'), .nextCol = ltoi('f'), .nextRow = ltoi('6')};
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) {.currCol = ltoi('d'), .currRow = ltoi('4'), .nextCol = ltoi('f'), .nextRow = ltoi('3')};
    b_mov = (struct Move) {.currCol = ltoi('f'), .currRow = ltoi('8'), .nextCol = ltoi('b'), .nextRow = ltoi('4')};
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) {.currCol = ltoi('c'), .currRow = ltoi('2'), .nextCol = ltoi('c'), .nextRow = ltoi('3')};
    b_mov = (struct Move) {.currCol = ltoi('b'), .currRow = ltoi('4'), .nextCol = ltoi('c'), .nextRow = ltoi('5')};
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) {.currCol = ltoi('f'), .currRow = ltoi('1'), .nextCol = ltoi('d'), .nextRow = ltoi('3')};
    b_mov = (struct Move) {.currCol = ltoi('c'), .currRow = ltoi('6'), .nextCol = ltoi('e'), .nextRow = ltoi('5')};
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    w_mov = (struct Move) {.currCol = ltoi('f'), .currRow = ltoi('3'), .nextCol = ltoi('e'), .nextRow = ltoi('5')};
    b_mov = (struct Move) {.currCol = ltoi('f'), .currRow = ltoi('6'), .nextCol = ltoi('e'), .nextRow = ltoi('5')};
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(0, w_mov, board), "White Move");
    TEST_ASSERT_EQUAL_MESSAGE(0, makemove(1, b_mov, board), "Black Move");
    int expected_board[8][8] = {
        {bRook, 0, bBishop, 0, bKing, 0, bKnight, bRook},
        {bPawn, bPawn, bPawn, bPawn, 0, bPawn, bPawn, bPawn},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, bBishop, 0, wKnight, 0, 0, 0},
        {0, 0, 0, 0, wPawn, 0, 0, 0},
        {0, 0, wPawn, wBishop, 0, 0, 0, 0},
        {wPawn, wPawn, 0, 0, 0, bQueen, wPawn, wPawn},
        {wRook, wKnight, wBishop, wQueen, wKing, 0, 0, wRook}
    };
    TEST_ASSERT_EQUAL_MEMORY(expected_board, board, 64);
}

void test_false_moves(void)
{
    int expected_board[8][8];
    initBoard(expected_board);
    struct Move w_mov = {.currCol = ltoi('e'), .currRow = ltoi('1'), .nextCol = ltoi('d'), .nextRow = ltoi('3')};
    struct Move b_mov = {.currCol = ltoi('h'), .currRow = ltoi('8'), .nextCol = ltoi('h'), .nextRow = ltoi('4')};
    TEST_ASSERT_EQUAL_MESSAGE(1, makemove(0, w_mov, board), "White king e1 to d3 two squares through pawn");
    TEST_ASSERT_EQUAL_MESSAGE(1, makemove(1, b_mov, board), "Black rook h8 to h4 through pawn");
    w_mov = (struct Move) {.currCol = ltoi('b'), .currRow = ltoi('1'), .nextCol = ltoi('a'), .nextRow = ltoi('9')};
    b_mov = (struct Move) {.currCol = ltoi('d'), .currRow = ltoi('8'), .nextCol = ltoi('b'), .nextRow = ltoi('6')};
    TEST_ASSERT_EQUAL_MESSAGE(1, makemove(0, w_mov, board), "White knight v1 to a9 outside board.");
    TEST_ASSERT_EQUAL_MESSAGE(1, makemove(1, b_mov, board), "Black queen d8 to b6 through pawn.");
    w_mov = (struct Move) {.currCol = ltoi('c'), .currRow = ltoi('1'), .nextCol = ltoi('c'), .nextRow = ltoi('4')};
    b_mov = (struct Move) {.currCol = ltoi('f'), .currRow = ltoi('7'), .nextCol = ltoi('f'), .nextRow = ltoi('4')};
    TEST_ASSERT_EQUAL_MESSAGE(1, makemove(0, w_mov, board), "White bishop c1 to c4 moves like a rook through pawn");
    TEST_ASSERT_EQUAL_MESSAGE(1, makemove(1, b_mov, board), "Black pawn f7 to f4 moves one square too far");

    TEST_ASSERT_EQUAL_MEMORY(expected_board, board, 64);
}

int main(void)
{
  UnityBegin("test/TestProductionCode.c");
  RUN_TEST(test_d2d4_opening, 1);
  RUN_TEST(test_scholars_mate_wc2023_gangulyVmadaminow, 2);
  RUN_TEST(test_false_moves, 3);

  return (UnityEnd());
}
