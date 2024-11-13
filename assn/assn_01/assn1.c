#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*개발환경 :  Windows Visual Studio 2019*/

int print_menu();/*첫 시작화면을 출력하는 함수*/
int game_info();/*게임 설명화면을 출력하는 함수*/
int game_start();/*게임이 실행되는 함수 여기에 모든 게임이 실행된다*/
void print_drink(int a, int b, int user_p);/*user과 computer의 주량을 출력하는 함수*/
void print_map(int user_pos);/*주루마블 보드를 출력하는 함수*/
void set_position(int user_pos, int pos);/*주르마블 보드에 말을 출력하는 함수. print_map함수 안에서 실행된다*/
int play_juru(int user_pos);/*각 칸의 룰을 이행하는 함수를 실행하게 하는 함수*/
void normal_space();/*일반칸의 룰을 이행하는 함수*/
void start_space();/*시작칸의 룰을 이행하는 함수*/
void rest_space();/*휴식칸의 룰을 이행하는 함수*/
int game_369();/*369게임을 실행하는 함수. mission_space함수 안에서 실행된다*/
int game_br31();/*베스킨라빈스 31 게임을 실행하는 함수. mission_space함수 안에서 실행된다*/
int mission_space();/*미션칸의 룰을 이행하는 함수*/
int chance_space();/*찬스칸의 룰을 이행하는 함수*/


int main()
{
	
	int a, b;
	a = print_menu();
	b = 0;

	srand(time(NULL));
	
	while (a != 3 || b != 1) /*a=3일때 while문의 반복을 멈추기 위해 switch문에서 case3일때 b값을 0에서 1로 바꾸어 while문을 break시킬수 있도록 하였다*/
	{
		if (a != 1 && a != 2 && a != 3)
		{
			system("cls");
			printf("메뉴를 다시 입력하세요.\n");
			a = print_menu();
		}
		


		switch (a)
		{
		case 1: a = game_info(); break;
		case 2: a = game_start(); break;
		case 3: printf("프로그램을 종료합니다...\n"); b = 1; break;
		default: break;
		}
	
	}/*여기까지 초기 화면*/

	

	

	return 0;
}

int print_menu() 
{
	int num;

	printf("[주루마블]\n");
	printf("=======================================\n");
	printf("     1. 게임 설명\n");
	printf("     2. 게임 시작\n");
	printf("     3. 게임 종료\n");
	printf("=======================================\n");
	printf("입력:");

	scanf("%d", &num);

	return num;
}

int game_info() 
{

	int num2, x;

	system("cls");/*게임 설명 화면*/

	printf("=============================== 주루마불 게임 설명 ===============================\n");
	printf("1. USER는 매턴 주사위를 던진다. 주사위를 던질 때 주사위의 눈은 플레이어가 결정한다.\n");
	printf("2. COMPUTER는 주사위를 던지지 않으며 매턴 1잔의 술을 마신다.\n");
	printf("3. USER와 COMPUTER의 주량은 소주 2병(14잔)이며, 14잔을 먼저 마신 쪽이 패배한다.\n");
	printf("4. 보드 칸은 5가지 칸으로 이루어져있으며 USER는 각 칸의 요구사항을 만족시켜야한다.\n");
	printf("==================================================================================\n");
	printf("메인 메뉴로 돌아가기(-1):\n");
	scanf("%d", &num2);

	if (num2 == -1)
	{
		system("cls");
		x = print_menu();/*다시 시작화면으로 가는 코드*/
	}
	return x;
}

