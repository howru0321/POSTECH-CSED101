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


void print_user(LIST_USER* slist);//user 리스트 출력하는 함수
void read_user(FILE* user, LIST_USER* slist);//user리스트 읽는 함수
void dltetr(char* str);//문자열에 '\n'지워주는 함수
void asc_user(LIST_USER* slist);//slist의 이름을 오름차순으로 정렬하는 함수
void add_user(LIST_USER* slist, char* name, char* email);//학생을 list에 추가하는 함수
void dlt_user(LIST_USER* slist, USER* dlt_user);//원하는 학생을 list에 삭제하는 함수
void print_con(CONFERENCE* list);//회의 참여자 리스트를 출력하는 함수
void add_con(CONFERENCE* list, char* name);//회의 참여자 추가하는 함수
void hangup_con(CONFERENCE* list, PARTICIPANT* hgp_par);//회의 참여자 삭제하는 함수


int main()
{
	FILE* user;
	printf("유저 리스트 파일 이름을 입력해주세요. >> ");
	char filename[30];
	scanf("%s", filename); FLUSH;
	while ((user = fopen(filename, "r")) == NULL)//유효한 파일을 받을 때 까지 받기위한 while문
	{
		printf("유효하지 않은 입력입니다. 유저 리스트 파일 이름을 입력해주세요 >> ");
		scanf("%s", filename); FLUSH;
	}
	LIST_USER slist;
	slist.count = 0;
	slist.head = NULL;
	slist.tail = NULL;//slist 초기화
	CONFERENCE clist;
	clist.numParticipant = 0;
	clist.participant = NULL;//clist 초기화
	read_user(user, &slist);
	asc_user(&slist);//오름차순 정렬
	printf("\n");
	printf("[INFO] user.txt에서 총 %d명의 유저를 불러왔습니다.\n", slist.count);
	printf("\n");
	char room[22];//'\n'고려해서 22칸 잡았다
	printf("회의실 이름을 입력해주세요. >> ");
	fgets(room, sizeof(room), stdin);
	dltetr(room);
	strcpy(clist.roomName, room);
	printf("최대 사용자 수를 입력해주세요. >> ");
	int max_par;
	scanf("%d", &max_par); FLUSH;
	clist.maxParticipant = max_par;
	printf("[INFO] test 회의실이 생성되었습니다!\n");
	
	int conti = 0;
	char cmd[20];//가장 긴 명령어가 18자인데, '\n' '\0'고려해서 크기를 20으로잡았다
	while (1)
	{
		if (conti == 0)//잘못된 입력을 했을때 "유효하지 않은 입력입니다." 와 "명령어를 입력해주세요. >> "사이 '\n'가 출력되지 않도록 하는 알고리즘
		{
			printf("\n");
		}
		conti = 0;
		printf("명령어를 입력해주세요. >> ");
		fgets(cmd, 20, stdin);
		dltetr(cmd);

		if (strcmp(cmd, "user list") == 0)//user list 입력했을경우
		{
			print_user(&slist);
		}
		else if (strcmp(cmd, "user add") == 0)//user add입력했을 경우
		{
			char add_name[21];
			char add_email[41];
			USER* add_temp;
			add_temp = slist.head;
			printf("추가할 유저의 이름을 입력해주세요. >> ");
			scanf("%s", add_name); FLUSH;
			while (add_temp != NULL)
			{
				if (strcmp(add_temp->name, add_name) == 0)
				{
					printf("[INFO] %s, %s 유저가 이미 유저 리스트에 있습니다.\n", add_temp->name, add_temp->email);
					break;
				}
				add_temp = add_temp->next;//첫 노드부터 하나씩 넘어가면서 입력한 이름이 존재하는지 확인한다
			}
			if (add_temp != NULL)//add_temp가 NULL이 됐다는 것은 노드가 while문 끝까지 돌았다는 뜻이고 겹치지 않는다는 뜻. 따라서 NULL이 아니면 continue를 통해 다시 명령어를 입력받게 한다.
			{
				continue;
			}
			printf("추가할 유저의 이메일을 입력해주세요. >> ");
			scanf("%s", add_email); FLUSH;
			add_user(&slist, add_name, add_email);
			printf("[INFO] %s, %s 유저가 추가되었습니다.\n", add_name, add_email);
		}
		else if (strcmp(cmd, "user delete") == 0)//user delete입력한 경우
		{
			if (slist.head == NULL)
			{
				printf("[INFO] 유저 리스트가 비어 있습니다!\n");
				continue;
			}
			USER* dlt_temp;
			char dlt_name[21];
			printf("제거할 유저의 이름을 입력해주세요. >> ");
			scanf("%s", dlt_name); FLUSH;
			for (dlt_temp = slist.head; dlt_temp != NULL; dlt_temp = dlt_temp->next)//입력한 이름과 일치하는 이름을 가진 노드를 찾는 알고리즘
			{
				if (strcmp(dlt_temp->name, dlt_name) == 0)
				{
					break;
				}
			}
			if (dlt_temp == NULL)//dlt_user가 NULL이면 for 문 끝까지 돌았다는 뜻이므로 입력한 이름과 일치하는 노드가 없다는 뜻이므로 다시 명령어를 입력받는다
			{
				printf("[INFO] 해당 유저는 존재하지 않습니다!\n");
			}
			else
			{
				printf("%s, %s 유저를 제거하시겠습니까? (y/n) >> ", dlt_temp->name, dlt_temp->email);
				char yn_user;
				scanf("%c", &yn_user); FLUSH;
				if (yn_user == 'y')
				{
					printf("[INFO] %s, %s 유저를 제거하였습니다.\n", dlt_temp->name, dlt_temp->email);
					dlt_user(&slist, dlt_temp);
				}
				else if (yn_user == 'n')//n입력하면 다시 입력받는다
				{
					continue;
				}
			}
		}
		else if (strcmp(cmd, "conf info") == 0)//conf info입력한 경우
		{
			print_con(&clist);
		}
		else if (strcmp(cmd, "conf join") == 0)//conf join 입력한 경우
		{
			if (clist.maxParticipant == clist.numParticipant)//최대인원이 참여하고 있으면 이 if문을 돌지 못하고 다시 명령어를 입력받도록 하는 알고리즘
			{
				printf("[INFO] 회의에 최대 인원 %d 명이 참여하고 있습니다!\n", clist.maxParticipant);
				continue;
			}
			char add_con_name[21];
			PARTICIPANT* add_con_temp;
			USER* temp;
			temp = slist.head;
			add_con_temp = clist.participant;//시작노드
			printf("추가할 유저의 이름을 입력해주세요. >> ");
			scanf("%s", add_con_name); FLUSH;
			while (temp != NULL)//입력한 이름의 사람이 있는지 확인
			{
				if (strcmp(temp->name, add_con_name) == 0)
				{
					break;
				}
				temp = temp->next;
			}
			if (temp == NULL)//while문 다 돌아도 그 사람이 없으면 NULL이 된다
			{
				printf("[INFO] 해당 유저는 존재하지 않습니다!\n");
				continue;
			}
			while (add_con_temp != NULL)//회의에 그 사람이 존재하는 지 확인하는 알고리즘
			{
				if (temp == add_con_temp->user)
				{
					printf("[INFO] %s 이(가) 회의에 이미 참여했습니다!\n", add_con_temp->user->name);
					break;
				}
				add_con_temp = add_con_temp->next;//첫 노드부터 하나씩 넘어가면서 입력한 이름이 존재하는지 확인한다
			}
			if (add_con_temp != NULL)//회의에 사람이 있으면 break 에 의해 while문을 중간에 빠져나온다. 이때 명령어를 다시 입력받는다
			{
				continue;
			}
			char yn_cam;
			char yn_mic;
			printf("카메라를 켠 상태로 시작하시겠습니까? (y/n) >> ");
			scanf("%c", &yn_cam); FLUSH;
			printf("마이크를 켠 상태로 시작하시겠습니까? (y/n) >> ");
			scanf("%c", &yn_mic); FLUSH;
			add_con(&clist, temp, yn_cam, yn_mic);
			printf("[INFO] %s 이(가) 회의에 참여했습니다!\n", add_con_name);
		}
		else if (strcmp(cmd, "conf hangup") == 0)//conf hangup를 입력한 경우
		{
			if (clist.participant == NULL)//회의 참석자가 없는 경우. 이 경우는 다시 명령어를 입력받는다.
			{
				printf("[INFO] 회의 참석자가 없습니다.\n");
				continue;
			}
			char hgp_name[21];
			printf("제외할 유저의 이름을 입력해주세요. >> ");
			scanf("%s", hgp_name); FLUSH;
			PARTICIPANT* hgp_temp;
			hgp_temp = clist.participant;//시작 노드
			while (hgp_temp != NULL)//입력한 이름의 사람이 존재하는지 확인하는 알고리즘
			{
				if (strcmp(hgp_temp->user->name, hgp_name) == 0)
				{
					break;
				}
				hgp_temp = hgp_temp->next;
			}
			if (hgp_temp == NULL)//while문을 다 돌았다는 뜻. 이 경우에는 다시 명령어를입력받는다
			{
				printf("[INFO] 해당 유저는 회의에 존재하지 않습니다!\n");
				continue;
			}
			char yn_hgp;
			printf("정말로 회의에서 내보내시겠습니까? (y/n) >> ");
			scanf("%c", &yn_hgp); FLUSH;
			if (yn_hgp == 'y')
			{
				printf("[INFO] %s 이(가) 회의에서 나갔습니다!\n", hgp_name);
				hangup_con(&clist, hgp_temp);
			}
			else if (yn_hgp == 'n')//다시 명령어를 입력 받는다
			{
				continue;
			}
		}
		else if (strcmp(cmd, "conf toggle camera") == 0)//conf toggle camera를 입력한 경우
		{
			char cam_name[21];
			printf("카메라 상태를 변경할 유저의 이름을 입력해주세요. >> ");
			scanf("%s", cam_name); FLUSH;
			PARTICIPANT* cam_temp;
			cam_temp = clist.participant;//시작 노드
			while (cam_temp != NULL)//입력한 이름의 사람이 존재하는지 확인하는 알고리즘
			{
				if (strcmp(cam_temp->user->name, cam_name) == 0)
				{
					break;
				}
				cam_temp = cam_temp->next;
			}
			if (cam_temp == NULL)//while문을 다 돌았다는 뜻. 이 경우에는 다시 명령어를입력받는다
			{
				printf("[INFO] 해당 유저는 회의에 존재하지 않습니다!\n");
				continue;
			}
			if (cam_temp->camera == true)
			{
				cam_temp->camera = false;
				printf("[INFO] %s 의 카메라가 ON -> OFF 되었습니다!\n", cam_name);
			}
			else if (cam_temp->camera == false)
			{
				cam_temp->camera = true;
				printf("[INFO] %s 의 카메라가 OFF -> ON 되었습니다!\n", cam_name);
			}

		}
		else if (strcmp(cmd, "conf toggle mic") == 0)//conf toggle mic를 입력한 경우
		{
			char mic_name[21];
			printf("카메라 상태를 변경할 유저의 이름을 입력해주세요. >> ");
			scanf("%s", mic_name); FLUSH;
			PARTICIPANT* mic_temp;
			mic_temp = clist.participant;//시작 노드
			while (mic_temp != NULL)//입력한 이름의 사람이 존재하는지 확인하는 알고리즘
			{
				if (strcmp(mic_temp->user->name, mic_name) == 0)
				{
					break;
				}
				mic_temp = mic_temp->next;
			}
			if (mic_temp == NULL)//while문을 다 돌았다는 뜻. 이 경우에는 다시 명령어를입력받는다
			{
				printf("[INFO] 해당 유저는 회의에 존재하지 않습니다!\n");
				continue;
			}
			if (mic_temp->microphone == true)
			{
				mic_temp->microphone = false;
				printf("[INFO] %s 의 카메라가 ON -> OFF 되었습니다!\n", mic_name);
			}
			else if (mic_temp->microphone == false)
			{
				mic_temp->microphone = true;
				printf("[INFO] %s 의 카메라가 OFF -> ON 되었습니다!\n", mic_name);
			}
		}
		else if (strcmp(cmd, "quit") == 0)//quit를 입력한 경우
		{
			PARTICIPANT* quit_par;
			PARTICIPANT* quit_par_temp;
			for (quit_par = clist.participant; quit_par != NULL; quit_par = quit_par_temp)
			{
				quit_par_temp = quit_par->next;//free하기전에 quit_par의 다음 주소를 받아놔야 한다
				free(quit_par);
			}
			USER* quit_user;
			USER* quit_user_temp;
			for (quit_user = slist.head; quit_user != NULL; quit_user = quit_user_temp)
			{
				quit_user_temp = quit_user->next;//위와 같은 맥락이다
				free(quit_user);
			}
			return 0;
		}
		else//유효하지 않은 명령어를 입력한 경우. 이 경우는 명령어를 다시 입력받는다.
		{
			conti = 1;
			printf("유효하지 않은 입력입니다. ");
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
	if (list->participant == list->tail)//회의에 한명밖에 없는 경우. conference의 시작 정보와 종료 정보에 모두 NULL넣으면 된다
	{
		list->participant = NULL;
		list->tail = NULL;
		free(hgp_par);
	}
	else if (list->participant == hgp_par)//회의에 두 명이상이 있고, 삭제하고 싶은 노드가 첫 노드인 경우
	{
		list->participant = hgp_par->next;
		free(hgp_par);
	}
	else if (list->tail == hgp_par)//회의에 두 명 이상이 있고, 삭제하고 싶은 노드가 마지막 노드인 경우
	{
		temp->next = NULL;
		list->tail = temp;
		free(hgp_par);
	}
	else//회의에 두명 이상이 있고, 삭제하고 싶은 노드가 시작노드도 아니고 마지막 노드도 아닌경우
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
	temp->next = NULL;//temp 초기화
	list->numParticipant++;
	if (list->participant == NULL)//linked list에 단어가 하나도 없는 경우
	{
		list->participant = temp;
		list->tail = temp;
	}
	else//단어가 하나 이상 있는 경우
	{
		list->tail->next = temp;
		list->tail = temp;
	}//참여자 리스트 맨 뒤에만 추가하면 된다
}

void print_con(CONFERENCE* list)
{
	PARTICIPANT* temp;
	char cam[4];
	char mic[4];
	
	printf("\n");
	printf("회의실 이름: %s\n", list->roomName);
	printf("최대 사용자 수: %d\n", list->maxParticipant);
	printf("참여자 목록:\n");
	printf("================================================================================\n");
	printf("               이름                                   이메일    카메라    마이크\n");
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
	for (temp = slist->head; temp != NULL; temp = temp->next)//dlt_user가 head가 아니면 temp는 삭제하고 싶은 노드의 전 노드를 가리키는 알고리즘. dlt_user가 head인 경우는 temp가 필요가 없다
	{
		if (temp->next == dlt_user)
		{
			break;
		}
	}
	if (slist->head == slist->tail)//linked list에 한 단어밖에 없는 경우. 이경우에 단어를 삭제하면 head와 tail 모두 NULL값을 넣어줘야 한다
	{
		slist->head = NULL;
		slist->tail = NULL;
		free(dlt_user);
	}
	else if (slist->head == dlt_user)//두단어 이상이 존재하고, 삭제하고 싶은 노드가 첫 노드인 경우
	{
		slist->head = dlt_user->next;
		free(dlt_user);
	}
	else if (slist->tail == dlt_user)//두단어 이상이고, 삭제하고 싶은 노드가 끝 노드인 경우
	{
		temp->next = NULL;
		slist->tail = temp;
		free(dlt_user);
	}
	else//두단어 이상이고, 삭제하고 싶은 노드가 첫 노드도 아니고 끝 노드도 아닌 경우
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
	temp->next = NULL;//temp 초기화
	slist->count++;
	if (slist->head == NULL)//linked list에 단어가 하나도 없는 경우
	{
		slist->head = temp;
		slist->tail = temp;
	}
	else//단어가 하나 이상 있는 경우
	{
		slist->tail->next = temp;
		slist->tail = temp;
	}
	asc_user(slist);//노드는 항상 linked list 끝에 추가하고, 나중에 오름차순 정렬을 한다
}

void asc_user(LIST_USER* slist)
{
	USER* temp1;
	USER* temp2;
	int max = slist->count;//user 수
	
	int i, j;
	for (i = 0; i < max - 1; i++)
	{
		temp1 = slist->head;
		temp2 = temp1->next;
		for (j = 0; j < max - i - 1; j++)
		{
			if (strcmp(temp1->name, temp2->name) > 0)//오름차순 정렬에 위배되는 경우
			{
				char name_temp[21];//name swap하는 알고리즘
				strcpy(name_temp, temp1->name);
				strcpy(temp1->name, temp2->name);
				strcpy(temp2->name, name_temp);
				char email_temp[41];//email swap하는 알고리즘
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
		if (slist->head == NULL)//첫 단어를 linked list에 넣는 경우
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
	printf("번호             이름                                   이메일\n");
	printf("--------------------------------------------------------------\n");
	for (temp = slist->head; temp != NULL; temp = temp->next)
	{
		i++;
		printf("%d%20s%40s\n", i, temp->name, temp->email);
	}
	printf("==============================================================\n");
}