#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MATCH 100001
#define PATTERN 1001

void GetNext(int next[], char string[])
{
	int j = 0, k = -1;
	int length = strlen(string);
	next[0] = -1;
	while (j < length - 1)
	{
		if (k == -1 || string[j] == string[k])
			next[++j] = ++k;
		else
			k = next[k];
	}
}

int KMP(int i, char match[], char pattern[])
{
	int j = 0;
	int Plength = strlen(pattern);
	int Mlength = strlen(match);
	int* next = (int*)malloc(Plength * sizeof(int));
	GetNext(next, pattern);

	while (i < Mlength && j < Plength)
	{
		if (j == -1 || match[i] == pattern[j])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j >= Plength)
		return i - Plength;
	else
		return -1;
}

int func(char match[], char pattern[])
{
	int i = 0, j;
	int cnt = 0;
	int Mlength = strlen(match);
	while (i < Mlength)
	{
		j = KMP(i, match, pattern);
		if (j == -1)
			return cnt;
		else
		{
			i = j + 1;
			cnt++;
		}
	}
	return cnt;
}

int main()
{
	int T;
	char match[MATCH];
	char pattern[PATTERN];
	scanf("%d",&T);
	while (T > 0)
	{
		memset(match, '\0', MATCH);
		memset(pattern, '\0', PATTERN);
		scanf("%s", pattern);
		scanf("%s", match);
		
		printf("%d\n", func(match, pattern));
		T--;
	}
	return 0;

	/*char match[] = "ccaaaba";
	char pattern[]="aba";
	printf("%d\n", func(match, pattern));
	return 0;*/
}