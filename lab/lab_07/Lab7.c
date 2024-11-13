#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 10


int seqSearch(int arr[], int size, int number);


int main()
{
	int a[SIZE];
	int i;
	int num;
	int b;

	printf("Input 10 integer values: ");

	for (i = 0; i < SIZE; i++)
	{
		scanf("%d", &a[i]);
	}

	printf("Entered number is      :");

	for (i = 0; i < SIZE; i++)
	{
		printf("%d ", a[i]);
	}

	printf("\n");

	printf("Input an integer that you want to find: ");
	scanf("%d", &num);

	b = seqSearch(a, SIZE, num);

	if (b != -1)
	{
		printf("The index of %d is %d", num, b);
	}
	else
	{
		printf("Not Found");
	}

	return 0;
}

int seqSearch(int arr[], int size, int number)
{
	int i;
	int find;

	for (i = 0; i < size; i++)
	{
		if (arr[i] == number)
		{
			return i;
		}
	}
	
	if (i == size)
	{
		return -1;
	}
}