/*
In this problem you have to find minimum trials to solve for n eggs and k floors.

T : Test Cases 
n k : n = no of eggs & k = no. of floors

Rows = 0 to n : Total n+1
Columns : 0 to k : Total k+1

First row & First Column = 0:

Second Row i.e. Row 1 (Not 0) : 1 egg and j floors
	T[i][j] = j;

Rest table : 
if(i > j)
	T[i][j] = take value from top
else
	T[i][j] = 1 + min(max of j iterations)
*/

#include "Functions.h"
#define INT_MAX 999999999

void EggDropUtil(int n, int k)
{
	int **T = (int **)malloc(sizeof(int *)*(n+1));	//N Rows
	if (!T)
		return;

	for (int i = 0; i < n+1; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*(k+1));	//k = expected SUM i.e. (Sum of All elements)/2
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(int)*(k+1));	//As first column is 1, so memset to 1
	}

	//1 extra row and column i.e. 0th : For ease of calculations

	//For 1st Row
	for (int j = 1; j < k+1; j++)
		T[1][j] = j;

	for (int i = 2; i < n+1; i++)
	{
		for (int j = 1; j < k+1; j++)
		{
			if (i > j)
				T[i][j] = T[i - 1][j];

			else
			{
				int max = 0;
				int min = INT_MAX;
				for (int l = 1; l <= j; l++)	//We need to do j iterations for each floor combination (Egg breaks vs Egg does not break at floor l (1 to j)
				{
					if (l == j)
						max = T[i - 1][l - 1] > T[i][j - 1] ? T[i - 1][l - 1] : T[i][j - 1];
					
					else
						max = T[i - 1][l - 1] > T[i][j - l] ? T[i - 1][l - 1] : T[i][j - l];

					min = min < max ? min : max;
				}
				T[i][j] = 1 + min;
			}
		}
	}

	printf("%d\n", T[n][k]);

	//Free memory after printing result
	if (T)
	{
		for (int i = 0; i < n; i++)
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

void Egg_Drop()
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
		int n,k;
		
		fscanf(fp, "%d", &n);
		fscanf(fp, "%d", &k);

		if (n < 1)
		{
			printf("%d\n", n);
			continue;
		}
			
		
		if (n < 2)
		{
			printf("%d\n", k);
			continue;
		}

		EggDropUtil(n, k);		

	}

	//close file pointer
	fclose(fp);
}