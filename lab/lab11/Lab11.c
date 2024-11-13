#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct
{
	char name[20];
	int exam[2];
	float avg;
	char grade;
}STUDENT;

void print_one_student(STUDENT s, int no);
void print_students(STUDENT slist[], int n);
void add_student(STUDENT* p);

int main()
{
	STUDENT slist[10];
	char command[20];
	int idx = 0;
	char name[20];

	while (1)
	{
		printf(">> ");
		scanf("%s", command);

		if (strcmp(command, "add") == 0)
		{
			add_student(&slist[idx]);
			idx++;
		}
		else if (strcmp(command, "print") == 0)
		{
			print_students(slist, idx);
		}
		else if (strcmp(command, "find") == 0)
		{
			printf("이름: ");
			scanf("%s", name);

			int i = 0;
			while (strcmp(name, slist[i].name) != 0)
			{
				i++;

				if (i == 10)
				{
					printf("There's no student with that name here!");
					break;
				}
			}
			printf("번호   이름       중간   기말   평균  (학점)\n");
			print_one_student(slist[i], i + 1);
		}
		else if (strcmp(command, "quit") == 0)
		{
			break;
		}

		printf("\n");
	}

	return 0;
}

void print_one_student(STUDENT s, int no)
{
	printf("%d %9s %9d %6d %7.1f  (%c)", no, s.name, s.exam[0], s.exam[1], s.avg, s.grade);
}

void print_students(STUDENT slist[], int n)
{
	printf("번호   이름       중간   기말   평균  (학점)\n");
	int i;
	for (i = 0; i < n; i++)
	{
		print_one_student(slist[i], i + 1);
		printf("\n");
	}
}

void add_student(STUDENT* p)
{
	printf("이름: ");
	scanf("%s", p->name);
	printf("중간고사: ");
	scanf("%d", &p->exam[0]);
	printf("기말고사: ");
	scanf("%d", &p->exam[1]);

	p->avg = (p->exam[0] + p->exam[1]) / 2.0;

	if (p->avg >= 90)
	{
		p->grade = 'A';
	}
	else if (p->avg >= 80 && p->avg < 90)
	{
		p->grade = 'B';
	}
	else if (p->avg >= 70 && p->avg < 80)
	{
		p->grade = 'C';
	}
	else if (p->avg >= 60 && p->avg < 70)
	{
		p->grade = 'D';
	}
	else if (p->avg >= 50 && p->avg < 60)
	{
		p->grade = 'E';
	}
	else
	{
		p->grade = 'F';
	}
}