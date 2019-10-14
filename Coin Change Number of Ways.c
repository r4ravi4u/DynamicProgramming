/*
Given a value N, find the number of ways to make change for N cents, if we have infinite supply of each of S = { S1, S2, .. , Sm} valued coins. The order of coins doesn’t matter. For example, for N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}. So output should be 4. For N = 10 and S = {2, 5, 3, 6}, there are five solutions: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}. So the output should be 5.

T : Test Cases
N : No. of elements
N1 N2 N3 .. : Array Elements (Unlimited supply of coins)
V : Value to Get combining cents A1 A2 ..

Rows = N : Coins values elements
Columns : V+1 : 0 to V

First Column is set to 1;

For First Row : 
if(V % arr[i] == 0)
	T[0][j] = 1;
else
	T[0][j] = 0;

if arr[i] > j
	T[i][j] = Value from Top
else
	T[i][j] = Value from Top + T[i][j-arr[i]]
*/

#include "Functions.h"

void CoinChangeWaysUtil(int *arr, int N, int V)
{
	int **T = (int **)malloc(sizeof(int *)*N);	//N Rows
	if (!T)
		return;

	for (int i = 0; i < N; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*(V + 1));	//V+1 Columns 0 to V
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(int)*(V + 1));	

		printf("%d ", arr[i]);
	}

	//Fill first 0th row as per % style
	for (int j = 1; j <= V; j++)
	{
		if (j % arr[0] == 0)
			T[0][j] = 1;
	}

	//Fill First 0th Column as 1
	for (int i = 0; i < N; i++)
		T[i][0] = 1;

	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j <= V; j++)
		{
			if (j < arr[i])
				T[i][j] = T[i - 1][j];	//value from top
			else
				T[i][j] = T[i - 1][j] + T[i][j - arr[i]];

			if (T[i][j] < 0)
				return;

			//printf("%d ", T[i][j]);
		}
		//printf("%d\n");
	}

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

void coin_change_ways()
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

		int V;
		if (N == 1)
		{
			fscanf(fp, "%d", &arr[0]);
			fscanf(fp, "%d", &V);
			
			if (V%arr[0] == 0)
				printf("%d\n", 1);	//only 1 way
			else
				printf("%d\n", 0);

			continue;
		}

		else
		{
			for (int i = 0; i < N; i++)
				fscanf(fp, "%d", &arr[i]);

			fscanf(fp, "%d", &V);
		}

		if (!V)
		{
			printf("%d\n", V);
			continue;
		}

		CoinChangeWaysUtil(arr, N, V);

		if (arr)
			free(arr);

	}

	//close file pointer
	fclose(fp);
}