int game_start()
{
	int x, di;/*di는 주사위 숫자*/
	int user_j = 0;/*user_j는 user가 마신 술의 횟수*/
	int comp_j = 0;/*comp_j는 comp가 마신 술의 횟수*/
	int rnd = 0;/*rnd는 진행된 라운드의 횟수*/
	int p = 0;
	int user_p = 0;/*user_p는 말의 위치*/
	int jh;/*jh는 play_juru의 return값을 받는 변수*/


	int cm=0;
	int stop;

	system("cls");

	printf("[주루마블 게임]\n");
	printf("=======================================\n");
	print_map(0);
	print_drink(0, 0, 0);/*게임 시작 하고 첫 실행화면을 나타내기 위해 말 위치, 마신 술 모두 0일때의 함수를 출력*/
	printf("주사위를 굴리시겠습니까? (0-굴림, -1-게임포기):\n");

	while (p != -1) 
	{
		scanf("%d", &p);

		while (1)
		{
			if (p == -1)
			{
				system("cls");
				x = print_menu();/*시작 화면으로 돌아감*/
				return x;
				break;
			}
			else if (p == 0)
			{
				di = rand() % 6 + 1;
				break;
			}
			else if (p >= 1 && p <= 6)
			{
				di = p;
				break;
			}
			else
			{
				scanf("%d", &p);
			}
		}

		/*여기서 부터 진짜 게임시작*/
		if (p == -1)
		{
			break;
		}

		else
		{
			rnd++;
			user_p = (user_p + di) % 12;/*한 바퀴 돌았을때를 감안해 12로 나눴을때의 나머지로 user_p를 설정함*/

			

			system("cls");

			printf("=======================================\n");
			printf("▶▶▶ ROUND %d ▶▶▶▶▶▶▶▶▶▶▶▶\n",rnd);
			printf("=======================================\n");
			printf("[USER’s Turn] \n");
			printf("---------------------------------------\n");
			printf("주사위 눈 : %d\n",di);
			printf("\n");
			
			print_map(user_p);

			jh = play_juru(user_p);/*각 칸에서 룰을 이행했을 시 play_juru함수에서 return 값을 받아 각 return값에 따라 user과 omputer이 술을 얼마나 마실지 판단*/
			
			if (jh == 0 && user_j != 13)
			{
				user_j++;

				comp_j++;
				cm = 1;

			}

			else if (jh == -1)
			{
				comp_j++;
				cm = 1;
			}
			else if (jh == 1)
			{
				comp_j = comp_j + 4;
				cm = 0;
			}
			else if (jh == 2)
			{
				user_j = user_j + 4;
				cm = 0;
			}
			else if (jh == 3 && user_j < 11)
			{
				user_j = user_j + 3;
				comp_j++;
				cm = 1;
			}

			else if (jh == 4)
			{
				user_j = user_j - 2;
				comp_j++;
				cm = 1;
			}

			else if (jh == 0 && user_j == 13)
			{
				user_j++;
			}

			else if (jh == 3 && user_j >= 11)
			{
				user_j = user_j + 3;
			}


			if (user_j < 0)
			{
				user_j = 0;/*user가 1잔 이하 마셨을때 여명 808 카드가 나오면 음수주량이 나오므로, 이 경우는 user_j=0이 되도록 하였다*/
			}

			if (user_j >= 14)
			{
				user_j = 14;/*14잔 이상 마셔도 14잔 마셨다고 출력되야 하므로 술 마신 값을 나타내는 변수가 14이상이면 모두 14로 설정*/
			}

			if (comp_j >= 14)
			{
				comp_j = 14;
			}


			if (user_j != 14)
			{
				printf("[COMPUTER’s Turn] \n");
				printf("---------------------------------------\n");
				printf("COMPUTER가 %d잔 마시게 되었습니다.\n", cm);
				printf("\n");
			}

			if (user_j == 14 || comp_j == 14)
			{
				printf("\n");
				printf("게임이 종료되었습니다.\n");
			}
			
			print_drink(user_j, comp_j, user_p);

			if (user_j < 14 && comp_j < 14)
			{
				printf("주사위를 굴리시겠습니까? (0-굴림, -1-게임포기):\n");
			}

			else if (user_j == 14)
			{
				printf("* 결과 COMPUTER가 승리하였습니다.\n");
				printf("\n");
				printf("메인 메뉴로 돌아가기(-1):");
				scanf("%d", &stop);

				
				if (stop == -1)
				{
					system("cls");
					x = print_menu();/*-1 누르면 시작화면 돌아감*/
					return x;
					break;
				}

				else
				{
					while (stop != -1)
					{
						scanf("%d", &stop);
					}
					system("cls");
					x = print_menu();/*시작화면 돌아감*/
					return x;
					break;
				}
			}

			else if (comp_j == 14)
			{
				printf("* 결과 USER가 승리하였습니다.\n");
				printf("\n");
				printf("메인 메뉴로 돌아가기(-1):");
				scanf("%d", &stop);


				if (stop == -1)
				{
					system("cls");
					x = print_menu();/*시작화면 돌아감*/
					return x;
					break;
				}

				else
				{
					while (stop != -1)
					{
						scanf("%d", &stop);
					}
					system("cls");
					x = print_menu();/*시작화면 돌아감*/
					return x;
					break;
				}
			}
			 
			
		}
		
	}
}

	

