/*
Given a binary matrix, Your task is to complete the function maxArea which the maximum size rectangle area in a binary-sub-matrix with all 1’s. The function takes 3 arguments the first argument is the Matrix M[ ] [ ] and the next two are two  integers n and m which denotes the size of the matrix M. Your function should return an integer denoting the area of the maximum rectangle .

T = Test Cases
n m : size of matrix n rows, m columns
Binary Digits 1 0 ... : elements of Matrix having order n x m

1. Table T as 1D array created : Row 0 is inserted from Column 0 to n-1
2. i = 0 to n-1 
Table T is updated at each i : 
if matrix element is 0, element in T also become 0
if matrix element is 1, element in T becomes existing element + 1

3. At each T updation, we need to calculate area by histogram process (O(n) time)
4. if max_area < area calculated above, then only update max_area else not

Histogram Area method : 
int i, top, area, max_area //this max_area is different from above final max_area
1. Stack is created with size m (no. of columns as T will be having at max m Non Zero elements)
2. if first element is 0, move to next item until we found an element > 0
3. Push index of the Table T iff value at T[i] >= value at T[stack.top]
4. if above condition 3 is False, then keep removing element from the stack until we get the condition 3 True. Once we get this true, we push our index i into the stack and move forward
5. while removing element from the stack, we need to calculate area by either of below 2 method : 
a) if stack is empty
area = T[top] * i;	//i & top will be different, mind it
b) if stack is not empty
area = T[top] * (i - stack.top - 1)

6. if max_area < area found above, then only update max_area, else not
7. return max_area


*/

#include "Functions.h"

#define MAX 100

int HistogramArea(int *T, int m)
{
	int *S = (int *)malloc(sizeof(int)*m);	//Stack to store index of T
	if (!S)
		return 0;

	memset(S, 0, sizeof(int)*m);	//since element in T >= 0

	int max_area = 0;
	int top = -1;

	int count = 0;	//to count how many 0 in start of T
	for (int i = 0; i <= m; i++)
	{
		if (T[i] == 0 && top < 0)	//if element is 0 & stack is empty no need to put it into Stack as it won't be have any role in the area
		{
			count++;
			continue;
		}
			

		if (top < 0)	//Stack is empty and hence we can push the element's index as T[i] > 0
			S[++top] = i;

		else if (T[i] >= T[S[top]])	//push index as current element is greater than stack top element in T
			S[++top] = i;

		else if (T[i] < T[S[top]])	//keep on removing elements from stack until either stack gets empty OR we found a top at which current value is >= S[top]'s value
		{
			int cur_area = 0;
			while (top >= 0 && T[i] < T[S[top]])
			{
				if (top == 0)	//stack is empty
					cur_area = T[S[top]] * (i-count);
				else //stack not empty
					cur_area = T[S[top]] * (i - S[top-1] - 1);

				top--;
				max_area = max_area > cur_area ? max_area : cur_area;
			}
			S[++top] = i;
		}
	}

	if (S)
	{
		free(S);
		S = NULL;
	}

	return max_area;
}

int maxArea(int M[MAX][MAX], int n, int m)
{
	int *T = (int *)malloc(sizeof(int)*(m+1));	//size of T = no. of Columns as Row will be inserted from 0 to n-1, m+1 because we need like this im Histogram
	if (!T)
		return 0;

	memset(T, 0, sizeof(int)*(m+1));

	int max_area = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (M[i][j])
				T[j] += M[i][j];
			else
				T[j] = 0;
		}
		int curr_area = curr_area = HistogramArea(T, m);

		max_area = max_area > curr_area ? max_area : curr_area;
	}

	return max_area;

	//Free memory after printing result
	if (T)
	{
		free(T);
		T = NULL;
	}
}

void Max_RectArea_BinMat()
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
		int n, m;
		fscanf(fp, "%d", &n);
		fscanf(fp, "%d", &m);

		if (n*m < 1)
		{
			printf("%d\n", n*m);
			continue;
		}

		if (n*m == 1)
		{
			int arr;
			fscanf(fp, "%d", &arr);
			printf("%d\n", arr);
			continue;
		}

		int M[MAX][MAX];
		memset(M, 0, sizeof(M));

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				fscanf(fp, "%d", &M[i][j]);

		printf("%d\n", maxArea(M, n, m));

	}

	//close file pointer
	fclose(fp);
}