#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define BOARD_SIZE 6



int start_game();//������ ����ȭ���� ȣ���ϴ� �Լ�
void print_board(int a[BOARD_SIZE][BOARD_SIZE], int score);//���� ����(2 ���� �迭) ���� ���޹޾� ����, ����, ������ ��� �� ��ȣ ����ϴ� �Լ�
void gaming(int a[BOARD_SIZE][BOARD_SIZE], int score, int turn, int b[BOARD_SIZE][BOARD_SIZE]);//���� ����ȭ�鿡�� ������ �ϴ� �Լ�
int check_position(int turn, int* A1, int* A2, int* B1, int* B2);//����� �Է��� �� ����� ��ġ�� ��ȿ���� �˻��ϴ� �Լ�
void swap(int* x, int* y);//���� 2���� �ٲ��ִ� �Լ�
void set_color_red();
void reset_color();
void print_board_red(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE], int score);//�ش����� ���������� ó���ϴ� �Լ�
int check_board(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE]);//���ӵ� ���ڸ� üũ�ϴ� �Լ�
void ini_board(int a[BOARD_SIZE][BOARD_SIZE]);//�Լ��� ��� ���� 0���� �ʱ�ȭ �ϴ� �Լ�
int sum_score(int b[BOARD_SIZE][BOARD_SIZE]);//�� ���� score�� ������ return�ϴ� �Լ�
void bingo_board(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE], int score);//��ġ�� ����� �����Ͽ� print�ϴ� �Լ�
void rand_board(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE], int score);//�� �ڸ��� �������� ���ڸ� ü���� print�ϴ� �Լ�


int main()
{
    srand(time(NULL));
    FILE* game_board;

    game_board = fopen("board.txt", "r");

    if (game_board == NULL)//board.txt�� ���ҽ� ���Ͽ� ���� ��� ������ ���� ������ �ߵ��� �ϴ� �˰���
    {
        printf("Could not open input file\n");

        return 100;
    }

    int board[BOARD_SIZE][BOARD_SIZE];

    int i, j;

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            fscanf(game_board, "%d", &board[i][j]);//board[][]�� board.txt�� �ִ� ���ڵ��� �Ű� ���� �˰���
        }
    }

    int score = 0;

    start_game();
    system("cls");//���� �������� ��Ÿ���� �ռ� �ռ� ȭ���� �� �����

    int turn = 5;

    int board_copy[BOARD_SIZE][BOARD_SIZE] = { 0 };


    for (turn = 5; turn > 0; turn--)//�� 5�� �ݺ��ϱ� ���� for���� ����Ͽ���.
    {
        gaming(board, score, turn, board_copy);//����ȭ���̰ų�, ���� ���� �����ϰ� �ٽ� �����Ҷ� ��Ÿ���� ȭ��
        system("cls");//�ش��ϴ� ����� �Է��� ��ġ�� �� �� ȭ���� �����
        print_board_red(board, board_copy, score);//�ش��ϴ� ����� �ٲٰ�, �ٲ� �� ����� ���������� ǥ���Ѵ�
        ini_board(board_copy);//borad_copy�� ���� �ش��ϴ� ����� �����ϰ� ��� 0���� �ʱ�ȭ �Ǿ��ִ�. �� ���� �ش��ϴ� ����� ������ ��� �ִ� ���̴�. ���߿� ���ӵ� ������ ������ ��ƾ� �ϱ� ������ �ٽ� 0���� �ʱ�ȭ �ؾ��Ѵ�.
        Sleep(1000);//1�ʵ��� �ٲ� ����� �����ش�
        system("cls");//�� ȭ���� �����

        while (check_board(board, board_copy) != 0)//check_board�� ���� ���� ������ ����� 3�������� ������ ��찡 ���� ��� 0�� return�Ѵ�. 0�� return�� �� ����(���� ���� ������ ����� 3�������� ������ ��찡 ���� ���)���� ��� �˻��Ѵ�
        {
            print_board_red(board, board_copy, score);//�������� ������ ����� ���������� ó���Ѵ�
            Sleep(1000);//1�� ���� �����ش�
            system("cls");//�� ȭ���� �����
            score += sum_score(board_copy);//�� �� ���ھ�� �̹��� �� ���ھ ���Ѵ�
            bingo_board(board, board_copy, score);//���ӵ� ����� �����
            Sleep(1000);//���ӵ� ����� ���� board�� 1�ʵ��� �����ش�
            system("cls");//�� ȭ���� �����
            rand_board(board, board_copy, score);//�� �κ��� �������� 1-5������ ���ڵ�� ä���
            Sleep(1000);//�������� ���ڸ� ä�� board�� 1�ʵ��� �����ش�
            system("cls");//�� ȭ���� �����
            ini_board(board_copy);//�ٽ� ���� ������ �ݺ��ϱ� ���ؼ��� board_copy�� ��� �� �������� ������ �ϹǷ� 0���� �ʱ�ȭ ���� ����Ѵ�
        }
    }
    print_board(board, score);
    printf("====================\n");
    printf("\n");
    printf("** You��ve earned %d points! **", score);//���������� ���� score�� �����ش�


    return 0;
}

