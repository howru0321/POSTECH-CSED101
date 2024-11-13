#include <stddef.h>

int mystrlen(char* str){
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

int mystrcmp(char* str1, char* str2){
	int i = 0;
	while (str1[i] == str2[i])
	{
		i++;
		if (str1[i] == '\0' && str2[i] == '\0')
		{
			return 0;
		}
	}
	if (str1[i] == '\0')
	{
		return -1;
	}
	else if (str2[i] == '\0')
	{
		return 1;
	}
	else if (str1[i] < str2[i])
	{
		return -1;
	}
	else if (str1[i] > str2[i])
	{
		return 1;
	}
}

char* mystrcpy(char* toStr, char* fromStr){
	int i = 0;
	while (fromStr[i] != '\0')
	{
		toStr[i] = fromStr[i];
		i++;
	}
	toStr[i] = '\0';
	return toStr;
}

char* mystrlower(char* str){
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