/*
A string is called a square string if it can be obtained by concatenating two copies of the same string. For example, "abab", "aa" are square strings, while "aaa", "abba" are not. Given a string, how many (non-empty) subsequences of the string are square strings? A subsequence of a string can be obtained by deleting zero or more characters from it, and maintaining the relative order of the remaining characters.
*/

#include "Functions.h"

#include <string.h>

#define LEN 201	//200 + 1 extra for NULL char
#define MOD 1000000007

void SquareSubsequenceUtil(char* str, int len)
{
	int **T = (int **)malloc(sizeof(int *)*(len + 1));	//Total Rows = len + 1
	if (!T)
		return;

	for (int i = 0; i <= len; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*(len + 1));	//Total Columns = len + 1
		if (!T[i])
			return;

	}

	int ans = 0;

	//In this, Table will be set to 0 after each split iteration
	for (int split = 1; split < len; split++)
	{
		for (int i = 0; i <= split; i++)
			memset(T[i], 0, sizeof(int)*(len - split + 1));

		//Fill first column i.e not 0 but 1
		for (int i = 1; i <= split; i++)
		{
			if (str[i - 1] == str[split])
				T[i][1] = 1;
		}

		//Now fill Table for each split
		for (int i = 1; i <= split; i++)
		{
			for (int j = 1; j <= len - split; j++)
			{
				T[i][j] += T[i - 1][j] + T[i][j - 1];
				if (str[i - 1] != str[split + j - 1])
					T[i][j] -= T[i - 1][j - 1];
				
				T[i][j] %= MOD;
			}
		}
		ans += T[split][len - split];
		ans %= MOD;
	}

	printf("%d\n", ans);

	//mem clear after usage
	if (T)
	{
		for (int i = 0; i <= len; i++)
		{
			if (T[i])
			{
				free(T[i]);
				T[i] = NULL;
			}

		}
		free(T);
		T = NULL;
	}
}

void SquareSubsequence()
{
	
	FILE *fp = fopen("Test.txt", "r");

	int T;

	fscanf(fp, "%d", &T);
	while (T--)
	{
		char *str = (char *)malloc(sizeof(char)*LEN);
		if (!str)
			return;

		fscanf(fp, "%s", str);

		int len = strlen(str);
	
		SquareSubsequenceUtil(str, len);

		if (str)
		{
			free(str);
			str = NULL;
		}
	}

	//close file pointer
	fclose(fp);
}