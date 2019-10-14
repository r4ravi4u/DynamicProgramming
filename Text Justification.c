/*
Text Justification : Word Wrap
Given an array of size N, which denotes the number of characters in one word. The task is simple, count the number of words in a single line with space character between two words.

Input:
First line contains the number of test cases T. First line of every test case consists of N, denoting number of elements in array. Second line consists of elements in array. Third line consists of characters allowed per line.

Output:
Single line output,print 2*N spaced integers, denoting from which word to word in every line.(for more clearance of output, look the output in example).

T = Test Cases
N = No. of elements into array
l1 l2 l3 .. N elements : Denoting length of each word //Length of each word is < Width of the line W
W : Width of line : Max allowed chars per line incl spaces

2 words separated by space so space will also consume 1 place 

Suppose l1 l2 placed on same line so W >= l1+l2+1

left spaces in last : we need to do square

Table T : 
Rows = N
Columns = N

Table Filled up row wise diagonally means : lets say 4 x 4
1	1	1	1 -> row wise fill not diagonal wise, start from 0 to N-1
	1	1	1 -> 1 to N-1
		1	1 -> 2 to N-1 & so on ..
			1

But we will make full table as its required to maintain indices for 2 1D array that is going to fetch info from this 2D array

if(W >= from arr[i] to arr[j] + spaces (j-1))
	T[i][j] = (W - from arr[i] to arr[j] + spaces (j-1))^2
else
	T[i][j] = INF or -1

Once Table is built up, we will use this info to build up 2 arrays (Length = N) : will start building from last i,j = N-1 and then decrement to move from right to left
i will move from N-1 to 0 & j will move from N-1 to i (j will check that at which point breakup is done so that cost gets minimum, like partitions we do)
Array 1 : Min Cost for breakup 
Array 2 : From array index to value at index (taken from j into array 1), excluding value at index -> this array 2 will have answer from 0 to N-1 with partitions info
Ex. Array 2(if 4 elements)
0 1 2 3 -> Index (0 means 1st word)
0 3 3 4	-> 
means like this 
0
1 2
3

*/

#include "Functions.h"
#define INT_MAX 999999999

void TextJustificationWordWrapUtil(int *arr, int N, int W)
{
	//We will make full N X N table
	int **T = (int **)malloc(sizeof(int *)*N);	//Total Rows = len2 + 1
	if (!T)
		return;

	for (int i = 0; i < N; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*N);	//Total Columns = len1 + 1
		if (!T[i])
			return;

		//memset(T[i], 0, sizeof(int)*N);

	}

	//Initialise all elements of T with -1 (means Infinity INF)
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			T[i][j] = -1;

	for (int i = 0; i < N; i++)
	{
		int sum = 0;
		for (int j = i; j < N; j++)
		{
			sum += arr[j] + j - i;
			if (W >= sum)
				T[i][j] = (W - sum)*(W - sum);	//squares of left spaces
			else
				break;

		//	printf("%d\t", T[i][j]);
		}
		/*printf("\n");
		for (int j = 0; j <= i;j++)
			printf("\t");*/
	}

	//Table built properly above, checked

	int *arr_cost = (int *)malloc(sizeof(int)*N);
	int *arr_index = (int *)malloc(sizeof(int)*N);

	if (!arr_cost || !arr_index)
		return;

	memset(arr_cost, 0, sizeof(int)*N);
	memset(arr_index, 0, sizeof(int)*N);

	for (int i = N - 1; i >= 0; i--)	//Fill both 1D array from Right to Left
	{
		int min = INT_MAX;
		int min_index = -1;
		
		int j = N - 1;

		if (T[i][j] >= 0)
		{
			arr_cost[i] = T[i][j];
			arr_index[i] = j + 1;
		}
		else
		{
			for (j = N - 1; j > i; j--)
			{
				if (T[i][j - 1] >= 0)
				{
					if (min >= T[i][j - 1] + arr_cost[j])
					{
						min = T[i][j - 1] + arr_cost[j];
						min_index = j;
					}
				}
					
			}
			arr_cost[i] = min;
			arr_index[i] = min_index;
		}
		
	//	printf("%d : %d\n", arr_cost[i], arr_index[i]);
		
	}

	//our 1D arrays have been filled up properly now till here

	//Printinf arr_index array so that we can show which words line wise. Words r from 1 to N while index from 0 to N-1
	int i = 0, k=1;
	while (i < N)
	{
		if (arr_index[i] - i <= 1)	//means only this 1 word can come on this line
		{
			printf("%d %d ", i + 1, i + 1);
			i++;
			continue;
		}
		
		else	//means more than 1 words can be printed in this particular line
		{
			k = arr_index[i] - i;
			for (int j = 0; j < k; j++)
			{
				printf("%d ", i + 1);
				i++;
			}
			
		}
	}

	printf("\n");

	if (arr_cost)
		free(arr_cost);

	if (arr_index)
		free(arr_index);

	//make mem free
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

void Text_Justification_Word_Wrap()
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
			printf("%d %d\n", N, N);
			continue;
		}

		int *arr = (int *)malloc(sizeof(int)*N);

		int sum = 0;
		for (int i = 0; i < N; i++)
		{
			fscanf(fp, "%d", &arr[i]);
			sum += arr[i] + i;
		}

		int W;
		fscanf(fp, "%d", &W);	//Width of line

		if (W >= sum)	//means all words can be on same Line
			printf("%d %d\n", 1, N);

		else
			TextJustificationWordWrapUtil(arr, N, W);

		if (arr)
			free(arr);

	}

	//close file pointer
	fclose(fp);
}