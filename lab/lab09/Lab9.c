#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void partial_print(int* arr_start, int size);
int partial_sum(int* arr_start, int* arr_end);

int main()
{
	printf("Enter 10 elements of array: ");
	int i;
	int a[10] = { 0 };

	for (i = 0; i < 10; i++)
	{
		scanf("%d", a + i);
	}
	
	printf("Numbers that you enter are: ");
	partial_print(a, 10);
	printf("\n");

	printf("Enter the starting and ending index: ");
	
	int st, ed;
	scanf("%d %d", &st, &ed);

	printf("\n");

	printf("Sum from array[%d] to array[%d] is %d\n", st, ed, partial_sum(a + st, a + ed));
	printf("Partial array output: ");
	partial_print(a + st, ed - st + 1);

	return 0;
}

void partial_print(int* arr_start, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d ", *(arr_start + i));
	}
}

int partial_sum(int* arr_start, int* arr_end)
{
	int sum = 0;
	int i;
	for (i = 0; i < arr_end - arr_start + 1; i++)
	{
		sum += *(arr_start + i);
	}

	return sum;
}