void print_drink(int a, int b, int user_p)
{
	int i, j, m, n;

	
	printf("=======================================\n");
	printf("[USER - %d] ( %d/14)\n", user_p, a);
	for (i = 0; i < a; i++)/*주량에 따라 검은 네모와 빈 네모를for 문으로 나타냄*/
	{
		printf("■");
	}
	for (j = 13; j >= a; j--)
	{
		printf("□");
	}
	
	printf("\n");
	printf("\n");

	printf("[COMP - 0] ( %d/14)\n", b);
	for (m = 0; m < b; m++)
	{
		printf("■");
	}
	for (n = 13; n >= b; n--)
	{
		printf("□");
	}
	printf("\n");
	printf("=======================================\n");
	printf("\n");
}

void print_map(int user_pos)
{
	printf("+--------+--------+--------+--------+\n");
	printf("| 미션 ");  set_position(user_pos, 9); printf(" | 찬스 "); set_position(user_pos, 8); printf(" | 일반 "); set_position(user_pos, 7); printf(" | 휴식 "); set_position(user_pos, 6); printf(" |\n");
	printf("+--------+--------+--------+--------+\n");
	printf("| 일반 ");  set_position(user_pos, 10); printf(" |                 | 일반 "); set_position(user_pos, 5); printf(" |\n");
	printf("+--------+                 +--------+\n");
	printf("| 일반 ");  set_position(user_pos, 11); printf(" |                 | 일반 "); set_position(user_pos, 4); printf(" |\n");
	printf("+--------+--------+--------+--------+\n");
	printf("| 시작 "); set_position(user_pos, 0); printf(" | 일반 "); set_position(user_pos, 1); printf(" | 찬스 "); set_position(user_pos, 2); printf(" | 미션 "); set_position(user_pos, 3); printf(" |\n");
	printf("+--------+--------+--------+--------+\n");
}

void set_position(int user_pos, int pos)/*char로 받지 않고 void로 받아 그대로 출력 되도록 함*/
{
	if (user_pos == pos)
	{
		printf("O");
	}
	else
	{
		printf(" ");
	}
}

int play_juru(int user_pos)/*각 칸에서 룰을 이행할 수 있도록 하는 함수*/
{
	int a;

	printf("\n");

	switch (user_pos)
	{
	case 1: normal_space(); a = 0; break;
	case 4: normal_space(); a = 0; break;
	case 5: normal_space(); a = 0; break;
	case 7: normal_space(); a = 0; break;
	case 10: normal_space(); a = 0; break;
	case 11: normal_space(); a = 0; break;
	case 0:start_space(); a = -1; break;
	case 6:rest_space(); a = -1; break;
	case 3:a = mission_space(); break;
	case 9:a = mission_space(); break;
	case 2:a = chance_space(); break;
	case 8:a = chance_space(); break;
	}

	return a;
}

void normal_space()/*일반 칸일때의 룰을 이행하는 함수*/
{
	printf("일반 칸에 도착하였습니다.\n");
	printf("USER가 1잔 마시게 되었습니다.\n");
	printf("\n");
}

void start_space()/*시작 칸일때의 룰을 이행하는 함수*/
{
	printf("시작 칸에 도착하였습니다.\n");
	printf("이번 턴은 아무것도 하지 않습니다.\n");
	printf("\n");
}

void rest_space()/*휴식 칸일때의 룰을 이행하는 함수*/
{
	printf("휴식 칸에 도착하였습니다.\n");
	printf("이번 턴은 아무것도 하지 않습니다.\n");
	printf("\n");
}

