#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


void find_minmax(int* arr, int size, int* max, int* min);

int main()
{
	int size;
	int* ptr;
	int max;
	int min;


	printf("Enter array size: ");
	scanf("%d", &size);

	ptr = (int*)malloc(sizeof(int) * size);

	int i;

	for (i = 0; i < size; i++)
	{
		scanf("%d", &ptr[i]);
	}

	printf("Entered numbers are\n");
	for (i = 0; i < size; i++)
	{
		printf("%d ", ptr[i]);
	}
	printf("\n");

	find_minmax(ptr, size, &max, &min);

	printf("Maximum is %d\n", max);
	printf("Minimum is %d\n", min);

	free(ptr);

	printf("\n");




	printf("Enter changed array size: ");
	scanf("%d", &size);

	ptr = (int*)calloc(size, sizeof(int));


	for (i = 0; i < size; i++)
	{
		scanf("%d", &ptr[i]);
	}

	printf("Entered numbers are\n");
	for (i = 0; i < size; i++)
	{
		printf("%d ", ptr[i]);
	}
	printf("\n");

	find_minmax(ptr, size, &max, &min);

	printf("Maximum is %d\n", max);
	printf("Minimum is %d\n", min);


	free(ptr);



	return 0;
}

void find_minmax(int* arr, int size, int* max, int* min)
{
	int i;
	*max = *arr;
	*min = *arr;

	for (i = 0; i < size; i++)
	{
		if (*max <= arr[i])
		{
			*max = arr[i];
		}
		if (*min >= arr[i])
		{
			*min = arr[i];
		}
	}
}