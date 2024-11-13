#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define FLUSH while (getchar() != '\n')

typedef struct User {
	char name[21];
	char email[41];
	struct User* next;
}USER;

typedef struct Participant {
	USER* user;
	bool camera;
	bool microphone;
	struct Participant* next;
}PARTICIPANT;

typedef struct Conference {
	char roomName[21];
	int numParticipant;
	int maxParticipant;
	PARTICIPANT* participant;
	PARTICIPANT* tail;
}CONFERENCE;

typedef struct {
	int count;
	USER* head;
	USER* tail;
}LIST_USER;


void print_user(LIST_USER* slist);//user ����Ʈ ����ϴ� �Լ�
void read_user(FILE* user, LIST_USER* slist);//user����Ʈ �д� �Լ�
void dltetr(char* str);//���ڿ��� '\n'�����ִ� �Լ�
void asc_user(LIST_USER* slist);//slist�� �̸��� ������������ �����ϴ� �Լ�
void add_user(LIST_USER* slist, char* name, char* email);//�л��� list�� �߰��ϴ� �Լ�
void dlt_user(LIST_USER* slist, USER* dlt_user);//���ϴ� �л��� list�� �����ϴ� �Լ�
void print_con(CONFERENCE* list);//ȸ�� ������ ����Ʈ�� ����ϴ� �Լ�
void add_con(CONFERENCE* list, char* name);//ȸ�� ������ �߰��ϴ� �Լ�
void hangup_con(CONFERENCE* list, PARTICIPANT* hgp_par);//ȸ�� ������ �����ϴ� �Լ�


