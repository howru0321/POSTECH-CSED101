#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_FILE_NAME 30
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#define FLUSH while (getchar() != '\n')

void print_start();//����ȭ�� ����ϴ� �Լ�
char* mystrlower(char* str);//���ڿ��� ��� ���ĺ��� �ҹ��ڷ� �ٲٴ� �Լ�
char* nonabttogap(char* str);//���ĺ��� ������ ��� ���ڴ� �������� ġȯ�ϴ� �Լ�
void dltetr(char* str);//'\n'��'\0'�� �ٲٴ� �Լ�
void swap(char** str1, char** str2);//���ڿ� 2���� swap�ϴ� �Լ�
void swap_int(int* a, int* b);//���� 2���� swap�ϴ� �Լ�


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
        char stc[1000];//test���� �޴� ������ �ִ� ���ڿ�
        char stcc[1000];//test �������� ���� �״�θ� ����ϱ� ���� stc�� ������ ���� ���ڿ�
        
        fgets(cmd, sizeof(cmd), stdin);

        dltetr(cmd);
        mystrlower(cmd);//��ҹ��� ������� �����ϰ� �۵��ϱ� ���ؼ� ���� ���ڿ��� ��� �ҹ��ڷ� ��ȯ��

        char filename[MAX_FILE_NAME];//�ʱ� ȭ�鿡�� ��ɾ �޴� �κ�

        FILE* train, * stats;

        if (strcmp(cmd, "train") == 0)//train�Է�������
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
                    chk = 0;//���� ���� ������ chk�� 0�� �����Ǿ while�� ��� ����.
                }
                else
                {
                    chk = 1;//�ִ� ���ϸ��� ������ chk�� 0�� �ƴϰ� �Ǿ� while �� �������´�
                }
            }
            char label[5];
            char text[1000];

            int a = 5;
            char** words = (char**)malloc(sizeof(char*) * a);//�ܾ �����ϴ� �����Ҵ� 2���迭
            int* freq_ham = (int*)malloc(sizeof(int) * a);//ham�ܾ� ���� ����
            int* freq_spam = (int*)malloc(sizeof(int) * a);//spam�ܾ� ���� ����


            int cnt = 0;
            int cntsum = 0;


            char trash;

            int cnt_ham = 0;//ham���� Ƚ��
            int cnt_spam = 0;//spam���� Ƚ��
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
                if (strcmp(label, "spam") == 0)//spam�� ��� text�տ� '\t'�� �ٴ´�. �̸� �����ϱ� ���� �˰����̴�.
                {
                    fscanf(train, "%c", &trash);
                    cnt_spam += 1;
                }
                if (fgets(text, sizeof(text), train) == NULL)
                {
                    break;
                }



                dltetr(text);//'\n'��'\0'�� �ٲ��� text ���ڿ��� ���������� '\0'�� �ι� �������� �ִ�.
                mystrlower(text);
                nonabttogap(text);



                int i = 0;
                int text_len;
                text_len = strlen(text);

                while (text[text_len] != '\0')//�޽��� �������� Ư�����ڰ� �������, �� �˰����� ���� Ư������ ������ ü���� ������ ó���� �� �ִ�.
                {
                    text_len++;
                }

                text[text_len + 1] = 'A';//text�� mystrlower���� �빮�ڴ� �������� �ʴ´�. ���� text�� �˻��Ҷ� 'A'�� ������ ���ڿ��� ����Ǿ��ٰ� �Ǵ��� �� �ִ�. ���峡���� '\0'�� 2�� �����Ƿ�, +1�� �� ���� '\0'�� 'A'�� �ٲ��ش�.


                while (1)//text�� �� ������ while���� �������ü� �ֵ��� i���� ��� ������Ű�� �˰����� ������ �ִ�
                {

                    if ((cntsum + cnt) >= (a - 1))//words�� ũ�⸦ ���÷� Ȯ���ϸ鼭 ������Ų��. �̴� cnt�� 1�� �þ�� ���� �˻��Ѵ�
                    {
                        a = a * 2;
                        words = (char**)realloc(words, sizeof(char*) * a);
                        freq_ham = (int*)realloc(freq_ham, sizeof(int) * a);
                        freq_spam = (int*)realloc(freq_spam, sizeof(int) * a);
                    }

                    char* bakt;
                    bakt = strtok(&text[i], " ");
                    while (!(strlen(bakt) > 1 && strlen(bakt) <= 20))//���̰� 1�̰ų� 20�ʰ��� ���� ������� �ʴ´�
                    {
                        while (text[i] != '\0')//���� �ܾ� ���� �پ� �ִ� '\0'�� ����Ű�� ���� �˰���
                        {
                            i++;

                        }
                        while (text[i] == '\0' || text[i] == ' ')//�ܾ��� ������ ����Ű�� �˰���
                        {
                            i++;
                        }

                        if (text[i] == 'A')//������ �������� ��� while �� ����
                        {
                            break;
                        }

                        bakt = strtok(&text[i], " ");//bakt �迭�� �� �ܾ �ִ´�
                    }
                    if (text[i] == 'A')//������ �������� ��� while �� ����
                    {
                        break;
                    }
                    int p;
                    int q = 0;

                    for (p = 0; p < (cntsum + cnt); p++)//cntsum�� �� ���� ���� �κ���, cnt�� �� �ٿ��� �˻簡 ����� �ܾ��� ���̴�. ���� �� ���������� �ݺ��� �˻��� �ָ� �ȴ�.
                    {
                        if (strcmp(bakt, words[p]) == 0)
                        {
                            q = 1;
                        }

                    }

                    int freq = 0;//�ܾ� ���� �󵵼�
                    int pos = (cntsum + cnt);//�ܾ��� ��ġ�� ��Ÿ���� ����. �ϴ� �˻��ϴ� ��ġ�� �ʱ�ȭ �Ѵ�.

                    freq_ham[cntsum + cnt] = 0;
                    freq_spam[cntsum + cnt] = 0;//�ܾ� �󵵼� 0���� �ʱ�ȭ

                    if (q == 0)//�ߺ��� ���� ���
                    {
                        words[cntsum + cnt] = malloc((strlen(bakt) + 1) * sizeof(char));
                        freq = 1;//ó�� ���� �ܾ��̹Ƿ� 1�� ������ �ȴ�.
                        strcpy(words[cntsum + cnt], bakt);//words�� �ܾ �ִ´�
                        bakt = " ";//bakt �ʱ�ȭ
                        cnt++;
                    }

                    else//�ߺ��� �ִ� ���
                    {
                        for (p = cntsum; p < (cntsum + cnt); p++)//�˻��ϴ� �ٿ��� �ߺ��� �ִ��� Ȯ���Ѵ�.
                        {
                            if (strcmp(bakt, words[p]) == 0)
                            {
                                bakt = " ";//bakt �ʱ�ȭ
                            }
                        }

                        for (p = 0; p < cntsum; p++)//�˻��ϴ� �� �̿��� �������� �ߺ��� �ִ��� Ȯ���Ѵ�.
                        {
                            if (strcmp(bakt, words[p]) == 0)
                            {
                                bakt = " ";//bakt �ʱ�ȭ
                                freq += 1;//�ܾ��� ���� Ƚ���� 1 �ø���.
                                pos = p;//�˻��ϴ� �� �̿��� �������� �ߺ��� ���� ���, p�� �ߺ��Ǵ� �ܾ��� ��ġ�̴�
                            }
                        }
                    }

                    if (strcmp(label, "ham") == 0)//�ܾ� �󵵼��� �迭�� �ִ´�
                    {
                        freq_ham[pos] += freq;
                    }
                    else if (strcmp(label, "spam") == 0)
                    {
                        freq_spam[pos] += freq;
                    }

                    while (text[i] != '\0')//���� �ܾ� ���� �پ� �ִ� '\0'�� ����Ű�� ���� �˰���
                    {
                        i++;

                    }
                    while (text[i] == '\0' || text[i] == ' ')//�ܾ��� ������ ����Ű�� �˰���
                    {
                        i++;
                    }


                    if (text[i] == 'A')//������ �������� ��� while �� ����
                    {
                        break;
                    }

                }
                cntsum += cnt;
                cnt = 0;
            }

            int w, x;
            for (w = 0; w < cntsum - 1; w++)//���������� ���� ���ڿ��� ������������ �����Ѵ�
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
            }//ȭ�鿡 ��� ���

            stats = fopen("stats.txt", "w");


            fprintf(stats, "Ham: %d, Spam: %d\n", cnt_ham, cnt_spam);
            for (v = 0; v < cntsum; v++)
            {
                fprintf(stats, "%s,", words[v]);
                fprintf(stats, "%d,", freq_ham[v]);
                fprintf(stats, "%d\n", freq_spam[v]);
            }//stats.txt.�� ��� ���
            
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


        else if (strcmp(cmd, "test") == 0)//test�Է�������
        {
            int ccc = 0;

            FILE* stats;
            stats = fopen("stats.txt", "r");
            if (stats == NULL)//stats.txt�� ���� ���, ccc=1�� �Ѵ�
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

            while (ccc == 0)//ccc=1�̸� stats.txt�� ���ٴ� ���̴� ���� �� ���� ���� �˰����� �ѹ��� �� ���� �ؾ��Ѵ�. stats.txt�� ���� ���, �ѹ��� ���� �ǹǷ� while �ؿ� ccc=1�� ó���Ѵ�.
            {
                int b = 5;
                char** hspam = (char**)malloc(sizeof(char*) * b);
                int* num_ham = (int*)malloc(sizeof(int*) * b);
                int* num_spam = (int*)malloc(sizeof(int*) * b);

                char t1[1000];//�� �޽����� ���̰�1000�ڰ� �Ѿ�� �����Ƿ�, �ܾ 1000�ڸ� �Ѿ �� ����
                int n1 = -1;
                char t2[1000];
                char t3[1000];
                int n2 = -1;

                fscanf(stats, "%s %d %s %s %d", t1, &n1, t2, t3, &n2);

                num_ham[0] = n1;
                num_spam[0] = n2;
                hspam[0] = "not";
                //strcpy(hspam[0], "not");//hspam[1]���� �ܾ ���Ƿ� �ƹ� ���ڿ��� �ʱ�ȭ�Ѵ�

                int ii = 1;
                int cnt_hspam = 0;//hspam�� ��� ���� �ľ�
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

                    if (ii >= b - 1)//words�� ũ�⸦ ���÷� Ȯ���ϸ鼭 ������Ų��. �̴� ii�� 1�� �þ�� ���� �˻��Ѵ�
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
                fgets(stc, sizeof(stc), stdin);//�����Է�

                strcpy(stcc, stc);//stcc�� ���� ���� ����

                mystrlower(stc);//�ҹ��ڷ� ��ȯ
                nonabttogap(stc);//Ư������ �������� ġȯ


                int sent_len = 0;
                while (stc[sent_len] != '\0')//�޽��� �������� Ư�����ڰ� �������, �� �˰����� ���� Ư������ ������ ü���� ������ ó���� �� �ִ�.
                {
                    sent_len++;
                }

                stc[sent_len + 1] = 'A';//text�� mystrlower���� �빮�ڴ� �������� �ʴ´�. ���� text�� �˻��Ҷ� 'A'�� ������ ���ڿ��� ����Ǿ��ٰ� �Ǵ��� �� �ִ�. ���峡���� '\0'�� 2�� �����Ƿ�, +1�� �� ���� '\0'�� 'A'�� �ٲ��ش�.


                b = 5;
                char** sent = (char**)malloc(sizeof(char*) * b);
                char* bakt2;
                int i = 0;
                int cnt_stc = 0;

                while (1)
                {
                    bakt2 = strtok(&stc[i], " ");
                    while (!(strlen(bakt2) > 1 && strlen(bakt2) <= 20))//���̰� 1�̰ų� 20�ʰ��� ���� ������� �ʴ´�
                    {
                        bakt2 = " ";
                        while (stc[i] != '\0')//���� �ܾ� ���� �پ� �ִ� '\0'�� ����Ű�� ���� �˰���
                        {
                            i++;

                        }
                        while (stc[i] == '\0' || stc[i] == ' ')//�ܾ��� ������ ����Ű�� �˰���
                        {
                            i++;
                        }
                        if (stc[i] == 'A')//������ �������� ��� while �� ����
                        {
                            break;
                        }
                        bakt2 = strtok(&stc[i], " ");//bakt2 �迭�� �� �ܾ �ִ´�
                    }
                    if (stc[i] == 'A')//������ �������� ��� while �� ����
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
                    if (q == 0)//�ߺ��� ���� ���
                    {
                        sent[cnt_stc] = malloc((strlen(bakt2) + 1) * sizeof(char));
                        strcpy(sent[cnt_stc], bakt2);//sent�� �ܾ �ִ´�
                        bakt2 = " ";//bakt2 �ʱ�ȭ
                        cnt_stc++;
                    }

                    while (stc[i] != '\0')//���� �ܾ� ���� �پ� �ִ� '\0'�� ����Ű�� ���� �˰���
                    {
                        i++;

                    }
                    while (stc[i] == '\0' || stc[i] == ' ')//�ܾ��� ������ ����Ű�� �˰���
                    {
                        i++;
                    }


                    if (stc[i] == 'A')//������ �������� ��� while �� ����
                    {
                        break;
                    }
                }//���忡�� �ܾ� �� sent�迭�� ����

                float ham = (float)num_ham[0] / (num_ham[0] + num_spam[0]);
                float spam = (float)num_spam[0] / (num_ham[0] + num_spam[0]);

                printf("\n");
                printf("P(Ham)=%.3f, ", ham);
                printf("P(Spam)=%.3f\n", spam);
                printf("\n");

                int ck, cl;

                for (ck = 0; ck < cnt_stc; ck++)//�Է��� ���忡 �ִ� �ܾ train�ߴ� �ܾ�� ��ġ�ϴ��� �Ǵ��ϴ� �˰���. �� ��������Naive Bayes Classifier�� ���ȴ�
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
                dltetr(stcc);//stc���� '\n'�� �����Ƿ�, �̸� �����ؼ� ����ؾ��Ѵ�
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
            return 0;//���α׷� ����
        }
        else//test train exit �̿��� �ܾ �Է��� ���
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
                enter = 0;//Enter������ enter=0�� �Ǽ� while���� �ٽ� ���ư���
                
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