int start_game()
{
    char a = 0;


    printf("-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("CSED 101\n");
    printf("Assignment 2\n");
    printf("\n");
    printf("[[ Match-3 Game ]]\n");
    printf("\n");
    printf("Press [Enter] to start\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=\n");
    scanf("%c", &a);//Enter�ܿ��� �ٸ� Ű �Է��� ��� ���ص� �ǹǷ�, �׳� char ���ڸ� �޴´�
}

void print_board(int a[BOARD_SIZE][BOARD_SIZE], int score)
{
    printf("Score: %d\n", score);

    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            printf("%2d", a[i][j]);
        }
        printf("| %d\n", i);
        if (i != 5)
        {
            printf("\n");
        }
    }
    printf("------------+\n");
    printf(" 0 1 2 3 4 5\n");

}

void gaming(int a[BOARD_SIZE][BOARD_SIZE], int score, int turn, int b[BOARD_SIZE][BOARD_SIZE])
{
    int num = -1;
    print_board(a, score);
    int aa1;//check_position���� �ش��ϴ� ����� ��ġ�� �޴� �����̴�
    int aa2;
    int bb1;
    int bb2;

    do
    {
        printf("====================\n");
        num = check_position(turn, &aa1, &aa2, &bb1, &bb2);

        if (num == 1)
        {
            system("cls");
            print_board(a, score);
            printf("*** They are not adjacent! ***\n");
        }
        else if (num == 2)
        {
            system("cls");
            print_board(a, score);
            printf("*** Out of range! ***\n");
        }
    } while (num != 0);

    swap(&a[aa1][aa2], &a[bb1][bb2]);

    b[aa1][aa2] = a[aa1][aa2];//borad_copy�� �ش�Ǵ� �κп� board���� ���� ���� �ִ´�. board_copy�� print_board_red���� ���������� ǥ�� �� ��ġ�� �Ǵ��ϴµ� ���ȴ�
    b[bb1][bb2] = a[bb1][bb2];

}

int check_position(int turn, int* A1, int* A2, int* B1, int* B2)
{
    int a1, a2, b1, b2;

    printf("* Remaining turns: %d\n", turn);
    printf("Swap...\n");
    printf("Block 1: ");
    scanf("%d %d", &a1, &a2);//���ϴ� ����� ��ġ�� �޴´�
    printf("Block 2: ");
    scanf("%d %d", &b1, &b2);

    if (a1 > 5 || a2 > 5 || b1 > 5 || b2 > 5)//������ ��� �� ������ ��� ����̴�
    {
        return 2;
    }

    else if (abs(a1 - b1) + abs(a2 - b2) == 1)//����� �����ϸ� ��� ���� ������ ���� 1�̴�
    {
        *A1 = a1;//��ȯ�� ��� ��ġ�� �����ͷ� ������
        *A2 = a2;
        *B1 = b1;
        *B2 = b2;
        return 0;
    }

    else//������ ��� ���� ������ ����� ������ �������� ���� ����̴�.
    {
        return 1;
    }

}

