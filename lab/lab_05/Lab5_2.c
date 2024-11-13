#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int i,j;

	for (i = 1; i <= 9; i++)
	{
		for (j = 2; j <= 9; j++)
		{
			printf("%d * %d = %2d  ", j, i, j * i);
		}
		printf("\n");
	}
}