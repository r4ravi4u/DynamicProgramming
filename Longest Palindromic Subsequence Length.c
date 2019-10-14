/*/
Given a String, find the longest palindromic subsequence length

T : Test Cases
str : String to be checked
Length not given in Test Case input this time

Rows : len
Columns = len

Fills Diagonally elements
T[i][i] = 1, as lowest length could be 1

if(str[i] == str[j]) j shall be in terms of k
	T[i][j] = T[i+1][j-1] + 2;	//Lower Diagonal element
else
	T[i][j] = max(T[i][j-1], T[i+1][j]) //Max of Left & Lower same column

Fill elements in diagonal fashion only in Top Right Direction
*/

#include "Functions.h"
#define LEN 1001	//as max length is 1000 given

void LongestPalindromeSubsequenceLengthUtil(char *str, int len)
{
	int **T = (int **)malloc(sizeof(int *)*len);	//N Rows
	if (!T)
		return;

	for (int i = 0; i < len; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*len);	//k = expected SUM i.e. (Sum of All elements)/2
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(int)*len);	//As first column is 1, so memset to 1
	}

	//Filling all elements with 1
	for (int i = 0; i < len; i++)
		T[i][i] = 1;

	//make a backup copy of N so as to use it in iterations
	int len_copy = len - 1;

	int k = 1;	//means difference between row and column in each iteration

	while (len_copy)	//Total iterations to fill Till right top T[0][N]
	{
		for (int i = 0; i < len_copy; i++)	//Diagonal elements filling up 1 by 1 going towards North East direction
		{
			if (str[i] == str[i+k])
				T[i][i + k] = T[i + 1][i + k - 1] + 2;
			else
				T[i][i + k] = T[i][i + k - 1] > T[i + 1][i + k] ? T[i][i + k - 1] : T[i + 1][i + k];

			//printf("%d\t", T[i][i + k]);
		}
		//printf("\n");
		k++;
		len_copy--;
	}

	printf("%d\n", T[0][len - 1]);

	//Free memory after printing result
	if (T)
	{
		for (int i = 0; i < len; i++)
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

void longest_palindromic_subsequence()
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
		char *str = (char *)malloc(sizeof(char)*LEN);	//1 extra for last NULL char
		if (!str)
			return;

		memset(str, 0, sizeof(char)*LEN);
		
		fscanf(fp, "%s", str);

		int len = strlen(str);

		if (len < 2)
		{
			printf("%d\n", len);
			continue;
		}
			

		if (len == 2)
		{
			if (str[0] == str[1])
				printf("%d\n", len);
			else
				printf("%d\n", len-1);

			continue;
		}


		LongestPalindromeSubsequenceLengthUtil(str, len);

		if (str)
			free(str);
	}

	//close file pointer
	fclose(fp);
}