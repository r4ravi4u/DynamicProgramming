/*
Given a matrix where every element is either ‘O’ or ‘X’, find the largest subsquare surrounded by ‘X’.

T : Test Cases
N : Rows & Columns N X N
X O O X ... Matrix elements row wise

struct cell
{
	int top;
	int left;
}
Table T of Cell elements = 2D array
Rows = Columns = N

Row 0 : only left will be +1 for each X, top will be 1 for all rows
Column 0 = only top will be +1 for each X, left will be 1 for all rows

if M[i] = O
	T[i][j] = 0,0
else
	T[i][j] = 1+top, 1+left

Once matrix made, we need to start from Right Bottom and check for each cell : 
min of top, left of the cell, go min-1 steps top and left : For top check left element and for left check top element
if >= min, store it as max and keep max updating after checking for each cell

*/

#include "Functions.h"

typedef struct Cell
{
	int top;	//will come from top (1st)
	int left;	//will come from left (2nd)
}Cell;

typedef struct Point	//to save i,j index of the element which can contribute to max size while building T : Optimisation
{
	int i;
	int j;
	int min;
}Point;

void MaxSubSquareSidesUtil(char **M, int N)
{
	/*for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%c ", M[i][j]);

		printf("\n");
	}*/
		
	
	Cell **T = (Cell **)malloc(sizeof(Cell *)*N);	//Here N = N-1
	if (!T)
		return;

	for (int i = 0; i < N; i++)
	{
		T[i] = (Cell *)malloc(sizeof(Cell)*N);	//Here N = N-1
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(Cell)*N);
	}
	
	//will be maintained like a stack
	

	//Filling T[0][0] explicitly
	if (M[0][0] == 'X')
		T[0][0].top = T[0][0].left = 1;		



	//Fill First Row 
	for (int j = 1; j < N; j++)
	{
		if (M[0][j] == 'X')
		{
			T[0][j].top = 1;
			T[0][j].left = 1 + T[0][j - 1].left;

		}
	}

	//Filling 1st Column
	for (int i = 1; i < N; i++)
	{
		if (M[i][0] == 'X')
		{
			T[i][0].left = 1;
			T[i][0].top = 1 + T[i-1][0].top;
		}
	}

	Point s[10];	//Because N <= 10
	int top = -1;
	memset(s, 0, sizeof(Point)* 10);

	int max = 1, min = 1;	//atleast size of 1 subsquare matrix is always possible if their is atleast 1 X in the matrix

	//Fill Rest of the table 
	for(int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			if (M[i][j] == 'X')
			{
				T[i][j].top = 1 + T[i - 1][j].top;
				T[i][j].left = 1 + T[i][j-1].left;

				//To store indexes of only those cells which has minimum is > 1
				min = T[i][j].top < T[i][j].left ? T[i][j].top : T[i][j].left;
				if (max < min)
				{
					max = s[++top].min = min;
					s[top].i = i;
					s[top].j = j;
				}
			}
		}
	}

	/*for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d, %d\t", T[i][j].top, T[i][j].left);

		printf("\n");
	}*/

	max = 1;
	while (top >= 0)
	{
		Point index_left, index_top;
		for (int size = s[top].min; size > 1; size--)
		{
			index_left.i = s[top].i;
			index_left.j = s[top].j - size + 1;

			index_top.j = s[top].j;
			index_top.i = s[top].i - size + 1;

			if (T[index_left.i][index_left.j].top >= size && T[index_top.i][index_top.j].left >= size)
				max = max > size ? max : size;
		}
		top--;
	}

	printf("%d\n", max);		

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

void MaxSubSquareSideX()
{

	int T;

	scanf("%d", &T);
	while (T--)
	{
		int N;
		scanf("%d", &N);

		if (N == 1)	//means only 1 element
		{
			char c;
			scanf("%s", &c);
			if (c == 'X')
				printf("%d\n", 1);
			else
				printf("%d\n", 0);

			continue;
		}

		char **M = (char **)malloc(sizeof(char *)*N);
		if (!M)
			return 0;

		for (int i = 0; i < N; i++)
		{
			M[i] = (char *)malloc(sizeof(char)*(N + 1));
			if (!M[i])
				return 0;

			memset(M[i], '\0', sizeof(char)*N);
		}

		int flag = 0, flag1 = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%s", &M[i][j]);
				if (!flag && M[i][j] == 'X')	//in case all elements is O, no X present
					flag = 1;

				if (!flag1 && M[i][j] == 'O')	//in case all elements is X, no O present
					flag1 = 1;
			}

		}

		if (!flag)
			printf("%d\n", 0);

		else if (!flag1)
			printf("%d\n", N);

		else
			MaxSubSquareSidesUtil(M, N);

		if (M)
		{
			for (int i = 0; i < N; i++)
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
	return 0;
	
	/*
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

		if (N == 1)	//means only 1 element
		{
			char c;
			fscanf(fp, "%s", &c);
			if (c == 'X')
				printf("%d\n", 1);
			else
				printf("%d\n", 0);
			continue;
		}

		char **M = (char **)malloc(sizeof(char *)*N);	
		if (!M)
			return;

		for (int i = 0; i < N; i++)
		{
			M[i] = (char *)malloc(sizeof(char)*(N + 1));
			if (!M[i])
				return;

			memset(M[i], 0, sizeof(char)*N);
		}

		int flag = 0, flag1 = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				fscanf(fp, "%s", &M[i][j]);
				if (!flag && M[i][j] == 'X')	//in case all elements is O, no X present
					flag = 1;

				if (!flag1 && M[i][j] == 'O')	//in case all elements is X, no O present
					flag1 = 1;
			}
			
		}

		if (!flag)
			printf("%d\n", 0);

		if (!flag1)
			printf("%d\n", N);

		else
			MaxSubSquareSidesUtil(M, N);

		if (M)
		{
			for (int i = 0; i < N; i++)
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
	fclose(fp);*/
}