int main()
{
	FILE* user;
	printf("���� ����Ʈ ���� �̸��� �Է����ּ���. >> ");
	char filename[30];
	scanf("%s", filename); FLUSH;
	while ((user = fopen(filename, "r")) == NULL)//��ȿ�� ������ ���� �� ���� �ޱ����� while��
	{
		printf("��ȿ���� ���� �Է��Դϴ�. ���� ����Ʈ ���� �̸��� �Է����ּ��� >> ");
		scanf("%s", filename); FLUSH;
	}
	LIST_USER slist;
	slist.count = 0;
	slist.head = NULL;
	slist.tail = NULL;//slist �ʱ�ȭ
	CONFERENCE clist;
	clist.numParticipant = 0;
	clist.participant = NULL;//clist �ʱ�ȭ
	read_user(user, &slist);
	asc_user(&slist);//�������� ����
	printf("\n");
	printf("[INFO] user.txt���� �� %d���� ������ �ҷ��Խ��ϴ�.\n", slist.count);
	printf("\n");
	char room[22];//'\n'����ؼ� 22ĭ ��Ҵ�
	printf("ȸ�ǽ� �̸��� �Է����ּ���. >> ");
	fgets(room, sizeof(room), stdin);
	dltetr(room);
	strcpy(clist.roomName, room);
	printf("�ִ� ����� ���� �Է����ּ���. >> ");
	int max_par;
	scanf("%d", &max_par); FLUSH;
	clist.maxParticipant = max_par;
	printf("[INFO] test ȸ�ǽ��� �����Ǿ����ϴ�!\n");
	
	int conti = 0;
	char cmd[20];//���� �� ��ɾ 18���ε�, '\n' '\0'����ؼ� ũ�⸦ 20������Ҵ�
	while (1)
	{
		if (conti == 0)//�߸��� �Է��� ������ "��ȿ���� ���� �Է��Դϴ�." �� "��ɾ �Է����ּ���. >> "���� '\n'�� ��µ��� �ʵ��� �ϴ� �˰���
		{
			printf("\n");
		}
		conti = 0;
		printf("��ɾ �Է����ּ���. >> ");
		fgets(cmd, 20, stdin);
		dltetr(cmd);

		if (strcmp(cmd, "user list") == 0)//user list �Է��������
		{
			print_user(&slist);
		}
		else if (strcmp(cmd, "user add") == 0)//user add�Է����� ���
		{
			char add_name[21];
			char add_email[41];
			USER* add_temp;
			add_temp = slist.head;
			printf("�߰��� ������ �̸��� �Է����ּ���. >> ");
			scanf("%s", add_name); FLUSH;
			while (add_temp != NULL)
			{
				if (strcmp(add_temp->name, add_name) == 0)
				{
					printf("[INFO] %s, %s ������ �̹� ���� ����Ʈ�� �ֽ��ϴ�.\n", add_temp->name, add_temp->email);
					break;
				}
				add_temp = add_temp->next;//ù ������ �ϳ��� �Ѿ�鼭 �Է��� �̸��� �����ϴ��� Ȯ���Ѵ�
			}
			if (add_temp != NULL)//add_temp�� NULL�� �ƴٴ� ���� ��尡 while�� ������ ���Ҵٴ� ���̰� ��ġ�� �ʴ´ٴ� ��. ���� NULL�� �ƴϸ� continue�� ���� �ٽ� ��ɾ �Է¹ް� �Ѵ�.
			{
				continue;
			}
			printf("�߰��� ������ �̸����� �Է����ּ���. >> ");
			scanf("%s", add_email); FLUSH;
			add_user(&slist, add_name, add_email);
			printf("[INFO] %s, %s ������ �߰��Ǿ����ϴ�.\n", add_name, add_email);
		}
		else if (strcmp(cmd, "user delete") == 0)//user delete�Է��� ���
		{
			if (slist.head == NULL)
			{
				printf("[INFO] ���� ����Ʈ�� ��� �ֽ��ϴ�!\n");
				continue;
			}
			USER* dlt_temp;
			char dlt_name[21];
			printf("������ ������ �̸��� �Է����ּ���. >> ");
			scanf("%s", dlt_name); FLUSH;
			for (dlt_temp = slist.head; dlt_temp != NULL; dlt_temp = dlt_temp->next)//�Է��� �̸��� ��ġ�ϴ� �̸��� ���� ��带 ã�� �˰���
			{
				if (strcmp(dlt_temp->name, dlt_name) == 0)
				{
					break;
				}
			}
			if (dlt_temp == NULL)//dlt_user�� NULL�̸� for �� ������ ���Ҵٴ� ���̹Ƿ� �Է��� �̸��� ��ġ�ϴ� ��尡 ���ٴ� ���̹Ƿ� �ٽ� ��ɾ �Է¹޴´�
			{
				printf("[INFO] �ش� ������ �������� �ʽ��ϴ�!\n");
			}
			else
			{
				printf("%s, %s ������ �����Ͻðڽ��ϱ�? (y/n) >> ", dlt_temp->name, dlt_temp->email);
				char yn_user;
				scanf("%c", &yn_user); FLUSH;
				if (yn_user == 'y')
				{
					printf("[INFO] %s, %s ������ �����Ͽ����ϴ�.\n", dlt_temp->name, dlt_temp->email);
					dlt_user(&slist, dlt_temp);
				}
				else if (yn_user == 'n')//n�Է��ϸ� �ٽ� �Է¹޴´�
				{
					continue;
				}
			}
		}
		else if (strcmp(cmd, "conf info") == 0)//conf info�Է��� ���
		{
			print_con(&clist);
		}
		else if (strcmp(cmd, "conf join") == 0)//conf join �Է��� ���
		{
			if (clist.maxParticipant == clist.numParticipant)//�ִ��ο��� �����ϰ� ������ �� if���� ���� ���ϰ� �ٽ� ��ɾ �Է¹޵��� �ϴ� �˰���
			{
				printf("[INFO] ȸ�ǿ� �ִ� �ο� %d ���� �����ϰ� �ֽ��ϴ�!\n", clist.maxParticipant);
				continue;
			}
			char add_con_name[21];
			PARTICIPANT* add_con_temp;
			USER* temp;
			temp = slist.head;
			add_con_temp = clist.participant;//���۳��
			printf("�߰��� ������ �̸��� �Է����ּ���. >> ");
			scanf("%s", add_con_name); FLUSH;
			while (temp != NULL)//�Է��� �̸��� ����� �ִ��� Ȯ��
			{
				if (strcmp(temp->name, add_con_name) == 0)
				{
					break;
				}
				temp = temp->next;
			}
			if (temp == NULL)//while�� �� ���Ƶ� �� ����� ������ NULL�� �ȴ�
			{
				printf("[INFO] �ش� ������ �������� �ʽ��ϴ�!\n");
				continue;
			}
			while (add_con_temp != NULL)//ȸ�ǿ� �� ����� �����ϴ� �� Ȯ���ϴ� �˰���
			{
				if (temp == add_con_temp->user)
				{
					printf("[INFO] %s ��(��) ȸ�ǿ� �̹� �����߽��ϴ�!\n", add_con_temp->user->name);
					break;
				}
				add_con_temp = add_con_temp->next;//ù ������ �ϳ��� �Ѿ�鼭 �Է��� �̸��� �����ϴ��� Ȯ���Ѵ�
			}
			if (add_con_temp != NULL)//ȸ�ǿ� ����� ������ break �� ���� while���� �߰��� �������´�. �̶� ��ɾ �ٽ� �Է¹޴´�
			{
				continue;
			}
			char yn_cam;
			char yn_mic;
			printf("ī�޶� �� ���·� �����Ͻðڽ��ϱ�? (y/n) >> ");
			scanf("%c", &yn_cam); FLUSH;
			printf("����ũ�� �� ���·� �����Ͻðڽ��ϱ�? (y/n) >> ");
			scanf("%c", &yn_mic); FLUSH;
			add_con(&clist, temp, yn_cam, yn_mic);
			printf("[INFO] %s ��(��) ȸ�ǿ� �����߽��ϴ�!\n", add_con_name);
		}
		else if (strcmp(cmd, "conf hangup") == 0)//conf hangup�� �Է��� ���
		{
			if (clist.participant == NULL)//ȸ�� �����ڰ� ���� ���. �� ���� �ٽ� ��ɾ �Է¹޴´�.
			{
				printf("[INFO] ȸ�� �����ڰ� �����ϴ�.\n");
				continue;
			}
			char hgp_name[21];
			printf("������ ������ �̸��� �Է����ּ���. >> ");
			scanf("%s", hgp_name); FLUSH;
			PARTICIPANT* hgp_temp;
			hgp_temp = clist.participant;//���� ���
			while (hgp_temp != NULL)//�Է��� �̸��� ����� �����ϴ��� Ȯ���ϴ� �˰���
			{
				if (strcmp(hgp_temp->user->name, hgp_name) == 0)
				{
					break;
				}
				hgp_temp = hgp_temp->next;
			}
			if (hgp_temp == NULL)//while���� �� ���Ҵٴ� ��. �� ��쿡�� �ٽ� ��ɾ�Է¹޴´�
			{
				printf("[INFO] �ش� ������ ȸ�ǿ� �������� �ʽ��ϴ�!\n");
				continue;
			}
			char yn_hgp;
			printf("������ ȸ�ǿ��� �������ðڽ��ϱ�? (y/n) >> ");
			scanf("%c", &yn_hgp); FLUSH;
			if (yn_hgp == 'y')
			{
				printf("[INFO] %s ��(��) ȸ�ǿ��� �������ϴ�!\n", hgp_name);
				hangup_con(&clist, hgp_temp);
			}
			else if (yn_hgp == 'n')//�ٽ� ��ɾ �Է� �޴´�
			{
				continue;
			}
		}
		else if (strcmp(cmd, "conf toggle camera") == 0)//conf toggle camera�� �Է��� ���
		{
			char cam_name[21];
			printf("ī�޶� ���¸� ������ ������ �̸��� �Է����ּ���. >> ");
			scanf("%s", cam_name); FLUSH;
			PARTICIPANT* cam_temp;
			cam_temp = clist.participant;//���� ���
			while (cam_temp != NULL)//�Է��� �̸��� ����� �����ϴ��� Ȯ���ϴ� �˰���
			{
				if (strcmp(cam_temp->user->name, cam_name) == 0)
				{
					break;
				}
				cam_temp = cam_temp->next;
			}
			if (cam_temp == NULL)//while���� �� ���Ҵٴ� ��. �� ��쿡�� �ٽ� ��ɾ�Է¹޴´�
			{
				printf("[INFO] �ش� ������ ȸ�ǿ� �������� �ʽ��ϴ�!\n");
				continue;
			}
			if (cam_temp->camera == true)
			{
				cam_temp->camera = false;
				printf("[INFO] %s �� ī�޶� ON -> OFF �Ǿ����ϴ�!\n", cam_name);
			}
			else if (cam_temp->camera == false)
			{
				cam_temp->camera = true;
				printf("[INFO] %s �� ī�޶� OFF -> ON �Ǿ����ϴ�!\n", cam_name);
			}

		}
		else if (strcmp(cmd, "conf toggle mic") == 0)//conf toggle mic�� �Է��� ���
		{
			char mic_name[21];
			printf("ī�޶� ���¸� ������ ������ �̸��� �Է����ּ���. >> ");
			scanf("%s", mic_name); FLUSH;
			PARTICIPANT* mic_temp;
			mic_temp = clist.participant;//���� ���
			while (mic_temp != NULL)//�Է��� �̸��� ����� �����ϴ��� Ȯ���ϴ� �˰���
			{
				if (strcmp(mic_temp->user->name, mic_name) == 0)
				{
					break;
				}
				mic_temp = mic_temp->next;
			}
			if (mic_temp == NULL)//while���� �� ���Ҵٴ� ��. �� ��쿡�� �ٽ� ��ɾ�Է¹޴´�
			{
				printf("[INFO] �ش� ������ ȸ�ǿ� �������� �ʽ��ϴ�!\n");
				continue;
			}
			if (mic_temp->microphone == true)
			{
				mic_temp->microphone = false;
				printf("[INFO] %s �� ī�޶� ON -> OFF �Ǿ����ϴ�!\n", mic_name);
			}
			else if (mic_temp->microphone == false)
			{
				mic_temp->microphone = true;
				printf("[INFO] %s �� ī�޶� OFF -> ON �Ǿ����ϴ�!\n", mic_name);
			}
		}
		else if (strcmp(cmd, "quit") == 0)//quit�� �Է��� ���
		{
			PARTICIPANT* quit_par;
			PARTICIPANT* quit_par_temp;
			for (quit_par = clist.participant; quit_par != NULL; quit_par = quit_par_temp)
			{
				quit_par_temp = quit_par->next;//free�ϱ����� quit_par�� ���� �ּҸ� �޾Ƴ��� �Ѵ�
				free(quit_par);
			}
			USER* quit_user;
			USER* quit_user_temp;
			for (quit_user = slist.head; quit_user != NULL; quit_user = quit_user_temp)
			{
				quit_user_temp = quit_user->next;//���� ���� �ƶ��̴�
				free(quit_user);
			}
			return 0;
		}
		else//��ȿ���� ���� ��ɾ �Է��� ���. �� ���� ��ɾ �ٽ� �Է¹޴´�.
		{
			conti = 1;
			printf("��ȿ���� ���� �Է��Դϴ�. ");
			continue;
		}
	}

	return 0;
}

