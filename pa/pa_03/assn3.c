#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_FILE_NAME 30
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#define FLUSH while (getchar() != '\n')

void print_start();//시작화면 출력하는 함수
char* mystrlower(char* str);//문자열의 모든 알파벳을 소문자로 바꾸는 함수
char* nonabttogap(char* str);//알파벳을 제외한 모든 문자는 공백으로 치환하는 함수
void dltetr(char* str);//'\n'을'\0'로 바꾸는 함수
void swap(char** str1, char** str2);//문자열 2개를 swap하는 함수
void swap_int(int* a, int* b);//숫자 2개를 swap하는 함수


int main()
{

    int enter = 0;
    while (enter == 0)
    {
        int kkk = 0;
        enter = 1;
        system("cls");
        print_start();
        char cmd[20];
        char stc[1000];//test에서 받는 문장을 넣는 문자열
        char stcc[1000];//test 마지막에 문장 그대로를 출력하기 위해 stc를 복사해 놓는 문자열
        
        fgets(cmd, sizeof(cmd), stdin);

        dltetr(cmd);
        mystrlower(cmd);//대소문자 상관없이 동일하게 작동하기 위해서 받은 문자열을 모두 소문자로 변환함

        char filename[MAX_FILE_NAME];//초기 화면에서 명령어를 받는 부분

        FILE* train, * stats;

        if (strcmp(cmd, "train") == 0)//train입력했을시
        {
            int chk = 0;
            while (chk == 0)
            {
                system("cls");
                print_start();
                printf("%s", "train\n");
                printf("File name: ");
                //scanf("%s", filename);
                fgets(filename, sizeof(filename), stdin);
                dltetr(filename);
                train = fopen(filename, "r");

                if (train == NULL)
                {
                    system("cls");
                    print_start();
                    printf("%s", "train\n");
                    printf("Error: File does not exist");
                    Sleep(1000);
                    system("cls");
                    chk = 0;//없는 파일 받으면 chk가 0이 유지되어서 while문 계속 돈다.
                }
                else
                {
                    chk = 1;//있는 파일명을 받으면 chk가 0이 아니게 되어 while 문 빠져나온다
                }
            }
            char label[5];
            char text[1000];

            int a = 5;
            char** words = (char**)malloc(sizeof(char*) * a);//단어를 저장하는 동적할당 2차배열
            int* freq_ham = (int*)malloc(sizeof(int) * a);//ham단어 수를 저장
            int* freq_spam = (int*)malloc(sizeof(int) * a);//spam단어 수를 저장


            int cnt = 0;
            int cntsum = 0;


            char trash;

            int cnt_ham = 0;//ham등장 횟수
            int cnt_spam = 0;//spam등장 횟수
            while (1)
            {
                if (fgets(label, sizeof(label), train) == NULL)
                {
                    break;
                }
                if (strcmp(label, "ham\t") == 0)
                {
                    strcpy(label, "ham");
                    cnt_ham += 1;
                }
                if (strcmp(label, "spam") == 0)//spam일 경우 text앞에 '\t'가 붙는다. 이를 제거하기 위한 알고리즘이다.
                {
                    fscanf(train, "%c", &trash);
                    cnt_spam += 1;
                }
                if (fgets(text, sizeof(text), train) == NULL)
                {
                    break;
                }



                dltetr(text);//'\n'이'\0'로 바껴서 text 문자열에 마지막에는 '\0'이 두번 연속으로 있다.
                mystrlower(text);
                nonabttogap(text);



                int i = 0;
                int text_len;
                text_len = strlen(text);

                while (text[text_len] != '\0')//메시지 마지막에 특수문자가 있을경우, 이 알고리즘을 통해 특수문자 공간에 체워진 공백을 처리할 수 있다.
                {
                    text_len++;
                }

                text[text_len + 1] = 'A';//text는 mystrlower에서 대문자는 존재하지 않는다. 따라서 text를 검사할때 'A'가 나오면 문자열이 종료되었다고 판단할 수 있다. 문장끝에는 '\0'이 2개 있으므로, +1을 해 뒤의 '\0'를 'A'로 바꿔준다.


                while (1)//text를 다 읽을때 while문을 빠져나올수 있도록 i값을 계속 증가시키는 알고리즘을 가지고 있다
                {

                    if ((cntsum + cnt) >= (a - 1))//words의 크기를 수시로 확인하면서 증가시킨다. 이는 cnt가 1씩 늘어날때 마다 검사한다
                    {
                        a = a * 2;
                        words = (char**)realloc(words, sizeof(char*) * a);
                        freq_ham = (int*)realloc(freq_ham, sizeof(int) * a);
                        freq_spam = (int*)realloc(freq_spam, sizeof(int) * a);
                    }

                    char* bakt;
                    bakt = strtok(&text[i], " ");
                    while (!(strlen(bakt) > 1 && strlen(bakt) <= 20))//길이가 1이거나 20초과인 경우는 고려하지 않는다
                    {
                        while (text[i] != '\0')//다음 단어 전에 붙어 있는 '\0'를 가리키기 위한 알고리즘
                        {
                            i++;

                        }
                        while (text[i] == '\0' || text[i] == ' ')//단어의 시작을 가리키는 알고리즘
                        {
                            i++;
                        }

                        if (text[i] == 'A')//문장의 마무리일 경우 while 문 종료
                        {
                            break;
                        }

                        bakt = strtok(&text[i], " ");//bakt 배열에 한 단어를 넣는다
                    }
                    if (text[i] == 'A')//문장의 마무리일 경우 while 문 종료
                    {
                        break;
                    }
                    int p;
                    int q = 0;

                    for (p = 0; p < (cntsum + cnt); p++)//cntsum은 그 줄의 시작 부분을, cnt는 그 줄에서 검사가 진행된 단어의 수이다. 따라서 이 범위에서만 반복을 검사해 주면 된다.
                    {
                        if (strcmp(bakt, words[p]) == 0)
                        {
                            q = 1;
                        }

                    }

                    int freq = 0;//단어 등장 빈도수
                    int pos = (cntsum + cnt);//단어의 위치를 나타내는 변수. 일단 검사하는 위치로 초기화 한다.

                    freq_ham[cntsum + cnt] = 0;
                    freq_spam[cntsum + cnt] = 0;//단어 빈도수 0으로 초기화

                    if (q == 0)//중복이 없는 경우
                    {
                        words[cntsum + cnt] = malloc((strlen(bakt) + 1) * sizeof(char));
                        freq = 1;//처음 나온 단어이므로 1을 넣으면 된다.
                        strcpy(words[cntsum + cnt], bakt);//words에 단어를 넣는다
                        bakt = " ";//bakt 초기화
                        cnt++;
                    }

                    else//중복이 있는 경우
                    {
                        for (p = cntsum; p < (cntsum + cnt); p++)//검사하는 줄에서 중복이 있는지 확인한다.
                        {
                            if (strcmp(bakt, words[p]) == 0)
                            {
                                bakt = " ";//bakt 초기화
                            }
                        }

                        for (p = 0; p < cntsum; p++)//검사하는 줄 이외의 범위에서 중복이 있는지 확인한다.
                        {
                            if (strcmp(bakt, words[p]) == 0)
                            {
                                bakt = " ";//bakt 초기화
                                freq += 1;//단어의 등장 횟수를 1 늘린다.
                                pos = p;//검사하는 줄 이외의 범위에서 중복이 있을 경우, p가 중복되는 단어의 위치이다
                            }
                        }
                    }

                    if (strcmp(label, "ham") == 0)//단어 빈도수를 배열에 넣는다
                    {
                        freq_ham[pos] += freq;
                    }
                    else if (strcmp(label, "spam") == 0)
                    {
                        freq_spam[pos] += freq;
                    }

                    while (text[i] != '\0')//다음 단어 전에 붙어 있는 '\0'를 가리키기 위한 알고리즘
                    {
                        i++;

                    }
                    while (text[i] == '\0' || text[i] == ' ')//단어의 시작을 가리키는 알고리즘
                    {
                        i++;
                    }


                    if (text[i] == 'A')//문장의 마무리일 경우 while 문 종료
                    {
                        break;
                    }

                }
                cntsum += cnt;
                cnt = 0;
            }

            int w, x;
            for (w = 0; w < cntsum - 1; w++)//버블정렬을 통해 문자열을 오름차순으로 나열한다
            {
                for (x = 0; x < cntsum - w - 1; x++)
                {
                    if (strcmp(words[x], words[x + 1]) > 0)
                    {
                        swap(&words[x], &words[x + 1]);
                        swap_int(&freq_ham[x], &freq_ham[x + 1]);
                        swap_int(&freq_spam[x], &freq_spam[x + 1]);
                    }
                }
            }
            printf("\n");
            printf("After training...\n");
            printf("Ham: %d, Spam: %d\n", cnt_ham, cnt_spam);
            int v;
            for (v = 0; v < cntsum; v++)
            {
                printf("%s,", words[v]);
                printf("%d,", freq_ham[v]);
                printf("%d\n", freq_spam[v]);
            }//화면에 결과 출력

            stats = fopen("stats.txt", "w");


            fprintf(stats, "Ham: %d, Spam: %d\n", cnt_ham, cnt_spam);
            for (v = 0; v < cntsum; v++)
            {
                fprintf(stats, "%s,", words[v]);
                fprintf(stats, "%d,", freq_ham[v]);
                fprintf(stats, "%d\n", freq_spam[v]);
            }//stats.txt.에 결과 출력
            
            fclose(train);
            fclose(stats);
            
            
            int g;
            for (g = 0; g < cntsum; g++)
            {
                free(words[g]);
                
            }
            free(words);
            free(freq_ham);
            free(freq_spam);
            
            
            
        }


        else if (strcmp(cmd, "test") == 0)//test입력했을시
        {
            int ccc = 0;

            FILE* stats;
            stats = fopen("stats.txt", "r");
            if (stats == NULL)//stats.txt가 없을 경우, ccc=1로 한다
            {
                system("cls");
                print_start();
                printf("test\n");
                printf("Error: File does not exist");
                Sleep(1000);
                system("cls");
                enter = 0;
                ccc = 1;
                kkk = 1;
            }

            while (ccc == 0)//ccc=1이면 stats.txt가 없다는 뜻이다 따라서 이 경우는 밑의 알고리즘을 한번도 안 돌게 해야한다. stats.txt가 있을 경우, 한번만 돌면 되므로 while 밑에 ccc=1로 처리한다.
            {
                int b = 5;
                char** hspam = (char**)malloc(sizeof(char*) * b);
                int* num_ham = (int*)malloc(sizeof(int*) * b);
                int* num_spam = (int*)malloc(sizeof(int*) * b);

                char t1[1000];//한 메시지의 길이가1000자가 넘어가지 않으므로, 단어도 1000자를 넘어갈 수 없다
                int n1 = -1;
                char t2[1000];
                char t3[1000];
                int n2 = -1;

                fscanf(stats, "%s %d %s %s %d", t1, &n1, t2, t3, &n2);

                num_ham[0] = n1;
                num_spam[0] = n2;
                hspam[0] = "not";
                //strcpy(hspam[0], "not");//hspam[1]부터 단어가 들어가므로 아무 문자열로 초기화한다

                int ii = 1;
                int cnt_hspam = 0;//hspam의 행렬 개수 파악
                while (1)
                {

                    int n = 0;
                    n = fscanf(stats, "%s", t1);


                    if (n != 1)
                    {
                        break;
                    }

                    char* tt1, * tt2, * tt3;
                    tt1 = strtok(t1, ",");
                    tt2 = strtok(NULL, ",");
                    tt3 = strtok(NULL, ",");

                    n1 = atoi(tt2);
                    n2 = atoi(tt3);

                    hspam[ii] = (char*)malloc(sizeof(char*) * (strlen(tt1) + 1));
                    strcpy(hspam[ii], tt1);
                    num_ham[ii] = n1;
                    num_spam[ii] = n2;
                    ii++;

                    if (ii >= b - 1)//words의 크기를 수시로 확인하면서 증가시킨다. 이는 ii가 1씩 늘어날때 마다 검사한다
                    {
                        b = b * 2;
                        hspam = (char**)realloc(hspam, sizeof(char*) * b);
                        num_ham = (int*)realloc(num_ham, sizeof(int) * b);
                        num_spam = (int*)realloc(num_spam, sizeof(int) * b);
                    }
                    cnt_hspam++;
                }

                system("cls");
                print_start();
                printf("%s", "test\n");
                printf("Enter a message: ");
                fgets(stc, sizeof(stc), stdin);//문장입력

                strcpy(stcc, stc);//stcc에 문장 원본 복사

                mystrlower(stc);//소문자로 변환
                nonabttogap(stc);//특수문자 공백으로 치환


                int sent_len = 0;
                while (stc[sent_len] != '\0')//메시지 마지막에 특수문자가 있을경우, 이 알고리즘을 통해 특수문자 공간에 체워진 공백을 처리할 수 있다.
                {
                    sent_len++;
                }

                stc[sent_len + 1] = 'A';//text는 mystrlower에서 대문자는 존재하지 않는다. 따라서 text를 검사할때 'A'가 나오면 문자열이 종료되었다고 판단할 수 있다. 문장끝에는 '\0'이 2개 있으므로, +1을 해 뒤의 '\0'를 'A'로 바꿔준다.


                b = 5;
                char** sent = (char**)malloc(sizeof(char*) * b);
                char* bakt2;
                int i = 0;
                int cnt_stc = 0;

                while (1)
                {
                    bakt2 = strtok(&stc[i], " ");
                    while (!(strlen(bakt2) > 1 && strlen(bakt2) <= 20))//길이가 1이거나 20초과인 경우는 고려하지 않는다
                    {
                        bakt2 = " ";
                        while (stc[i] != '\0')//다음 단어 전에 붙어 있는 '\0'를 가리키기 위한 알고리즘
                        {
                            i++;

                        }
                        while (stc[i] == '\0' || stc[i] == ' ')//단어의 시작을 가리키는 알고리즘
                        {
                            i++;
                        }
                        if (stc[i] == 'A')//문장의 마무리일 경우 while 문 종료
                        {
                            break;
                        }
                        bakt2 = strtok(&stc[i], " ");//bakt2 배열에 한 단어를 넣는다
                    }
                    if (stc[i] == 'A')//문장의 마무리일 경우 while 문 종료
                    {
                        break;
                    }


                    int p;
                    int q = 0;

                    for (p = 0; p < cnt_stc; p++)
                    {
                        if (strcmp(bakt2, sent[p]) == 0)
                        {
                            q = 1;
                        }

                    }
                    if (q == 0)//중복이 없는 경우
                    {
                        sent[cnt_stc] = malloc((strlen(bakt2) + 1) * sizeof(char));
                        strcpy(sent[cnt_stc], bakt2);//sent에 단어를 넣는다
                        bakt2 = " ";//bakt2 초기화
                        cnt_stc++;
                    }

                    while (stc[i] != '\0')//다음 단어 전에 붙어 있는 '\0'를 가리키기 위한 알고리즘
                    {
                        i++;

                    }
                    while (stc[i] == '\0' || stc[i] == ' ')//단어의 시작을 가리키는 알고리즘
                    {
                        i++;
                    }


                    if (stc[i] == 'A')//문장의 마무리일 경우 while 문 종료
                    {
                        break;
                    }
                }//문장에서 단어 다 sent배열에 저장

                float ham = (float)num_ham[0] / (num_ham[0] + num_spam[0]);
                float spam = (float)num_spam[0] / (num_ham[0] + num_spam[0]);

                printf("\n");
                printf("P(Ham)=%.3f, ", ham);
                printf("P(Spam)=%.3f\n", spam);
                printf("\n");

                int ck, cl;

                for (ck = 0; ck < cnt_stc; ck++)//입력한 문장에 있는 단어가 train했던 단어와 일치하는지 판단하는 알고리즘. 이 과정에서Naive Bayes Classifier가 사용된다
                {
                    for (cl = 0; cl < cnt_hspam + 1; cl++)
                    {
                        if (strcmp(sent[ck], hspam[cl]) == 0)
                        {
                            float p = (float)num_ham[cl] / num_ham[0];
                            float q = (float)num_spam[cl] / num_spam[0];
                            if (p == 0)
                            {
                                p = (0.1) / num_ham[0];
                            }
                            if (q == 0)
                            {
                                q = (0.1) / num_spam[0];
                            }
                            printf("P(%s | Ham) = %.3f, ", hspam[cl], p);
                            printf("P(%s | Spam) = %.3f\n", hspam[cl], q);


                            ham *= p;
                            spam *= q;
                        }
                    }
                }
                dltetr(stcc);//stc에는 '\n'가 있으므로, 이를 제거해서 출력해야한다
                printf("\n");
                printf("P( Ham | '%s'): %.3f\n", stcc, ham);
                printf("P( Spam | '%s'): %.3f\n", stcc, spam);

                printf("\n");
                if (ham > spam)
                {
                    printf("This message is HAM");
                }
                else if (ham < spam)
                {
                    printf("This message is SPAM");
                }
                else
                {
                    printf("I can't tell if this message is spam or ham");
                }
                ccc = 1;
                
                int u;
                for (u = 1; u < cnt_hspam + 1; u++)
                {
                    free(hspam[u]);
                }
                free(hspam);
                free(num_ham);
                free(num_spam);
                free(sent);

                
            }


        }


        else if (strcmp(cmd, "exit") == 0)
        {
            return 0;//프로그램 종료
        }
        else//test train exit 이외의 단어를 입력한 경우
        {
            system("cls");
            print_start();
            printf("%s\n", cmd);
            printf("Error: Invalid input");
            Sleep(1000);
            system("cls");
            enter = 0;
            kkk = 1;
        }

        char enter_chk;

        if (kkk == 0)
        {
            scanf("%c", &enter_chk);
            if (enter_chk == '\n')
            {
                enter = 0;//Enter누르면 enter=0이 되서 while문이 다시 돌아간다
                
            }

        }

    }
    return 0;
}

void swap_int(int* a, int* b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}

void swap(char** str1, char** str2)
{
    char* str = *str1;
    *str1 = *str2;
    *str2 = str;
}

void dltetr(char* str)
{
    int i = 0;
    while (str[i] != '\n')
    {
        i++;
        if (str[i] == '\0')
        {
            break;
        }
    }
    str[i] = '\0';
}

char* nonabttogap(char* str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || ((str[i] >= 'a' && str[i] <= 'z'))))
        {
            str[i] = ' ';
        }
        i++;
    }

    return str;
}

char* mystrlower(char* str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] - 'A' + 'a';
        }
        i++;
    }
    return str;
}

void print_start()
{
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("CSED 101 \n");
    printf("Assignment 3\n");
    printf("\n");
    printf("Naive Bayesian Classifier for Spam Filtering\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Command: ");
}