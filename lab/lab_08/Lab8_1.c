#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 20

void print_matrix(int a[MAX_SIZE][MAX_SIZE], int size);

int main()
{
	int arr[MAX_SIZE][MAX_SIZE] = { 0 };
	int num;

	printf("Enter the size of square: ");
	scanf("%d", &num);

	int i, j;

	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num; j++)
		{
			if (i + j == num-1)
			{
				arr[i][j] = 0;
			}
			else if (i + j < num-1)
			{
				arr[i][j] = 1;
			}
			else
			{
				arr[i][j] = -1;
			}
		}
	}

	print_matrix(arr, num);


	return 0;
}

void print_matrix(int a[MAX_SIZE][MAX_SIZE], int size)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			printf("%2d", a[i][j]);
		}
		printf("\n");
	}
}