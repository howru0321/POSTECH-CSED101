#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


void randData(int* a, int* b, int* c);
float arithmeticMean(int a, int b);
float geometicMean(int a, int b);
float harmonicMean(int a, int b);

int main()
{
	int a, b, c, d, e, f;

	srand(time(NULL));
	randData(&a, &b, &c);
	randData(&d, &e, &f);

	printf("arithmeticMean(%d, %d) => %f\n", a, d, arithmeticMean(a, d));
	printf("geometicMean(%d, %d) => %f\n", b, e, geometicMean(b, e));
	printf("harmonicMean(%d, %d) => %f\n", c, f, harmonicMean(c, f));

	return 0;
}


void randData(int* a, int* b, int* c)
{
	*a = rand() % 81 + 5;
	*b = rand() % 81 + 5;
	*c = rand() % 81 + 5;
}

float arithmeticMean(int a, int b)
{
	return (a + (float)b) / 2;
}

float geometicMean(int a, int b)
{
	return sqrt(a * (float)b);
}

float harmonicMean(int a, int b)
{
	return 2 * a * (float)b / (a + b);
}