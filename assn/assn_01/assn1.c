#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*����ȯ�� :  Windows Visual Studio 2019*/

int print_menu();/*ù ����ȭ���� ����ϴ� �Լ�*/
int game_info();/*���� ����ȭ���� ����ϴ� �Լ�*/
int game_start();/*������ ����Ǵ� �Լ� ���⿡ ��� ������ ����ȴ�*/
void print_drink(int a, int b, int user_p);/*user�� computer�� �ַ��� ����ϴ� �Լ�*/
void print_map(int user_pos);/*�ַ縶�� ���带 ����ϴ� �Լ�*/
void set_position(int user_pos, int pos);/*�ָ����� ���忡 ���� ����ϴ� �Լ�. print_map�Լ� �ȿ��� ����ȴ�*/
int play_juru(int user_pos);/*�� ĭ�� ���� �����ϴ� �Լ��� �����ϰ� �ϴ� �Լ�*/
void normal_space();/*�Ϲ�ĭ�� ���� �����ϴ� �Լ�*/
void start_space();/*����ĭ�� ���� �����ϴ� �Լ�*/
void rest_space();/*�޽�ĭ�� ���� �����ϴ� �Լ�*/
int game_369();/*369������ �����ϴ� �Լ�. mission_space�Լ� �ȿ��� ����ȴ�*/
int game_br31();/*����Ų��� 31 ������ �����ϴ� �Լ�. mission_space�Լ� �ȿ��� ����ȴ�*/
int mission_space();/*�̼�ĭ�� ���� �����ϴ� �Լ�*/
int chance_space();/*����ĭ�� ���� �����ϴ� �Լ�*/


int main()
{
	
	int a, b;
	a = print_menu();
	b = 0;

	srand(time(NULL));
	
	while (a != 3 || b != 1) /*a=3�϶� while���� �ݺ��� ���߱� ���� switch������ case3�϶� b���� 0���� 1�� �ٲپ� while���� break��ų�� �ֵ��� �Ͽ���*/
	{
		if (a != 1 && a != 2 && a != 3)
		{
			system("cls");
			printf("�޴��� �ٽ� �Է��ϼ���.\n");
			a = print_menu();
		}
		


		switch (a)
		{
		case 1: a = game_info(); break;
		case 2: a = game_start(); break;
		case 3: printf("���α׷��� �����մϴ�...\n"); b = 1; break;
		default: break;
		}
	
	}/*������� �ʱ� ȭ��*/

	

	

	return 0;
}

int print_menu() 
{
	int num;

	printf("[�ַ縶��]\n");
	printf("=======================================\n");
	printf("     1. ���� ����\n");
	printf("     2. ���� ����\n");
	printf("     3. ���� ����\n");
	printf("=======================================\n");
	printf("�Է�:");

	scanf("%d", &num);

	return num;
}

int game_info() 
{

	int num2, x;

	system("cls");/*���� ���� ȭ��*/

	printf("=============================== �ַ縶�� ���� ���� ===============================\n");
	printf("1. USER�� ���� �ֻ����� ������. �ֻ����� ���� �� �ֻ����� ���� �÷��̾ �����Ѵ�.\n");
	printf("2. COMPUTER�� �ֻ����� ������ ������ ���� 1���� ���� ���Ŵ�.\n");
	printf("3. USER�� COMPUTER�� �ַ��� ���� 2��(14��)�̸�, 14���� ���� ���� ���� �й��Ѵ�.\n");
	printf("4. ���� ĭ�� 5���� ĭ���� �̷���������� USER�� �� ĭ�� �䱸������ �������Ѿ��Ѵ�.\n");
	printf("==================================================================================\n");
	printf("���� �޴��� ���ư���(-1):\n");
	scanf("%d", &num2);

	if (num2 == -1)
	{
		system("cls");
		x = print_menu();/*�ٽ� ����ȭ������ ���� �ڵ�*/
	}
	return x;
}

