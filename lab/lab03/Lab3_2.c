#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char upperToLower(char c);
int getPosition(char c);

int main()
{
	char Uc;
	printf("Input a character in Uppercase : ");
	scanf("%c", &Uc);

	printf("Lowercase of Entered character is %c\n", upperToLower(Uc));
	printf("Position of '%c' in English Alpabets is %d\n", upperToLower(Uc), getPosition(Uc));

	return 0;
}

char upperToLower(char c)
{
	return c + ('a' - 'A');
}

int getPosition(char c)
{
	return c - 'A' + 1;
}