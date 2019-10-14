/*
0/1 Knapsack problem : Geek OK
Weight = wt
value associated = val
W = Max weight limit

Rows = Total no. of items (1 each) (Do not take 1 extra)
Columns = 0 to W

T[i][j] = 0 for first column

T[i][j] = max(T[i-1][j], wt[i] + T[i-1][j-wt[i]];
T[i-1][j] means current item not included
wt[i] + T[i-1][j-wt[i]] : means current item included and for remaining weight incl from above row by going back

The first line of input contains an integer T denoting the number of test cases. Then T test cases follow. Each test case consists of four lines. The first line consists of N the number of items. The second line consists of W, the maximum capacity of the knapsack. In the next  line are N space separated positive integers denoting the values of the N items and in the fourth line are N space separated positive integers denoting the weights of the corresponding items.

T : Test Cases
N : no. of items
W : max. capacity
n1 n2 n3 ... : items value
w1 w2 w3 ... : items weight

*/

#include "Functions.h"

typedef struct Item
{
	int wt;
	int val;
}Item;

void knapsackUtil(int N, int W, Item *item)
{
	int **T = (int **)malloc(sizeof(int *)*N);	//Total Rows = N
	if (!T)
		return;

	for (int i = 0; i < N; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*(W + 1));	//1 extra for 0 Column as we have columns 0 to W
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(int)*(W + 1));
		
	}
	// our 2D array has been designed above

	//Fill up first row so as to fill below rows later on based on formula in comments above
	for (int j = 0; j <= W; j++)	//since T[0][0] shall be 0
	{
		while (j < item[0].wt && j <= W)
		{
			j++;
			continue;	//since already memset to 0 else we shall not make it 0 explicitly
		}
			

		if (j > W)
			break;

		T[0][j] = item[0].val;
	}

	//Now fill rest of the table row wise
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j <= W; j++)
		{
			while (j < item[i].wt && j <= W)
			{
				T[i][j] = T[i - 1][j];
				//printf("%d\t", T[i][j]);
				j++;
				continue;
			}

			if (j > W)
				break;

			T[i][j] = T[i - 1][j] >(item[i].val + T[i - 1][j - item[i].wt]) ? T[i - 1][j] : (item[i].val + T[i - 1][j - item[i].wt]);
			//printf("%d\t", T[i][j]);
		}
		//printf("\n");
	}

	//int max = T[N - 1][W] > T[N - 2][W] ? T[N - 1][W] : T[N - 2][W];

	printf("%d\n", T[N - 1][W]);

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

void knapsack()
{
	//file pointer
	FILE *fp;

	//opening/creation of file
	fp = fopen("Test.txt", "r");

	//sets the file position to the beginning of the file
	rewind(fp);

	int T, N, W;

	fscanf(fp, "%d", &T);
	while (T--)
	{
		fscanf(fp, "%d", &N);
		Item *item = (Item *)malloc(sizeof(Item)*N);	//pointer array to store N items val, wt
		if (!item)
			return;

		fscanf(fp, "%d", &W);

		for (int i = 0; i < N; i++)
			fscanf(fp, "%d", &item[i].val);

		for (int i = 0; i < N; i++)
			fscanf(fp, "%d", &item[i].wt);

		knapsackUtil(N, W, item);

		if (item)
		{
			free(item);
			item = NULL;
		}

	}

	//close file pointer
	fclose(fp);
}