#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


/*add(int x, int y);
average(float x, float y);
printResults(int x, int y, int sum, float avg);*/

int add(int x, int y)
{
	return x + y;
}

float average(float x, float y)
{
	return (x + y) / 2.0;
}

void printResults(int x, int y, int sum, float avg)
{
	printf("The sum of %d and %d is %d\n", x, y, sum);
	printf("The average of numbers is %.1f\n", avg);

	return 0;
}


int main()
{
	int x, y, sum;
	float avg;
	
	printf("Enter two integers:");
	scanf("%d %d", &x, &y);
	sum = add(x, y);
	avg = average(x, y);
	printResults(x, y, sum, avg);

	return 0;
}