int game_start()
{
	int x, di;/*di�� �ֻ��� ����*/
	int user_j = 0;/*user_j�� user�� ���� ���� Ƚ��*/
	int comp_j = 0;/*comp_j�� comp�� ���� ���� Ƚ��*/
	int rnd = 0;/*rnd�� ����� ������ Ƚ��*/
	int p = 0;
	int user_p = 0;/*user_p�� ���� ��ġ*/
	int jh;/*jh�� play_juru�� return���� �޴� ����*/


	int cm=0;
	int stop;

	system("cls");

	printf("[�ַ縶�� ����]\n");
	printf("=======================================\n");
	print_map(0);
	print_drink(0, 0, 0);/*���� ���� �ϰ� ù ����ȭ���� ��Ÿ���� ���� �� ��ġ, ���� �� ��� 0�϶��� �Լ��� ���*/
	printf("�ֻ����� �����ðڽ��ϱ�? (0-����, -1-��������):\n");

	while (p != -1) 
	{
		scanf("%d", &p);

		while (1)
		{
			if (p == -1)
			{
				system("cls");
				x = print_menu();/*���� ȭ������ ���ư�*/
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

		/*���⼭ ���� ��¥ ���ӽ���*/
		if (p == -1)
		{
			break;
		}

		else
		{
			rnd++;
			user_p = (user_p + di) % 12;/*�� ���� ���������� ������ 12�� ���������� �������� user_p�� ������*/

			

			system("cls");

			printf("=======================================\n");
			printf("������ ROUND %d ������������������������\n",rnd);
			printf("=======================================\n");
			printf("[USER��s Turn] \n");
			printf("---------------------------------------\n");
			printf("�ֻ��� �� : %d\n",di);
			printf("\n");
			
			print_map(user_p);

			jh = play_juru(user_p);/*�� ĭ���� ���� �������� �� play_juru�Լ����� return ���� �޾� �� return���� ���� user�� omputer�� ���� �󸶳� ������ �Ǵ�*/
			
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
				user_j = 0;/*user�� 1�� ���� �������� ���� 808 ī�尡 ������ �����ַ��� �����Ƿ�, �� ���� user_j=0�� �ǵ��� �Ͽ���*/
			}

			if (user_j >= 14)
			{
				user_j = 14;/*14�� �̻� ���ŵ� 14�� ���̴ٰ� ��µǾ� �ϹǷ� �� ���� ���� ��Ÿ���� ������ 14�̻��̸� ��� 14�� ����*/
			}

			if (comp_j >= 14)
			{
				comp_j = 14;
			}


			if (user_j != 14)
			{
				printf("[COMPUTER��s Turn] \n");
				printf("---------------------------------------\n");
				printf("COMPUTER�� %d�� ���ð� �Ǿ����ϴ�.\n", cm);
				printf("\n");
			}

			if (user_j == 14 || comp_j == 14)
			{
				printf("\n");
				printf("������ ����Ǿ����ϴ�.\n");
			}
			
			print_drink(user_j, comp_j, user_p);

			if (user_j < 14 && comp_j < 14)
			{
				printf("�ֻ����� �����ðڽ��ϱ�? (0-����, -1-��������):\n");
			}

			else if (user_j == 14)
			{
				printf("* ��� COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("\n");
				printf("���� �޴��� ���ư���(-1):");
				scanf("%d", &stop);

				
				if (stop == -1)
				{
					system("cls");
					x = print_menu();/*-1 ������ ����ȭ�� ���ư�*/
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
					x = print_menu();/*����ȭ�� ���ư�*/
					return x;
					break;
				}
			}

			else if (comp_j == 14)
			{
				printf("* ��� USER�� �¸��Ͽ����ϴ�.\n");
				printf("\n");
				printf("���� �޴��� ���ư���(-1):");
				scanf("%d", &stop);


				if (stop == -1)
				{
					system("cls");
					x = print_menu();/*����ȭ�� ���ư�*/
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
					x = print_menu();/*����ȭ�� ���ư�*/
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
	for (i = 0; i < a; i++)/*�ַ��� ���� ���� �׸�� �� �׸�for ������ ��Ÿ��*/
	{
		printf("��");
	}
	for (j = 13; j >= a; j--)
	{
		printf("��");
	}
	
	printf("\n");
	printf("\n");

	printf("[COMP - 0] ( %d/14)\n", b);
	for (m = 0; m < b; m++)
	{
		printf("��");
	}
	for (n = 13; n >= b; n--)
	{
		printf("��");
	}
	printf("\n");
	printf("=======================================\n");
	printf("\n");
}

void print_map(int user_pos)
{
	printf("+--------+--------+--------+--------+\n");
	printf("| �̼� ");  set_position(user_pos, 9); printf(" | ���� "); set_position(user_pos, 8); printf(" | �Ϲ� "); set_position(user_pos, 7); printf(" | �޽� "); set_position(user_pos, 6); printf(" |\n");
	printf("+--------+--------+--------+--------+\n");
	printf("| �Ϲ� ");  set_position(user_pos, 10); printf(" |                 | �Ϲ� "); set_position(user_pos, 5); printf(" |\n");
	printf("+--------+                 +--------+\n");
	printf("| �Ϲ� ");  set_position(user_pos, 11); printf(" |                 | �Ϲ� "); set_position(user_pos, 4); printf(" |\n");
	printf("+--------+--------+--------+--------+\n");
	printf("| ���� "); set_position(user_pos, 0); printf(" | �Ϲ� "); set_position(user_pos, 1); printf(" | ���� "); set_position(user_pos, 2); printf(" | �̼� "); set_position(user_pos, 3); printf(" |\n");
	printf("+--------+--------+--------+--------+\n");
}

void set_position(int user_pos, int pos)/*char�� ���� �ʰ� void�� �޾� �״�� ��� �ǵ��� ��*/
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

int play_juru(int user_pos)/*�� ĭ���� ���� ������ �� �ֵ��� �ϴ� �Լ�*/
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

void normal_space()/*�Ϲ� ĭ�϶��� ���� �����ϴ� �Լ�*/
{
	printf("�Ϲ� ĭ�� �����Ͽ����ϴ�.\n");
	printf("USER�� 1�� ���ð� �Ǿ����ϴ�.\n");
	printf("\n");
}

void start_space()/*���� ĭ�϶��� ���� �����ϴ� �Լ�*/
{
	printf("���� ĭ�� �����Ͽ����ϴ�.\n");
	printf("�̹� ���� �ƹ��͵� ���� �ʽ��ϴ�.\n");
	printf("\n");
}

void rest_space()/*�޽� ĭ�϶��� ���� �����ϴ� �Լ�*/
{
	printf("�޽� ĭ�� �����Ͽ����ϴ�.\n");
	printf("�̹� ���� �ƹ��͵� ���� �ʽ��ϴ�.\n");
	printf("\n");
}

int game_369()/*369������ �����ϴ� �Լ�*/
{
	int a;
	
	a = rand() % 2;/*a�� 0�Ǵ� 1�� �������� �ްԵȴ�. 0�϶��� computer�� ���� ����, 1�϶��� user�� ���� ���۵ǵ��� �Ѵ�*/

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
				printf("USER�� �¸��Ͽ����ϴ�.\n");
				printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n");
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
				printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("USER�� 4�� ���ð� �Ǿ����ϴ�.\n");
				printf("\n");
				return 2;
				break;

			}
			else if (n == 0 || n == 3 || n == 6 || n == 9)
			{
				if (user_n != 0)
				{
					printf("--------------------------------------\n");
					printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
					printf("USER�� 4�� ���ð� �Ǿ����ϴ�.\n");
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
				printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("USER�� 4�� ���ð� �Ǿ����ϴ�.\n");
				printf("\n");
				return 2;
				break;

			}
			else if (n == 0 || n == 3 || n == 6 || n == 9)
			{
				if (user_n != 0)
				{
					printf("--------------------------------------\n");
					printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
					printf("USER�� 4�� ���ð� �Ǿ����ϴ�.\n");
					printf("\n");
					return 2;
					break;
				}

			}
			else if (user_n == 21)
			{
				printf("--------------------------------------\n");
				printf("USER�� �¸��Ͽ����ϴ�.\n");
				printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n");
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
}/*return ���� 1�̸� user �¸�, 2�� computer �¸��̴�*/

int game_br31()/*����Ų��� 31������ �����ϴ� �Լ�*/
{
	int a, b;
	
	a = rand() % 2;/*a�� 0�Ǵ� 1�� �������� �ްԵȴ�. 0�϶��� computer�� ���� ����, 1�϶��� user�� ���� ���۵ǵ��� �Ѵ�*/

	int j;
	int user_n;
	int i;
	int num = 0;
	if (a == 0)
	{
		while (1)
		{
			b = rand() % 3 + 1;/*computer�� �ڱ� �Ͽ��� 1���� 3���� �������� �θ� �� �ְ� ����� ��*/
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
				for (i = num - user_n + 1; i <= 31; i++)/*���� 31�� �Ѿ�� 31������ ��µɼ� �ֵ��� �ڵ� ��*/
				{
					printf("%d ", i);
				}
				printf("\n");
				printf("--------------------------------------\n");
				printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("USER�� 4�� ���ð� �Ǿ����ϴ�.\n");
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
				printf("USER�� �¸��Ͽ����ϴ�.\n");
				printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n");
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
			b = rand() % 3 + 1;/*computer�� �ڱ� �Ͽ��� 1���� 3���� �������� �θ� �� �ְ� ����� ��*/
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
				for (j = num - b + 1; j <= 31; j++)/*���� 31�� �Ѿ�� 31������ ��µɼ� �ֵ��� �ڵ� ��*/
				{
					printf("%d ", j);
				}
				printf("\n");
				printf("--------------------------------------\n");
				printf("USER�� �¸��Ͽ����ϴ�.\n");
				printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n");
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
				printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("USER�� 4�� ���ð� �Ǿ����ϴ�.\n");
				printf("\n");
				return 2;
				break;
			}


		}
	}
}/*return ���� 1�̸� user �¸�, 2�� computer �¸��̴�*/

int mission_space()/*�̼�ĭ������ ���� �����ϴ� �Լ�(game_369,game_br31 �Լ��� ���ԵǾ� �ִ�)*/
{
	int a;
	int b, c;
	
	a = rand() % 2;/*a�� 0�Ǵ� 1�� �������� �ްԵȴ�. 0�϶��� 369������, 1�϶��� ����Ų���31 ������ ����ǵ��� �Ѵ�*/
	if (a == 0)
	{
		printf("�̼� ĭ�� �����Ͽ����ϴ�.\n");
		printf("369 ������ ���õǾ����ϴ�.\n");
		printf("---------------------------------------\n");
		printf("�ڡڡڡڡ�     369 ����     �ڡڡڡڡ�\n");
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
		printf("�̼� ĭ�� �����Ͽ����ϴ�.\n");
		printf("����Ų��� ������ ���õǾ����ϴ�.\n");
		printf("---------------------------------------\n");
		printf("�ڡڡڡڡ� ����Ų��� ���� �ڡڡڡڡ�\n");
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

}/*user �¸��� 1��, computer �¸��� 2�� return �Ѵ�*/

int chance_space()/*����ĭ�� ���� �����ϴ� �Լ�*/
{
	printf("���� ĭ�� �����Ͽ����ϴ�.\n");
	
	int a;
	a = rand() % 2;
	if (a == 0)
	{
		printf("'���� ��!' ī�带 �̾ҽ��ϴ�.\n");
		printf("USER�� 3�� ���ð� �Ǿ����ϴ�.\n");
		printf("\n");

		return 3;
	}
	else if (a == 1)
	{
		printf("'���� 808' ī�带 �̾ҽ��ϴ�.\n");
		printf("USER�� -2�� ���ð� �Ǿ����ϴ�.\n");
		printf("\n");

		return 4;
	}
	printf("\n");
}/*���� �� ī�带 ������ 3��, ����808 ī�带 ������ 4�� return �Ѵ�*/
