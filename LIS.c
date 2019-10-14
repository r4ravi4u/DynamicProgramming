/*
Longest Increasing Subsequence : 
The longest increasing subsequence means to find a subsequence of a given sequence in which the subsequence's elements are in sorted order, lowest
to highest, and in which the subsequence is as long as possible. This subsequence is not necessarily contiguous, or unique.

Duplicate numbers are not counted as increasing subsequence.

For example:
length of LIS for
{ 10, 22, 9, 33, 21, 50, 41, 60, 80 } is 6 and LIS is {10, 22, 33, 50, 60, 80}.

T : Test Cases
N : Array Size N elements
N1 N2 ... N : Array elements

Table T will be 1D only here. 

initially T[i] = 1 (All); Since length of subsequence shall be >= 1 in any case

j start from 0 and i start from 1 
i = 1 to N-1
j = 0 to i-1

if (arr[j] < arr[i])
	T[i] = max(T[i], T[j]+1);

j++;	

*/

#include "Functions.h"

void LISUtil(int *arr, int N)
{
	int *T = (int *)malloc(sizeof(int)*N);	//N Rows
	if (!T)
		return;

	for (int i = 0; i < N; i++)
		T[i] = 1;

	int max = 1;
	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[j] < arr[i])
				T[i] = T[i] > T[j] + 1 ? T[i] : T[j] + 1;

		}
		max = max > T[i] ? max : T[i];
	}

	printf("%d\n", max);

	//Free memory after printing result
	if (T)
	{
		free(T);
		T = NULL;
	}

}

void LIS()
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
			printf("%d\n", N);
			continue;
		}

		int *arr = (int *)malloc(sizeof(int)*N);
		if (!arr)
			return;

		if (N == 2)
		{
			fscanf(fp, "%d", &arr[0]);
			fscanf(fp, "%d", &arr[1]);

			if (arr[0] < arr[1])
				printf("%d\n", N);
			else
				printf("%d\n", N-1);

			continue;
		}

		else
		{
			for (int i = 0; i < N; i++)
				fscanf(fp, "%d", &arr[i]);

		}

		LISUtil(arr, N);

		if (arr)
			free(arr);

	}

	//close file pointer
	fclose(fp);
}