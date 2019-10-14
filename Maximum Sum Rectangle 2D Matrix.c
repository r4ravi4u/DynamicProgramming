/*
Given a 2D array, find the maximum sum subarray in it. For example, in the following 2D array, the maximum sum subarray is highlighted with blue rectangle and sum of this subarray is 29.

First line of every test case consists of T test case. First line of every test case consists of 2 integers R and C , denoting number of rows and columns. Second line consists of R*C spaced integers denoting number of elements in array.

T : Test Cases
R C : Rows & Columns
n1 n2 ... R*C elements : Matrix Elements Row Wise

R X C 2D Matrix
L & R : to mark maxL & maxR (Left & Right) will move from Left to Right only
L from 0 to C-1
R from L to C-1

1D array of length = R, to caculate current SUM & update required values (Previous column to be added to new Column) as R moves
When R resets to L, this 1D array also resets to C Column values

Kadane's Algo to be used to find below stuff : 
1. CurrentSum : To store current Sum
2. maxTop : Top Index from 1D array which takes to currentSUM . Its only updated when currentSum > maxSum
3. maxDown : Down Index from 1D array which takes to currentSUM . Its only updated when currentSum > maxSum

maxSum = maxSum > currentSum ? maxSum : CurrentSum

when currentSum > maxSum
{
	maxLeft = L 
	maxRight = R
	maxTop = 1D array index1
	maxDown = 1D array index2

	index1 & index2 are the boundary indexes which has max. sum subarray using kadane's algo

	//But since only we are interested in maxSUM, so NO need to maintain indices Left, Right, Top & Down
}

*/

#include "Functions.h"
#define INT_MIN -999999999

int kadane(int *T, int R)	//R = len of T	//only works when their is atleast 1 positive element in the array
{
	int max_sum = 0;	//since this algo only works when their is atleast 1 element positive
	int sum = 0;	//sum till now
	for (int i = 0; i < R; i++)
	{
		sum += T[i];
		if (sum < 0)
			sum = 0;

		max_sum = max_sum > sum ? max_sum : sum;
	}

	return max_sum;
}

void MaxSumRectSubMatrixUtil(int **M, int R, int C)
{
	int *T = (int *)malloc(sizeof(int)*R);
	if (!T)
		return;

	memset(T, 0, sizeof(int)*R);
		
	int max_sum = INT_MIN;
	//i = L, j = R as per above comments
	for (int i = 0; i < C; i++)	//From Left to Right
	{
		int cur_sum = 0;
		memset(T, 0, sizeof(int)*R);
		for (int j = i; j < C; j++)
		{
			for (int k = 0; k < R; k++)	//For initialising T array for CurrentSum by applying Kadane's Algo on T
				T[k] += M[k][j];

			cur_sum = kadane(T, R);	//O(n) Kadane Algo to find Max Sum Subarray (Contiguous)

			max_sum = max_sum > cur_sum ? max_sum : cur_sum;
		}
	}

	printf("%d\n", max_sum);

	//Free memory after printing result
	if (T)
	{
		free(T);
		T = NULL;
	}
}

void Max_Sum_Rectangular_SubMatrix()
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
		int R, C;
		fscanf(fp, "%d", &R);
		fscanf(fp, "%d", &C);

		if (R*C < 1)
		{
			printf("%d\n", R*C);
			continue;
		}
		
		if (R*C == 1)
		{
			int arr;
			fscanf(fp, "%d", &arr);
			printf("%d\n", arr);
			continue;
		}

		int **M = (int **)malloc(sizeof(int *)*R);	
		if (!M)
			return;

		for (int i = 0; i < R; i++)
		{
			M[i] = (int *)malloc(sizeof(int)*C);	
			if (!M[i])
				return;

			memset(M[i], 0, sizeof(int)*C);	
		}

		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				fscanf(fp, "%d", &M[i][j]);

		MaxSumRectSubMatrixUtil(M, R, C);

		//Free memory after printing result
		if (M)
		{
			for (int i = 0; i < R; i++)
			{
				if (M[i])
				{
					free(M[i]);
					M[i] = NULL;
				}

			}
			free(M);
			M = NULL;
		}

	}

	//close file pointer
	fclose(fp);
}