#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main()
{
	FILE* score,* report;

	int a, b, c;
	float sc;
	char grd;
	int n = 0;
	float adsc=0;
	float avgsc;
	int cnt = 0;;

	score = fopen("score.txt", "r");
	report = fopen("report.txt", "w");

	fprintf(report, "====================\n");
	fprintf(report, "�й�     ����(����)\n");
	fprintf(report, "====================\n");

	if (score == NULL)
	{
		printf("�� ���� Lab6���� ������� �ʽ��ϴ�.");
	}

	while (1)
	{
		n = fscanf(score, "%d %d %d", &a, &b, &c);
		if (n != 3)
		{
			break;
		}

		sc = (b * 0.4 + c * 0.6);
		if (sc >= 90)
		{
			grd = 'A';
		}
		else if (sc >= 80 && sc < 90)
		{
			grd = 'B';
		}
		else if (sc >= 70 && sc < 80)
		{
			grd = 'C';
		}
		else if (sc >= 60 && sc < 70)
		{
			grd = 'D';
		}
		else
		{
			grd = 'F';
		}
		
		fprintf(report, "%d     %.1f(%c)", a, sc, grd);
		fprintf(report, "\n");

		adsc = adsc + sc;
		cnt++;
	}
	avgsc = adsc / cnt;
	fprintf(report, "====================\n");
	fprintf(report, "    ���     %.1f\n", avgsc);
	fprintf(report, "====================\n");
	

	return 0;
}