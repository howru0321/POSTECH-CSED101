#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	double pi = 3.141592;
	double r;

	printf("반지름을 입력하시오:");
	scanf("%lf", &r);

	printf("원 둘레: %lf\n", 2 * pi * r);
	printf("원 넓이: %lf", pi * r * r);

	return 0;
}