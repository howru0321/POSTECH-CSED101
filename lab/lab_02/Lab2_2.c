#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	double pi = 3.141592;
	double r;

	printf("�������� �Է��Ͻÿ�:");
	scanf("%lf", &r);

	printf("�� �ѷ�: %lf\n", 2 * pi * r);
	printf("�� ����: %lf", pi * r * r);

	return 0;
}