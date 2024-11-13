#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define BOARD_SIZE 6



int start_game();//게임의 시작화면을 호출하는 함수
void print_board(int a[BOARD_SIZE][BOARD_SIZE], int score);//게임 보드(2 차원 배열) 등을 전달받아 점수, 보드, 보드의 행과 열 번호 출력하는 함수
void gaming(int a[BOARD_SIZE][BOARD_SIZE], int score, int turn, int b[BOARD_SIZE][BOARD_SIZE]);//게임 보드화면에서 게임을 하는 함수
int check_position(int turn, int* A1, int* A2, int* B1, int* B2);//사용자 입력한 두 블록의 위치가 유효한지 검사하는 함수
void swap(int* x, int* y);//숫자 2개를 바꿔주는 함수
void set_color_red();
void reset_color();
void print_board_red(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE], int score);//해당블록을 붉은색으로 처리하는 함수
int check_board(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE]);//연속된 숫자를 체크하는 함수
void ini_board(int a[BOARD_SIZE][BOARD_SIZE]);//함수의 모든 항을 0으로 초기화 하는 함수
int sum_score(int b[BOARD_SIZE][BOARD_SIZE]);//그 판의 score의 총합을 return하는 함수
void bingo_board(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE], int score);//매치된 블록을 제거하여 print하는 함수
void rand_board(int a[BOARD_SIZE][BOARD_SIZE], int b[BOARD_SIZE][BOARD_SIZE], int score);//빈 자리에 랜덤으로 숫자를 체워서 print하는 함수


int main()
{
    srand(time(NULL));
    FILE* game_board;

    game_board = fopen("board.txt", "r");

    if (game_board == NULL)//board.txt가 리소스 파일에 없을 경우 적절한 오류 문구가 뜨도록 하는 알고리즘
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
            fscanf(game_board, "%d", &board[i][j]);//board[][]에 board.txt에 있는 숫자들을 옮겨 적는 알고리즘
        }
    }

    int score = 0;

    start_game();
    system("cls");//게임 보드판을 나타내기 앞서 앞선 화면을 다 지운다

    int turn = 5;

    int board_copy[BOARD_SIZE][BOARD_SIZE] = { 0 };


    for (turn = 5; turn > 0; turn--)//총 5번 반복하기 위해 for문을 사용하였다.
    {
        gaming(board, score, turn, board_copy);//시작화면이거나, 그전 턴을 종료하고 다시 시작할때 나타나는 화면
        system("cls");//해당하는 블록의 입력을 마치면 그 전 화면을 지운다
        print_board_red(board, board_copy, score);//해당하는 블록을 바꾸고, 바꾼 두 블록을 붉은색으로 표현한다
        ini_board(board_copy);//borad_copy는 현재 해당하는 블록을 제외하고 모두 0으로 초기화 되어있다. 이 말은 해당하는 블록의 정보를 담고 있는 것이다. 나중에 연속된 숫자의 정보를 담아야 하기 때문에 다시 0으로 초기화 해야한다.
        Sleep(1000);//1초동안 바뀐 블록을 보여준다
        system("cls");//전 화면을 지운다

        while (check_board(board, board_copy) != 0)//check_board는 같은 값을 가지는 블록이 3연속으로 나열된 경우가 없을 경우 0을 return한다. 0을 return할 때 까지(같은 값을 가지는 블록이 3연속으로 나열된 경우가 없을 경우)까지 계속 검사한다
        {
            print_board_red(board, board_copy, score);//연속으로 나열된 블록을 붉은색으로 처리한다
            Sleep(1000);//1초 동안 보여준다
            system("cls");//전 화면을 지운다
            score += sum_score(board_copy);//그 전 스코어에서 이번에 딴 스코어를 더한다
            bingo_board(board, board_copy, score);//연속된 블록을 지운다
            Sleep(1000);//연속된 블록을 지운 board를 1초동안 보여준다
            system("cls");//전 화면을 지운다
            rand_board(board, board_copy, score);//빈 부분은 랜덤으로 1-5까지의 숫자들로 채운다
            Sleep(1000);//랜덤으로 숫자를 채운 board를 1초동안 보여준다
            system("cls");//전 화면을 지운다
            ini_board(board_copy);//다시 위의 과정을 반복하기 위해서는 board_copy에 담긴 전 정보들을 지워야 하므로 0으로 초기화 시켜 줘야한다
        }
    }
    print_board(board, score);
    printf("====================\n");
    printf("\n");
    printf("** You’ve earned %d points! **", score);//최종적으로 얻은 score을 보여준다


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
    scanf("%c", &a);//Enter외에는 다른 키 입력을 고려 안해도 되므로, 그냥 char 문자를 받는다
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
    int aa1;//check_position에서 해당하는 블록의 위치를 받는 변수이다
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

    b[aa1][aa2] = a[aa1][aa2];//borad_copy에 해당되는 부분에 board값과 같은 값을 넣는다. board_copy는 print_board_red에서 붉은색으로 표시 될 위치를 판단하는데 사용된다
    b[bb1][bb2] = a[bb1][bb2];

}

