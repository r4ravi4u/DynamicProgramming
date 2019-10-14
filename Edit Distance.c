/*
Given two strings str1 and str2 and below operations that can performed on str1. Find minimum number of edits (operations) required to convert ‘str1′ into ‘str2′.

T : test cases
len1 len2 : of str1 and str2
str1 str2 : str1 to str2 convert min operations

Rows : len2+1 (str2)
Columns : len1+1 (str1)

T[0][0] = 0;
First 0th Row : Null string comparing with str1
T[0][j] = j;

First 0th Column : Null string comparing with str2
T[i][0] = i;

Rest Table :
if(chars equal)
	diagonal element
else
	min(top, left, diagonal) + 1;

*/

#include "Functions.h"

void EditDistanceUtil(int len1, char *str1, int len2, char *str2)
{
	int **T = (int **)malloc(sizeof(int *)*(len2 + 1));	//Total Rows = len2 + 1
	if (!T)
		return;

	for (int i = 0; i <= len2; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*(len1 + 1));	//Total Columns = len1 + 1
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(int)*(len1 + 1));

	}

	//Filling First Column 0th : 
	for (int i = 1; i <= len2; i++)
		T[i][0] = i;

	//Filling First Row 0th : 
	for (int j = 1; j <= len1; j++)
		T[0][j] = j;

	//Fill Rest of the table
	for (int i = 1; i <= len2; i++)
	{
		for (int j = 1; j <= len1; j++)
		{
			if (str2[i - 1] == str1[j - 1])
				T[i][j] = T[i - 1][j - 1];
			else
			{
				T[i][j] = T[i - 1][j - 1] < T[i - 1][j] ? T[i - 1][j - 1] : T[i - 1][j];
				T[i][j] = T[i][j] < T[i][j - 1] ? T[i][j] + 1 : T[i][j - 1] + 1;
			}
				 
		}
	}

	/*for (int i = 0; i <= len2; i++)
	{
		for (int j = 0; j <= len1; j++)
		{
			printf("%d\t", T[i][j]);
		}
		printf("\n");
	}*/

	printf("%d\n", T[len2][len1]);

	//Free mem
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

void edit_distance()
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
			printf("%d\n", len1);
			continue;
		}
		else if (!len1)
		{
			printf("%d\n", len2);	//if len1 = 0 & len2 > 0, then LCS is 0
			char *str = (char *)malloc(sizeof(char)*len2);	//so that fp pointer gets to next usable part for next iteration as this string is of no use
			fscanf(fp, "%s", str);
			free(str);
			continue;
		}
		else if (!len2)
		{
			printf("%d\n", len1);
			char *str = (char *)malloc(sizeof(char)*len1);
			fscanf(fp, "%s", str);
			free(str);
			continue;
		}

		char *str1 = (char *)malloc(sizeof(char)*(len1 + 1));	//1 extra for last NULL char
		char *str2 = (char *)malloc(sizeof(char)*(len2 + 1));	//1 extra for last NULL char

		fscanf(fp, "%s", str1);
		fscanf(fp, "%s", str2);

		EditDistanceUtil(len1, str1, len2, str2);

		if (str1)
			free(str1);

		if (str2)
			free(str2);

	}

	//close file pointer
	fclose(fp);
}