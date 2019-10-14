/*

Given a set of numbers, check whether it can be partitioned into two subsets such that the sum of elements in both subsets is same or not.

Subset Sum Problem : 
T = No. of Test Cases
N = no. of elements into the array
n1 n2 n3 .. N elements 

Sum k = n1+n2+n3 ... /2

Columns = k+1;
Rows = N;

First Column True i.e. 1 because we can form 0 with empty Set
First Row if arr[i] == j, then 1 else 0(False)

if (arr[i] > j)
	take value from Top

else
	move 1 row above and then check just above value, if false then go arr[i] steps back i.e arr[i][j] = arr[i-1][j-arr[i]] else take value from top

*/

#include "Functions.h"

void SubsetSumUtil(int *arr, int N)
{
	int k = 0;
	for (int i = 0; i < N; i++)
		k = k + arr[i];

	if (k % 2 != 0)
	{
		printf("NO\n");
		return;
	}
	
	k = k / 2;	//as array could be partitioned into halves or not : so Sum shall be same of 2 partitioned arrays
	
	int **T = (int **)malloc(sizeof(int *)*N);	//N Rows
	if (!T)
		return;

	for (int i = 0; i < N; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*(k+1));	//k = expected SUM i.e. (Sum of All elements)/2
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(int)*(k+1));	//0 = False; 1 = True
	}

	for (int i = 0; i < N; i++)
		T[i][0] = 1;	//making first column all True

	for (int j = 1; j <= k; j++)
	{
		if (j == arr[0])	//First Row Fill only as 1 element can only add upto equal to itself 
			T[0][j] = 1;
	}

	//Filling up table now
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			if (j < arr[i])
				T[i][j] = T[i - 1][j];

			else
				T[i][j] = T[i - 1][j] || T[i - 1][j - arr[i]];
		}
	}

	/*for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <= k; j++)
			printf("%d  ", T[i][j]);

		printf("\n");
	}*/
	

	if (T[N - 1][k])	//Last bottom right South East Corner element 
		printf("YES\n");
	else
		printf("NO\n");

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

void SubsetSum()
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

		if (N < 2)
		{
			printf("NO");
			continue;
		}

		int *arr = (int *)malloc(sizeof(int)*N);
		if (!arr)
			return;

		else if (N == 2)
		{
			fscanf(fp, "%d", &arr[0]);
			fscanf(fp, "%d", &arr[1]);

			if (arr[0] == arr[1])
				printf("YES");
			else
				printf("NO");

			continue;
		}

		else
		{
			for (int i = 0; i < N; i++)
				fscanf(fp, "%d", &arr[i]);
		}

		SubsetSumUtil(arr, N);	

		if (arr)
			free(arr);

	}

	//close file pointer
	fclose(fp);
}