void hangup_con(CONFERENCE* list, PARTICIPANT* hgp_par)
{
	PARTICIPANT* temp;
	for (temp = list->participant; temp != NULL; temp = temp->next)
	{
		if (temp->next == hgp_par)
		{
			break;
		}
		
	}
	if (list->participant == list->tail)//ȸ�ǿ� �Ѹ�ۿ� ���� ���. conference�� ���� ������ ���� ������ ��� NULL������ �ȴ�
	{
		list->participant = NULL;
		list->tail = NULL;
		free(hgp_par);
	}
	else if (list->participant == hgp_par)//ȸ�ǿ� �� ���̻��� �ְ�, �����ϰ� ���� ��尡 ù ����� ���
	{
		list->participant = hgp_par->next;
		free(hgp_par);
	}
	else if (list->tail == hgp_par)//ȸ�ǿ� �� �� �̻��� �ְ�, �����ϰ� ���� ��尡 ������ ����� ���
	{
		temp->next = NULL;
		list->tail = temp;
		free(hgp_par);
	}
	else//ȸ�ǿ� �θ� �̻��� �ְ�, �����ϰ� ���� ��尡 ���۳�嵵 �ƴϰ� ������ ��嵵 �ƴѰ��
	{
		temp->next = hgp_par->next;
		free(hgp_par);
	}
	list->numParticipant--;
}

