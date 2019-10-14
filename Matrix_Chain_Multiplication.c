/*
Matrix Chain Multiplication : 
A: 10 × 30 matrix
B : 30 × 5 matrix
C : 5 × 60 matrix
Then,
(AB)C = (10×30×5) + (10×5×60)
= 1500 + 3000
= 4500 operations
A(BC) = (30×5×60) + (10×30×60)
= 9000 + 18000
= 27000 operations.

T = Test Cases
N = No. of elements into array : Total N-1 Matrices
n1 n2 ... N elements = Order of Matrices : n1 x n2, n2 x n3, n3 x n4 ... so on 
Means we can multiply them serially but need to find which first, and which second and then which third and so on ..

Rows = Columns = N-1

Table T will be formed or order N-1 x N-1, as total matrices are N-1 (not N)
Diagonal elements = 0 (As it means that their is only 1 matrix , hence no multiplication i x i = same)
Filling the table only on North East Direction & in diagonal manner
First : T[0][0], T[1][1], T[2][2] .. So on = 0 All
Second : T[0][1], T[1][2], T[2][3] .. so on : Taking 2 at a time going from left to right AB, BC, CD ...
Third : min((AB)C, A(BC)) .. and so on 2 difference  between row and column
.... & so on


*/

#include "Functions.h"
#define INT_MAX 9999999999

void Matrix_Multiply(matrix *M, int N)	//N-1 copied to N, ex. if 5 elements so 4 matrices will be there
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

	//All elements = 0 , So No need to explicit making diagonal elements = 0

	//We need to fill elements diagonally now in Top - Right side means North East side till T[0][N-1] (T[0][Real N-2])
	/*
	Filling Table Iteration is like : 
	01, 12, 23, 34 ... : 1st : Column - Row = 1	//N-1 Iterations (if N=5, N-1=4 -> Copied to N ; So N-1 in this function = 3) 
	02, 13, 24, ... : 2nd : Column - Row = 2	//N-2 iteration
	03, 14, ... : 3rd : Column - Row = 3
	& so on ..	//till N = 0
	*/

	//make a backup copy of N so as to use it in iterations
	int N_copy = N-1;

	int k = 1;	//means difference between row and column in each iteration

	while (N_copy)	//Total iterations to fill Till right top T[0][N]
	{
		for (int i = 0; i < N_copy; i++)	//Diagonal elements filling up 1 by 1 going towards North East direction
		{
			if (k == 1)
				T[i][i + k] = M[i].m * M[i].n * M[i + k].n;		//Always M[i].n = M[i+1].m
			else
			{
				int min = INT_MAX;
				int curr_value = 0;

				//j will act as partition : A-BCD .. ; AB-CD...
				//when j=1 or j=k : Boundary partitions, then 1 + else 2 +
				for (int j = 1; j <= k; j++)	//As there shall be k possibilities for each cell and we have to take minimum of All, 
				{
					if (j == 1)
					{
						curr_value = T[i+1][k+i] + (M[i].m * M[i].n * M[k+i].n);	//only 1 addition
					}

					else if (j == k)
					{
						curr_value = T[i][k+i-1] + (M[i].m * M[k+i].m * M[k+i].n);	//only 1 addition
					}

					else //for 2 additions in between : 2 values from table and multiplication aspect b/w them	//1 < j < k
					{
						curr_value = T[i][j + i - 1] + T[j+i][k + i] + (M[i].m * M[j + i].m * M[k + i].n);
					}
					
					min = min < curr_value ? min : curr_value;
				}
				T[i][i + k] = min;
			}
			//printf("%d\t", T[i][i + k]);
		}
		//printf("\n");
		k++;
		N_copy--;
	}
		
	printf("%d\n", T[0][N - 1]);
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

void matrix_chain()
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
				
		if (N < 2)	//since 0 & 1 element can't form a matrix
		{
			printf("%d", 0);
			continue;
		}

		matrix *M = (matrix *)malloc(sizeof(matrix)*(N-1));
		if (!M)
			return;

		if (N == 2)
		{
			fscanf(fp, "%d", &M[0].m);
			fscanf(fp, "%d", &M[0].n);
		}
		else
		{
			for (int i = 0; i < N; i++)
			{
				if (i == 0)
				{
					fscanf(fp, "%d", &M[i].m);
				}
				else
				{
					fscanf(fp, "%d", &M[i - 1].n);
					if (i < N-1)
						M[i].m = M[i - 1].n;
				}
			}
		}

		Matrix_Multiply(M, N - 1);	//Total matrices = N-1

		if (M)
			free(M);

	}

	//close file pointer
	fclose(fp);
}