#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 6


void bubble_sort(int a[], int size);
void input_array(int a[], int size);
void print_array(int a[], int size);
void swap(int* x, int* y);


int main()
{
	int arr[SIZE] = { 0 };
	printf("Input integer numbers to be sorted: ");
	input_array(arr, SIZE);

	printf("Unsorted: ");
	print_array(arr, SIZE);

	printf("----------------------------------\n");
	bubble_sort(arr, SIZE);
	printf("----------------------------------\n");

	printf(" Sorted: ");
	print_array(arr, SIZE);
	


	return 0;
}

void bubble_sort(int a[], int size)
{
	int i, j;
	for (i = 0; i < size-1; i++)
	{
		for (j = size - 1; j > i - 1; j--)
		{
			if (a[j] < a[j - 1])
			{
				swap(&a[j], &a[j - 1]);
			}
		}
		printf("[step %d]: ", i + 1);
		print_array(a, SIZE);
	}
}
void input_array(int a[], int size)
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		scanf("%d", &a[i]);
	}
}
void print_array(int a[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%4d", a[i]);
	}
	printf("\n");
}
void swap(int* x, int* y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}