void add_con(CONFERENCE* list, USER* user, char cam, char mic)
{
	PARTICIPANT* temp = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));
	if (cam == 'y')
	{
		temp->camera = true;
	}
	else if (cam == 'n')
	{
		temp->camera = false;
	}
	if (mic == 'y')
	{
		temp->microphone = true;
	}
	else if (mic == 'n')
	{
		temp->microphone = false;
	}
	temp->user = user;
	temp->next = NULL;//temp �ʱ�ȭ
	list->numParticipant++;
	if (list->participant == NULL)//linked list�� �ܾ �ϳ��� ���� ���
	{
		list->participant = temp;
		list->tail = temp;
	}
	else//�ܾ �ϳ� �̻� �ִ� ���
	{
		list->tail->next = temp;
		list->tail = temp;
	}//������ ����Ʈ �� �ڿ��� �߰��ϸ� �ȴ�
}

void print_con(CONFERENCE* list)
{
	PARTICIPANT* temp;
	char cam[4];
	char mic[4];
	
	printf("\n");
	printf("ȸ�ǽ� �̸�: %s\n", list->roomName);
	printf("�ִ� ����� ��: %d\n", list->maxParticipant);
	printf("������ ���:\n");
	printf("================================================================================\n");
	printf("               �̸�                                   �̸���    ī�޶�    ����ũ\n");
	printf("--------------------------------------------------------------------------------\n");
	for (temp = list->participant; temp != NULL; temp = temp->next)
	{
		if (temp->camera == true)
		{
			strcpy(cam, "ON");
		}
		else if (temp->camera == false)
		{
			strcpy(cam, "OFF");
		}
		if (temp->microphone == true)
		{
			strcpy(mic, "ON");
		}
		else if (temp->microphone == false)
		{
			strcpy(mic, "OFF");
		}
		printf("%20s%40s%10s%10s\n", temp->user->name, temp->user->email, cam, mic);
	}
	printf("================================================================================\n");
}

