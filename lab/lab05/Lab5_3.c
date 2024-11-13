#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int num, i, k, sum;
	
	i = 10;
	sum = 0;

	printf("Enter a number: ");
	scanf("%d", &num);
	while (num>0)
	{
		k = num % 10;

		sum = sum + k;
		num = num / 10;
	}
	printf("The sum of the digits is %d", sum);

	return 0;
}