int game_369()/*369게임을 이행하는 함수*/
{
	int a;
	
	a = rand() % 2;/*a는 0또는 1을 랜덤으로 받게된다. 0일때는 computer가 먼저 시작, 1일때는 user가 먼저 시작되도록 한다*/

	int num = 1;
	int n;
	int user_n;

	int x = 0;
	if (a == 0)
	{
		while (1)
		{
			n = num % 10;
			if (n == 0 || n == 3 || n == 6 || n == 9)
			{
				printf("COMP >> 0\n");
			}
			else
			{
				printf("COMP >> %d\n", num);
			}

			if (num == 21)
			{
				printf("--------------------------------------\n");
				printf("USER가 승리하였습니다.\n");
				printf("COMPUTER가 4잔 마시게 되었습니다.\n");
				printf("\n");
				return 1;
				break;
			}
			num++;
			n = num % 10;
			printf("USER >> ");
			scanf("%d", &user_n);
			if ((user_n != num) && !(n == 0 || n == 3 || n == 6 || n == 9))
			{
				printf("--------------------------------------\n");
				printf("COMPUTER가 승리하였습니다.\n");
				printf("USER가 4잔 마시게 되었습니다.\n");
				printf("\n");
				return 2;
				break;

			}
			else if (n == 0 || n == 3 || n == 6 || n == 9)
			{
				if (user_n != 0)
				{
					printf("--------------------------------------\n");
					printf("COMPUTER가 승리하였습니다.\n");
					printf("USER가 4잔 마시게 되었습니다.\n");
					printf("\n");
					return 2;
					break;
				}
			}

			num++;

		}
	}
	else if (a == 1)
	{
		while (1)
		{
			n = num % 10;
			printf("USER >> ");
			scanf("%d", &user_n);
			if ((user_n != num) && !(n == 0 || n == 3 || n == 6 || n == 9))
			{
				printf("--------------------------------------\n");
				printf("COMPUTER가 승리하였습니다.\n");
				printf("USER가 4잔 마시게 되었습니다.\n");
				printf("\n");
				return 2;
				break;

			}
			else if (n == 0 || n == 3 || n == 6 || n == 9)
			{
				if (user_n != 0)
				{
					printf("--------------------------------------\n");
					printf("COMPUTER가 승리하였습니다.\n");
					printf("USER가 4잔 마시게 되었습니다.\n");
					printf("\n");
					return 2;
					break;
				}

			}
			else if (user_n == 21)
			{
				printf("--------------------------------------\n");
				printf("USER가 승리하였습니다.\n");
				printf("COMPUTER가 4잔 마시게 되었습니다.\n");
				printf("\n");
				return 1;
				break;
			}

			num++;



			n = num % 10;
			if (n == 0 || n == 3 || n == 6 || n == 9)
			{
				printf("COMP >> 0\n");
			}
			else
			{
				printf("COMP >> %d\n", num);
			}

			num++;

		}

	}
}/*return 값이 1이면 user 승리, 2면 computer 승리이다*/

