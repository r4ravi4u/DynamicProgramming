/*
Longest Common Subsequence : 
LCS for input Sequences “ABCDGH” and “AEDFHR” is “ADH” of length 3.

LCS of "ABC" and "AC" is "AC" of length 2

T : no. of test cases
len1 len2 : len(str1) len(str2)
Str1
Str2

No. of Columns : Len1 + 1
No. of Rows : Len2 + 1

First Column and First Row = 0
Will start T[i][j] from 1,1

if (char at str2[i] != char at str1[j])
	T[i][j] = max(T[i-1][j], T[i][j-1]) -> Max of Top & Left
else //if same
	T[i][j] = T[i-1][j-1] + 1; Diagonal + 1

*/

#include "Functions.h"

void lcsUtil(int len1, char *str1, int len2, char *str2)
{
	int **T = (int **)malloc(sizeof(int *)*(len2+1));	//Total Rows = len2 + 1
	if (!T)
		return;

	for (int i = 0; i <= len2; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*(len1 + 1));	//Total Columns = len1 + 1
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(int)*(len1 + 1));

	}
	// our 2D array has been designed above

	//Filling Table : char of str1[i] comparing with str2[j],
	for (int i = 0; i < len2; i++)
	{
		for (int j = 0; j < len1; j++)
		{
			if (str1[j] == str2[i])	//Diagonal + 1
			{
				T[i + 1][j + 1] = T[i][j] + 1;
			}
			else //max(top, left)
			{
				T[i + 1][j + 1] = T[i][j + 1] > T[i + 1][j] ? T[i][j + 1] : T[i + 1][j];
			}
			printf("%d\t", T[i + 1][j + 1]);
		}
		printf("\n");
	}

	printf("%d\n", T[len2][len1]);

	if (T)
	{
		for (int i = 0; i <= len2; i++)
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

void LCS()
{
	//file pointer
	FILE *fp;

	//opening/creation of file
	fp = fopen("Test.txt", "r");

	//sets the file position to the beginning of the file
	rewind(fp);

	int T;

	fscanf(fp, "%d", &T);
	while (T--)
	{
		int len1, len2;
		fscanf(fp, "%d", &len1);
		fscanf(fp, "%d", &len2);

		if (!len1 && !len2)	
		{
			printf("%d", len1);
			continue;
		}
		else if (!len1)
		{
			printf("%d", len1);	//if len1 = 0 & len2 > 0, then LCS is 0
			char *str = (char *)malloc(sizeof(char)*len2);	//so that fp pointer gets to next usable part for next iteration as this string is of no use
			fscanf(fp, "%s", str);
			free(str);
			continue;
		}
		else if (!len2)
		{
			printf("%d", len2);
			char *str = (char *)malloc(sizeof(char)*len1);
			fscanf(fp, "%s", str);
			free(str);
			continue;
		}

		char *str1 = (char *)malloc(sizeof(char)*(len1+1));	//1 extra for last NULL char
		char *str2 = (char *)malloc(sizeof(char)*(len2 + 1));	//1 extra for last NULL char

		fscanf(fp, "%s", str1);
		fscanf(fp, "%s", str2);

		lcsUtil(len1, str1, len2, str2);

		if (str1)
			free(str1);

		if (str2)
			free(str2);

	}

	//close file pointer
	fclose(fp);
}