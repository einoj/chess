#include <stdlib.h>
/*the guiMove takes move col*row instead of row*col*/
void cfrom(int right, int top, int *move) 
{
	move[0] = right-1;
	move[1] = top;
}

void cto(int right, int top, int *move) 
{
	move[2] = right-1;
	move[3] = top;
}
