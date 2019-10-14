/*
Given a value V, if we want to make change for V cents,
and we have infinite supply of each of C = { C1, C2, .. , Cm} valued coins,
what is the minimum number of coins to make the change?

T : Test Cases
V N : Value to make up & N Total array elements (different coins present)
N1 N2 N3 ... Till N : Cents Value Denomination (Infinite Supply)

Rows = N
Columns = V+1 i.e 0 to V

1st Column = 0

1st Row : 
if(j%arr[0])
	T[i][j] = INT_MAX;
else
	T[i][j] = j/arr[0];

Rest rows : 
if(j<arr[i])
	T[i][j] = Value from top
else
	T[i][j] = min(Value from top, T[i][j-arr[i]] + 1);



*/

#include "Functions.h"
#define INT_MAX 999999999

void CoinChangeMinRequiredUtil(int *arr, int N, int V)
{
	int **T = (int **)malloc(sizeof(int *)*N);	//N Rows
	if (!T)
		return;

	for (int i = 0; i < N; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*(V + 1));	
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(int)*(V + 1));	
	}

	//First Row i.e 0th row initialise
	for (int j = 1; j <= V; j++)
	{
		if (j < arr[0])
			T[0][j] = INT_MAX;

		else if (j % arr[0])
			T[0][j] = INT_MAX;
		
		else
			T[0][j] = j/arr[0];
	}

	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j <= V; j++)
		{
			if (j < arr[i])
				T[i][j] = T[i - 1][j];
			else
			{
				T[i][j] = T[i - 1][j] < T[i][j - arr[i]] + 1 ? T[i - 1][j] : T[i][j - arr[i]] + 1;
					//if (T[i][j] < 0)	//Special handling since we have some -1 in first row 
					//	T[i][j] = T[i][j - arr[i]] + 1;
					
			}
				
		}
	}
	
	if (T[N - 1][V] >= INT_MAX)
		printf("%d\n", -1);
	else
		printf("%d\n", T[N - 1][V]);

	//Free memory after printing result
	if (T)
	{
		for (int i = 0; i < N; i++)
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

void coin_change_min_reqd()
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
		int V;
		fscanf(fp, "%d", &V);
		if (!V)
		{
			printf("%d\n", V);
			continue;
		}
		
		int N;
		fscanf(fp, "%d", &N);

		if (N < 1)
		{
			printf("%d\n", N);
			continue;
		}

		int *arr = (int *)malloc(sizeof(int)*N);
		if (!arr)
			return;
		
		if (N == 1)
		{
			fscanf(fp, "%d", &arr[0]);			

			if (V % arr[0] == 0)
				printf("%d\n", V/arr[0]);	//No. of coins required
			else
				printf("%d\n", -1);

			continue;
		}

		else
		{
			for (int i = 0; i < N; i++)
				fscanf(fp, "%d", &arr[i]);

		}

		CoinChangeMinRequiredUtil(arr, N, V);

		if (arr)
			free(arr);

	}

	//close file pointer
	fclose(fp);
}