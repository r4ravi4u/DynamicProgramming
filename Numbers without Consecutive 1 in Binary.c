/*
Count number of binary strings without consecutive 1’s

Problem Description:
Given a positive integer N, count all possible distinct binary strings of length N such that there are no consecutive 1’s. Output your answer mod 10^9 + 7.

T : Test Cases
N : till 2^N - 1

T[0] = 1
T[1] = 2
T[2] = 3

T[N] = T[N-1] + T[N-2] -> Fibonacci Series (same as staircase problem)

We shall use memoization to compute Fibonacci, so as to save time & space

*/

#include "Functions.h"

int Fibonacci(int N, int *F)
{
	if (F[N])
		return F[N];

	F[N] = (Fibonacci(N - 1, F) + Fibonacci(N - 2, F)) % 1000000007;

	return F[N];
}

void ConsecutiveOneNotAllowed()
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

		if (N < 3)
		{
			printf("%d\n", N+1);
			continue;
		}

		int *F = (int *)malloc(sizeof(int)*(N+1));
		if (!F)
			return;

		memset(F, 0, sizeof(int)*(N+1));

		F[0] = 1;
		F[1] = 2;
		F[2] = 3;

		printf("%d\n", Fibonacci(N, F));

		if (F)
		{
			free(F);
			F = NULL;
		}
			
	}

	//close file pointer
	fclose(fp);
}