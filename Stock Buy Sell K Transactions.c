/*
In stock market , a person buys a stock and sells it on some future date. Given the stock prices of N days in an form of an array A[ ] and a positive integer K, find out the maximum profit a person can make in atmost K transactions. A transaction is equivalent to (buying + selling) of a stock and new transaction can start only when the previous transaction has been completed.

T = Test Cases
K = No. of transactions
N = No. of Days i.e. Array length
n1 n2 ... = Prices of each day

Table T : Stores Profit
Rows = 0 to K = K+1 Rows
Columns = N : 0 to N-1

First Row = 0 -> If 0 transactions allowed, no profit can be made
First Column = 0 -> If only 1 day (first day), we can only buy, can not sell, hence no profit can be made

Rest Table : 
T[i][j] = max(T[i][j-1], MaxDiff + Price on jth Day);

T[i][j-1] : Left element i.e not transacting on the jth day
MaxDiff + Price on jth Day : Transacting i.e. Selling on the jth day, so we can buy that stock on any day from 0 to j-1 days

MaxxDiff : used, so that we shall not go from 0 to j-1 days for each cell iteration
MaxDiff = max(Maxdiff, T[i-1][j-1] - Price at j-1) Diagonal cell - Price on that day itself

*/

#include "Functions.h"
#define INT_MIN -9999

void StockBuySellKTransactionUtil(int K, int N, int *arr)
{
	int **T = (int **)malloc(sizeof(int *)*(K + 1));	//Total Rows = len2 + 1
	if (!T)
		return;

	for (int i = 0; i <= K; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*N);	//Total Columns = len1 + 1
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(int)*N);

	}

	//First Row and Column already set to 0, so start to fill rest of the table
	
	for (int i = 1; i <= K; i++)
	{
		int MaxDiff = INT_MIN;
		for (int j = 1; j < N; j++)
		{
			MaxDiff = MaxDiff > (T[i - 1][j-1] - arr[j - 1]) ? MaxDiff : T[i - 1][j-1] - arr[j - 1];

			T[i][j] = T[i][j - 1] > MaxDiff + arr[j] ? T[i][j - 1] : MaxDiff + arr[j];

			printf("%d\t", T[i][j]);
		}
		printf("\n\n");
	}

	printf("%d\n", T[K][N - 1]);

	//Free mem
	if (T)
	{
		for (int i = 0; i <= K; i++)
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

void Stock_Buy_Sell_K_Transactions()
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
		int K;

		fscanf(fp, "%d", &K);

		if (K < 1)	//0 transactions allowed
		{
			printf("%d\n", 0);
			continue;
		}

		int N;
		fscanf(fp, "%d", &N);	

		if (N < 2)	//0 or 1 day only, so profit can be made
		{
			printf("%d\n", 0);
			continue;
		}

		int *arr = (int *)malloc(sizeof(int)*N);
		if (!arr)
			return;

		int  d = 0, flag = 0;
		for (int i = 0; i < N; i++)
		{
			fscanf(fp, "%d", &arr[i]);

			if (i > 0)	//check if prices are in decreasing order, If Yes then no profit can be made
			{
				d = arr[i - 1];
				if (arr[i] > d)
					flag = 1;
			}
		}
		if (!flag)	//for for sorted non increasing order, profit is 0
		{
			printf("%d\n", 0);
			continue;
		}

		StockBuySellKTransactionUtil(K, N, arr);

		if (arr)
			free(arr);

	}

	//close file pointer
	fclose(fp);
}