int game_br31()/*베스킨라빈스 31게임을 이행하는 함수*/
{
	int a, b;
	
	a = rand() % 2;/*a는 0또는 1을 랜덤으로 받게된다. 0일때는 computer가 먼저 시작, 1일때는 user가 먼저 시작되도록 한다*/

	int j;
	int user_n;
	int i;
	int num = 0;
	if (a == 0)
	{
		while (1)
		{
			b = rand() % 3 + 1;/*computer가 자기 턴에서 1에서 3까지 랜덤으로 부를 수 있게 적어논 것*/
			printf("USER >> ");
			scanf("%d", &user_n);

			while (user_n > 3 || user_n < 1)
			{
				printf("WRONG INPUT!\n");
				printf("USER >> ");
				scanf("%d", &user_n);
			}

			num = num + user_n;
			if (num < 31)
			{
				for (i = 0; i < user_n; i++)
				{
					printf("%d ", num - user_n + i + 1);
				}
				printf("\n");
			}
			else
			{
				for (i = num - user_n + 1; i <= 31; i++)/*값이 31이 넘어가도 31까지만 출력될수 있도록 코딩 함*/
				{
					printf("%d ", i);
				}
				printf("\n");
				printf("--------------------------------------\n");
				printf("COMPUTER가 승리하였습니다.\n");
				printf("USER가 4잔 마시게 되었습니다.\n");
				printf("\n");
				return 2;
				break;
			}




			printf("COMP >> %d\n", b);
			num = num + b;

			if (num < 31)
			{
				for (j = 0; j < b; j++)
				{
					printf("%d ", num - b + j + 1);
				}
				printf("\n");
			}
			else
			{
				for (j = num - b + 1; j <= 31; j++)
				{
					printf("%d ", j);
				}
				printf("\n");
				printf("--------------------------------------\n");
				printf("USER가 승리하였습니다.\n");
				printf("COMPUTER가 4잔 마시게 되었습니다.\n");
				printf("\n");
				return 1;
				break;
			}


		}
	}


	else if (a == 1)
	{
		while (1)
		{
			b = rand() % 3 + 1;/*computer가 자기 턴에서 1에서 3까지 랜덤으로 부를 수 있게 적어논 것*/
			printf("COMP >> %d\n", b);
			num = num + b;

			if (num < 31)
			{
				for (j = 0; j < b; j++)
				{
					printf("%d ", num - b + j + 1);
				}
				printf("\n");
			}
			else
			{
				for (j = num - b + 1; j <= 31; j++)/*값이 31이 넘어가도 31까지만 출력될수 있도록 코딩 함*/
				{
					printf("%d ", j);
				}
				printf("\n");
				printf("--------------------------------------\n");
				printf("USER가 승리하였습니다.\n");
				printf("COMPUTER가 4잔 마시게 되었습니다.\n");
				printf("\n");
				return 1;
				break;
			}


			printf("USER >> ");
			scanf("%d", &user_n);

			while (user_n > 3 || user_n < 1)
			{
				printf("WRONG INPUT!\n");
				printf("USER >> ");
				scanf("%d", &user_n);
			}



			num = num + user_n;
			if (num < 31)
			{
				for (i = 0; i < user_n; i++)
				{
					printf("%d ", num - user_n + i + 1);
				}
				printf("\n");
			}
			else
			{
				for (j = num - user_n + 1; j <= 31; j++)
				{
					printf("%d ", j);
				}
				printf("\n");
				printf("--------------------------------------\n");
				printf("COMPUTER가 승리하였습니다.\n");
				printf("USER가 4잔 마시게 되었습니다.\n");
				printf("\n");
				return 2;
				break;
			}


		}
	}
}/*return 값이 1이면 user 승리, 2면 computer 승리이다*/

int mission_space()/*미션칸에서의 룰을 이행하는 함수(game_369,game_br31 함수가 포함되어 있다)*/
{
	int a;
	int b, c;
	
	a = rand() % 2;/*a는 0또는 1을 랜덤으로 받게된다. 0일때는 369게임을, 1일때는 베스킨라빈스31 게임이 실행되도록 한다*/
	if (a == 0)
	{
		printf("미션 칸에 도착하였습니다.\n");
		printf("369 게임이 선택되었습니다.\n");
		printf("---------------------------------------\n");
		printf("★★★★★     369 게임     ★★★★★\n");
		printf("---------------------------------------\n");
		b = game_369();

		if (b == 1)
		{
			return 1;
		}
		else if (b == 2)
		{
			return 2;
		}
	}
	else if (a == 1)
	{
		printf("미션 칸에 도착하였습니다.\n");
		printf("베스킨라빈스 게임이 선택되었습니다.\n");
		printf("---------------------------------------\n");
		printf("★★★★★ 베스킨라빈스 게임 ★★★★★\n");
		printf("---------------------------------------\n");
		b = game_br31();

		if (b == 1)
		{
			return 1;
		}
		else if (b == 2)
		{
			return 2;
		}
	}

}/*user 승리시 1을, computer 승리시 2를 return 한다*/

int chance_space()/*찬스칸의 룰을 이행하는 함수*/
{
	printf("찬스 칸에 도착하였습니다.\n");
	
	int a;
	a = rand() % 2;
	if (a == 0)
	{
		printf("'세잔 더!' 카드를 뽑았습니다.\n");
		printf("USER가 3잔 마시게 되었습니다.\n");
		printf("\n");

		return 3;
	}
	else if (a == 1)
	{
		printf("'여명 808' 카드를 뽑았습니다.\n");
		printf("USER가 -2잔 마시게 되었습니다.\n");
		printf("\n");

		return 4;
	}
	printf("\n");
}/*세잔 더 카드를 뽑으면 3을, 여명808 카드를 뽑으면 4를 return 한다*/
