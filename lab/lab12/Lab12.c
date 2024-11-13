#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	char name[20];
	int exam[2];
	float avg;
	char grade;
}STUDENT;

typedef struct node
{
	STUDENT data;
	struct node* next;
}NODE;

typedef struct
{
	int count;
	NODE* head;
	NODE* tail;
}LIST;

void print_list(LIST* plist);
void insert_node(LIST* plist);
void print_one_student(STUDENT s, int no);
void add_student(STUDENT* p);

int main()
{
	
	char command[20];
	LIST slist;

	slist.count = 0;
	slist.head = NULL;
	slist.tail = NULL;
	char name[20];

	while (1)
	{
		printf(">> ");
		scanf("%s", command);

		if (strcmp(command, "add") == 0)
		{
			insert_node(&slist);
		}
		else if (strcmp(command, "print") == 0)
		{
			printf("번호   이름       중간   기말   평균  (학점)\n");
			print_list(&slist);
		}
		else if (strcmp(command, "find") == 0)
		{
			printf("이름: ");
			scanf("%s", name);

			int i = 0;
			NODE* temp;
			temp = slist.head;
			while (strcmp(name, temp->data.name) != 0)
			{
				i++;
				temp = temp->next;

				if (i == 10)
				{
					printf("There's no student with that name here!");
					break;
				}
			}
			printf("번호   이름       중간   기말   평균  (학점)\n");
			print_one_student(temp->data, i + 1);
		}
		else if (strcmp(command, "quit") == 0)
		{
			break;
		}

		printf("\n");
	}
	
	return 0;
}

void print_list(LIST* plist)
{
	NODE* temp;
	int i = 0;
	for (temp = plist->head; temp != NULL; temp = temp->next)
	{
		i++;
		print_one_student(temp->data, i);
	}
}

void insert_node(LIST* plist)
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->next = NULL;
	add_student(&temp->data);
	if (plist->head == NULL)
	{
		plist->head = temp;
	}
	else
	{
		plist->tail->next = temp;
	}
	plist->tail = temp;
	plist->count++;
}

void print_one_student(STUDENT s, int no)
{
	printf("%d %9s %9d %6d %7.1f  (%c)\n", no, s.name, s.exam[0], s.exam[1], s.avg, s.grade);
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