void swap(int* x, int* y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void set_color_red()
{
    printf("\033[1;31m");
}
void reset_color()
{
    printf("\033[0m");
}

void print_board_red(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE], int score)
{
    printf("Score: %d\n", score);

    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (b[i][j] == 0)//board_copy�κп��� �ش��ϴ� ����� ��� board���� ���� �Ǿ��ְ�, �������� �ʱ⿡ 0���� �ʱ�ȭ �� ���� ������ b[i][j] == 0�̸� �ش��ϴ� ����� �ƴϹǷ� �׳� ���������� print�ϸ� �ȴ�
            {
                printf("%2d", a[i][j]);
            }
            else//�ش��ϴ� ����̹Ƿ� ���������� print�Ѵ�
            {
                set_color_red();
                printf("%2d", a[i][j]);
                reset_color();
            }
        }
        printf("| %d\n", i);
        if (i != 5)
        {
            printf("\n");
        }
    }
    printf("------------+\n");
    printf(" 0 1 2 3 4 5\n");

}

int check_board(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE])
{
    int check = 0;
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE - 2; j++)//���ǿ� j+2�� �ֱ� ������ -2�� �� �־���
        {
            if (a[i][j] == a[i][j + 1] && a[i][j + 1] == a[i][j + 2])//���� ���� ������ ����� �ּ� 3�� �̻� �����Ǿ�� �Ѵ�. �� �κ��� ���� �࿡�� 3�������� ���� ���� ������ ����� �ִ��� Ȯ���ϴ� �˰����̴�.
            {
                b[i][j] = a[i][j];
                b[i][j + 1] = a[i][j];
                b[i][j + 2] = a[i][j];
                check++;//�� if���� ���ƴ���(���� 3�� ������ ���ڰ� �ִ��� Ȯ���ϴ� �뵵
            }
        }
    }
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE - 2; j++)
        {
            if (a[j][i] == a[j + 1][i] && a[j + 1][i] == a[j + 2][i])// �� �κ��� ���� ������ 3�������� ���� ���� ������ ����� �ִ��� Ȯ���ϴ� �˰����̴�.
            {
                b[j][i] = a[j][i];
                b[j + 1][i] = a[j][i];
                b[j + 2][i] = a[j][i];
                check++;//�� if���� ���ƴ���(���� 3�� ������ ���ڰ� �ִ��� Ȯ���ϴ� �뵵
            }
        }
    }

    if (check == 0)//�� ���� 3�������� ���� ���� ������ ��찡 �ѹ��� ���� ����̴�
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void ini_board(int a[BOARD_SIZE][BOARD_SIZE])
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            a[i][j] = 0;
        }
    }
}

int sum_score(int b[BOARD_SIZE][BOARD_SIZE])
{
    int i, j;
    int sum = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (b[i][j] != 0)
            {
                sum += b[i][j];//board_copy���� �ش�Ǵ� ���� �����Ƿ�, �� ���� �� ���ϸ� �ȴ�
            }
        }
    }
    return sum;
}

void bingo_board(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE], int score)
{
    printf("Score: %d\n", score);
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (b[i][j] == 0)//b[i][j] == 0�� �ش����� ���� ��ġ�� ��Ÿ���� ���� �� �κ��� �״�� print�ϸ� �ȴ�
            {
                printf("%2d", a[i][j]);
            }
            else//�ݴ�� else�� �ش��ϴ� ��ġ�� ��Ÿ����. �� �κ��� ��ĭ���� ä���.
            {
                printf("  ");
            }
        }
        printf("| %d\n", i);
        if (i != 5)
        {
            printf("\n");
        }
    }
    printf("------------+\n");
    printf(" 0 1 2 3 4 5\n");
}

void rand_board(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE], int score)
{
    printf("Score: %d\n", score);
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (b[i][j] == 0)//b[i][j] == 0�� �ش����� ���� ��ġ�� ��Ÿ���� ���� �� �κ��� �״�� print�ϸ� �ȴ�
            {
                printf("%2d", a[i][j]);
            }
            else//�ݴ�� else�� �ش��ϴ� ��ġ�� ��Ÿ����. �� �κ��� rand()�Լ��� �̿��� ������ ���ڷ� ä���.
            {
                a[i][j] = rand() % 5 + 1;
                printf("%2d", a[i][j]);
            }
        }
        printf("| %d\n", i);
        if (i != 5)
        {
            printf("\n");
        }
    }
    printf("------------+\n");
    printf(" 0 1 2 3 4 5\n");
}