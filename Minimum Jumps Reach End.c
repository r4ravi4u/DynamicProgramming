/*
Given an array of integers where each element represents the max number of steps that can be made forward from that element. Write a function to return the minimum number of jumps to reach the end of the array (starting from the first element). If an element is 0, then cannot move through that element.

T : test cases
N : Array Length
n1 n2 .. : Array elements representing how much far from this cell, you can jump i.e range of jump, if first element is 0, we can not reach to end

if arr[i] = k : means our range of jump is i+1, i+2 ... i+k

1D Table T of length N is required to store jumps

T[0] = 0;

Rest Table : 
i start from 1 to N-1
j start from 0 to i-1

if(i-j >= arr[j]) then only it can jump
	T[i] = T[j]+1

*/

#include "Functions.h"

void MinJumpReachEndUtil(int *arr, int N)
{

	int *T = (int *)malloc(sizeof(int)*N);	//N Rows
	if (!T)
		return;

	memset(T, 0, sizeof(int)*N);

	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[j] >= i - j)
				if (!T[i])
					T[i] = T[j] + 1;
				else
					T[i] = T[i] < T[j] + 1 ? T[i] : T[j] + 1;
		}
	}

	if (!T[N - 1])
		printf("%d\n", T[N - 1] - 1);
	else
		printf("%d\n", T[N - 1]);

	//Free memory after printing result
	if (T)
	{
		free(T);
		T = NULL;
	}
}

void min_jump()
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


		if (N < 2)	//0 or 1 day only, so profit can be made
		{
			printf("%d\n", N);
			continue;
		}
		
		int *arr = (int *)malloc(sizeof(int)*N);
		if (!arr)
			return;

		for (int i = 0; i < N; i++)
			fscanf(fp, "%d", &arr[i]);

		if (!arr[0])	//means 1st element is 0, hence we can't jump and hence can't reach to end
			printf("%d\n", -1);

		else
			MinJumpReachEndUtil(arr, N);

		if (arr)
			free(arr);

	}

	//close file pointer
	fclose(fp);
}