void dlt_user(LIST_USER* slist, USER* dlt_user)
{
	USER* temp;
	for (temp = slist->head; temp != NULL; temp = temp->next)//dlt_user�� head�� �ƴϸ� temp�� �����ϰ� ���� ����� �� ��带 ����Ű�� �˰���. dlt_user�� head�� ���� temp�� �ʿ䰡 ����
	{
		if (temp->next == dlt_user)
		{
			break;
		}
	}
	if (slist->head == slist->tail)//linked list�� �� �ܾ�ۿ� ���� ���. �̰�쿡 �ܾ �����ϸ� head�� tail ��� NULL���� �־���� �Ѵ�
	{
		slist->head = NULL;
		slist->tail = NULL;
		free(dlt_user);
	}
	else if (slist->head == dlt_user)//�δܾ� �̻��� �����ϰ�, �����ϰ� ���� ��尡 ù ����� ���
	{
		slist->head = dlt_user->next;
		free(dlt_user);
	}
	else if (slist->tail == dlt_user)//�δܾ� �̻��̰�, �����ϰ� ���� ��尡 �� ����� ���
	{
		temp->next = NULL;
		slist->tail = temp;
		free(dlt_user);
	}
	else//�δܾ� �̻��̰�, �����ϰ� ���� ��尡 ù ��嵵 �ƴϰ� �� ��嵵 �ƴ� ���
	{
		temp->next = dlt_user->next;
		free(dlt_user);
	}
	slist->count--;
}

void add_user(LIST_USER* slist, char* name, char* email)
{
	USER* temp = (USER*)malloc(sizeof(USER));
	strcpy(temp->name, name);
	strcpy(temp->email, email);
	temp->next = NULL;//temp �ʱ�ȭ
	slist->count++;
	if (slist->head == NULL)//linked list�� �ܾ �ϳ��� ���� ���
	{
		slist->head = temp;
		slist->tail = temp;
	}
	else//�ܾ �ϳ� �̻� �ִ� ���
	{
		slist->tail->next = temp;
		slist->tail = temp;
	}
	asc_user(slist);//���� �׻� linked list ���� �߰��ϰ�, ���߿� �������� ������ �Ѵ�
}

void asc_user(LIST_USER* slist)
{
	USER* temp1;
	USER* temp2;
	int max = slist->count;//user ��
	
	int i, j;
	for (i = 0; i < max - 1; i++)
	{
		temp1 = slist->head;
		temp2 = temp1->next;
		for (j = 0; j < max - i - 1; j++)
		{
			if (strcmp(temp1->name, temp2->name) > 0)//�������� ���Ŀ� ����Ǵ� ���
			{
				char name_temp[21];//name swap�ϴ� �˰���
				strcpy(name_temp, temp1->name);
				strcpy(temp1->name, temp2->name);
				strcpy(temp2->name, name_temp);
				char email_temp[41];//email swap�ϴ� �˰���
				strcpy(email_temp, temp1->email);
				strcpy(temp1->email, temp2->email);
				strcpy(temp2->email, email_temp);
			}
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}
}

void dltetr(char* str)
{
	int i = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
		}
	}
}

void read_user(FILE* user, LIST_USER* slist)
{
	char line[62];
	while (fgets(line, sizeof(line), user) != NULL)
	{
		USER* temp = (USER*)malloc(sizeof(USER));
		temp->next = NULL;
		strcpy(temp->name, strtok(line, "\t"));
		strcpy(temp->email, strtok(NULL,"\n"));
		if (slist->head == NULL)//ù �ܾ linked list�� �ִ� ���
		{
			slist->head = temp;
		}
		else
		{
			slist->tail->next = temp;
		}
		slist->tail = temp;
		slist->count++;
	}
}

void print_user(LIST_USER* slist)
{
	USER* temp;
	int i = 0;
	printf("\n");
	printf("==============================================================\n");
	printf("��ȣ             �̸�                                   �̸���\n");
	printf("--------------------------------------------------------------\n");
	for (temp = slist->head; temp != NULL; temp = temp->next)
	{
		i++;
		printf("%d%20s%40s\n", i, temp->name, temp->email);
	}
	printf("==============================================================\n");
}