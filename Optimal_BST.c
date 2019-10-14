/*

Optimal Binary Search Tree : 
Given a sorted array keys[0.. n-1] of search keys and an array freq[0.. n-1] of frequency counts, where freq[i] is the number of searches to keys[i]. Construct a binary search tree of all keys such that the total cost of all the searches is as small as possible.
Let us first define the cost of a BST. The cost of a BST node is level of that node multiplied by its frequency. Level of root is 1.

T = No. of Test Cases
N = No. of Keys (Nodes)
n1 n2 n3 .. : Keys (Values based on which BST shall be formed)
f1 f2 f3 ... : Frequency of searches of corresponding keys

Rows = N : 0 to N-1
Columns = N : 0 to N-1

Diagonal elements start and will fill table in North East Direction : Top Right Corner is Answer

T[i][i] = Freq[i] (Key Array is sorted) For First Diagonal elements  i.e. when i=j

T[i][j] = Sum of All frequencie from i to j + min of left side T[i][j] and Right side T[i][j]

*/

#include "Functions.h"
#define INT_MAX 9999999999

void optimal_BSTUtil(int *key, int *freq, int N)
{
	int **T = (int **)malloc(sizeof(int *)*N);	//Here N = N-1
	if (!T)
		return;

	for (int i = 0; i < N; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*N);	//Here N = N-1
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(int)*N);
	}
	
	int *sum = (int *)malloc(sizeof(int)*(N-1));	//to store SUMs of the elements till the index they have encountered
	if (!sum)
		return;
	memset(sum, 0, sizeof(int)*(N-1));
	/*sum[0] = 01 -> 012 -> 0123 .. & so on sum 
	sum[1] = 12, 123, 1234 ...
	& so on ..
	so that each time we need not to scan whole array, to save time
	*/
	
	for (int i = 0; i < N; i++)
		T[i][i] = freq[i];

	//make a backup copy of N so as to use it in iterations
	int N_copy = N - 1;

	int k = 1;	//means difference between row and column in each iteration

	while (N_copy)	//Total iterations to fill Till right top T[0][N-1]
	{
		for (int i = 0; i < N_copy; i++)	//Diagonal elements filling up 1 by 1 going towards North East direction
		{
			if (k == 1)
			{
				sum[i] += freq[i] + freq[i + 1];
				T[i][i + k] = T[i][i] < T[i + 1][i + 1] ? T[i][i] : T[i + 1][i + 1];
				T[i][i + k] += sum[i];
			}
				
			else
			{
				int min = INT_MAX;
				int curr_value = 0;

				//j will act as partition : A-BCD .. ; AB-CD...
				//when j=0 or j=k : Boundary partitions,
				for (int j = 0; j <= k; j++)	//As there shall be k possibilities for each cell and we have to take minimum of All, 
				{
					if (j == 0)	//first node as root 
					{
						curr_value = T[i + 1][k + i];
					}

					else if (j == k)	//last node as root
					{
						curr_value = T[i][k + i - 1];
					}

					else //left side also a BST and right side also a BST
					{
						curr_value = T[i][j + i - 1] + T[j + i + 1][k + i];
					}

					min = min < curr_value ? min : curr_value;
				}
				sum[i] += freq[i + k];
				T[i][i + k] = sum[i] + min;
			}
		//	printf("%d\t", T[i][i + k]);
		}
	//	printf("\n");
		k++;
		N_copy--;
	}
	
	printf("%d\n", T[0][N - 1]);
	
	//Free memory after printing result
	if (sum)
		free(sum);
	
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

void optimal_BST()
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
			printf("%d", N);
			continue;
		}

		int *key = (int *)malloc(sizeof(int)*N);
		if (!key)
			return;

		int *freq = (int *)malloc(sizeof(int)*N);
		if (!freq)
			return;

		if (N == 1)
		{
			fscanf(fp, "%d", &key[0]);
			fscanf(fp, "%d", &freq[0]);

			printf("%d", key[0] * freq[0]);
			continue;
		}

		for (int i = 0; i < N; i++)
				fscanf(fp, "%d", &key[i]);

		for (int i = 0; i < N; i++)
			fscanf(fp, "%d", &freq[i]);

		optimal_BSTUtil(key, freq, N);

		if (key)
			free(key);

		if (freq)
			free(freq);

	}

	//close file pointer
	fclose(fp);
}