int check_position(int turn, int* A1, int* A2, int* B1, int* B2)
{
    int a1, a2, b1, b2;

    printf("* Remaining turns: %d\n", turn);
    printf("Swap...\n");
    printf("Block 1: ");
    scanf("%d %d", &a1, &a2);//원하는 블록의 위치를 받는다
    printf("Block 2: ");
    scanf("%d %d", &b1, &b2);

    if (a1 > 5 || a2 > 5 || b1 > 5 || b2 > 5)//보드의 행과 열 범위를 벗어난 경우이다
    {
        return 2;
    }

    else if (abs(a1 - b1) + abs(a2 - b2) == 1)//블록이 인접하면 행과 열의 차이의 합이 1이다
    {
        *A1 = a1;//교환할 블록 위치를 포인터로 저장함
        *A2 = a2;
        *B1 = b1;
        *B2 = b2;
        return 0;
    }

    else//보드의 행과 열의 범위를 벗어나진 않지만 인접하지 않은 경우이다.
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
            if (b[i][j] == 0)//board_copy부분에서 해당하는 블록은 모두 board값과 같게 되어있고, 나머지는 초기에 0으로 초기화 해 놨기 때문에 b[i][j] == 0이면 해당하는 블록이 아니므로 그냥 검은색으로 print하면 된다
            {
                printf("%2d", a[i][j]);
            }
            else//해당하는 블록이므로 붉은색으로 print한다
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
        for (j = 0; j < BOARD_SIZE - 2; j++)//조건에 j+2가 있기 때문에 -2를 해 주었다
        {
            if (a[i][j] == a[i][j + 1] && a[i][j + 1] == a[i][j + 2])//같은 값을 가지는 블록이 최소 3개 이상 나열되어야 한다. 이 부분은 같은 행에서 3연속으로 같은 값을 가지는 블록이 있는지 확인하는 알고리즘이다.
            {
                b[i][j] = a[i][j];
                b[i][j + 1] = a[i][j];
                b[i][j + 2] = a[i][j];
                check++;//이 if문을 거쳤는지(연속 3개 나열된 숫자가 있는지 확인하는 용도
            }
        }
    }
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE - 2; j++)
        {
            if (a[j][i] == a[j + 1][i] && a[j + 1][i] == a[j + 2][i])// 이 부분은 같은 열에서 3연속으로 같은 값을 가지는 블록이 있는지 확인하는 알고리즘이다.
            {
                b[j][i] = a[j][i];
                b[j + 1][i] = a[j][i];
                b[j + 2][i] = a[j][i];
                check++;//이 if문을 거쳤는지(연속 3개 나열된 숫자가 있는지 확인하는 용도
            }
        }
    }

    if (check == 0)//이 경우는 3연속으로 같은 값이 나열된 경우가 한번도 없는 경우이다
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
                sum += b[i][j];//board_copy에는 해당되는 값만 있으므로, 이 값을 다 더하면 된다
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
            if (b[i][j] == 0)//b[i][j] == 0는 해당하지 않은 위치를 나타낸다 따라서 이 부분은 그대로 print하면 된다
            {
                printf("%2d", a[i][j]);
            }
            else//반대로 else면 해당하는 위치를 나타낸다. 이 부분은 빈칸으로 채운다.
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
            if (b[i][j] == 0)//b[i][j] == 0는 해당하지 않은 위치를 나타낸다 따라서 이 부분은 그대로 print하면 된다
            {
                printf("%2d", a[i][j]);
            }
            else//반대로 else면 해당하는 위치를 나타낸다. 이 부분은 rand()함수를 이용해 랜덤한 숫자로 채운다.
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