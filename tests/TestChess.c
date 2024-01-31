#include "chess.h"
#include "letterToInt.h"
#include "unity.h"

void setUp(void)
{
  /* This is run before EACH TEST */
}

void tearDown(void)
{
}

void test_d2d4_opening(void)
{
	int board[8][8];
	initBoard(board);
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

int main(void)
{
  UnityBegin("test/TestProductionCode.c");
  RUN_TEST(test_d2d4_opening, 21);

  return (UnityEnd());
}
