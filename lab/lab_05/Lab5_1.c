#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


float calc_average(float a, float b);
char calc_grade(float avg);


int main()
{
	float sc1, sc2, avg;

	printf("Enter your midterm score: ");
	scanf("%f", &sc1);
	printf("Enter your final score: ");
	scanf("%f", &sc2);

	avg = calc_average(sc1, sc2);

	printf("Average: %.1f\n", avg);
	printf("Grade: %c", calc_grade(avg));

	return 0;
}

float calc_average(float a, float b)
{
	return (a + b) / 2;
}

char calc_grade(float avg)
{
	char grd;
	if (avg > 90)
		grd = 'A';
	else if (avg > 70 && avg <= 80)
		grd = 'B';
	else if (avg > 60 && avg <= 70)
		grd = 'C';
	else if (avg > 50 && avg <= 60)
		grd = 'D';
	else
		grd = 'E';

	return grd;
}