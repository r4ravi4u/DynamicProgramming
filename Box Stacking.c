/*
You are given a set of N types of rectangular 3-D boxes, where the ith box has height h, width w and length l. You task is to create a stack of boxes which is as tall as possible, but you can only stack a box on top of another box if the dimensions of the 2-D base of the lower box are each strictly larger than those of the 2-D base of the higher box. Of course, you can rotate a box so that any side functions as its base.It is also allowable to use multiple instances of the same type of box. You task is to complete the function maxHeight which returns the height of the highest possible stack so formed.

T  : Test Cases
N : No. of Boxes
h1 w1 l1 h2 w2 l2 ... hn wn ln : Height Width Length of N Boxes 3*N elements

1. Possible Combinations of L,W,H after rotation of each box such that L >= W for each box
Ex. 3 2 1 -> L W H
So its like possible rotations we will consider : L >= W
3 2 1
3 1 2
2 1 3

So for all boxes we  need to find out above possible combinations for rotation purpose

2. Sort them in Decreasing order on basis of Base Area i.e. L X W
a) If Base Area of B1 is greater than B2, then B1 can not go on top of B2
b) If Base Area B1 < Base Area B2 : May be possible (need to check later on), that B1 can go on top of B2 or not by comparing L & W (both shall be greater)

3) Sorted Boxes is a list now from index 0 to N-1 (Total N type of boxes with unlimited supply of each box)

4) Make 2 1D array of length N : Max (max Height) & Result (Final Result)
A) Max array : each element initialised with height of sorted boxes as if their is only 1 box
B) Result array : 0 to N-1 fill

5) i = 0 to N-1
j = 0 to i

Can i go on top of j : means L & W of i shall be less than L & W of j, then only it can go (even if equal, then not possible)
if Yes,
	max[i] = max(max[i], max[j] + height[i]);	//LIS : Longest Increasing Subsequence
	result[i] = j; //means i is at top of j

max heigth = maximum element in max array (not last element always)

*/

#include "Functions.h"
#define H 1000
#define W 1000
#define L 10001

typedef struct Box	//to store rotations of box and hence will sort the boxes bases on base area
{
	int l;
	int w;
	int h;
	int base_area;	//based on this we need to sort boxes
}Box;

void qsort_box(Box *b, int start, int end)
{
	int index = -1; //parition index
	if (start < end)
	{
		index = partition_box(b, start, end);
		qsort_box(b, start, index - 1);
		qsort_box(b, index + 1, end);
	}
}
int partition_box(Box *b, int start, int end)
{
	Box pivot = b[end];
	int index = start;
	Box temp;
	for (int i = start; i < end; i++)
	{
		if (b[i].base_area >= pivot.base_area)
		{
			//swap i, index elements
			temp = b[index];
			b[index] = b[i];
			b[i] = temp;

			index++;
		}
	}
	//swap index, pivot end
	temp = b[index];
	b[index] = b[end];
	b[end] = temp;

	return index;
}

int maxHeight(int height[], int width[], int length[], int n)
{
	if (n == 1 && height[0] == width[0] && width[0] == length[0])
		return height[0];	//Only 1 box can be put

	struct Box *b = (Box *)malloc(sizeof(Box)*n*3);	//At max 3n rotations possible each type box where L >= W
	if (!b)
		return 0;

	memset(b, 0, sizeof(Box)*n * 3);

	int j = 0;
	for (int i = 0; i < n; i++)
	{
		b[j].l = length[i];
		b[j].w = width[i];
		b[j].h = height[i];
		b[j].base_area = b[j].l * b[j].w;

		//Now will check for rotations and store it on j index. Need to check for already stored box as well

		int count = 0;

		if (b[j].l == b[j].w && b[j].w == b[j].h)	//l w h same so no need to rotate
			j++;

		else if (b[j].l != b[j].w && b[j].w != b[j].h && b[j].h != b[j].l)	//all 3 different, so 3 rotations
		{
			int max, mid, min;

			if (b[j].l > b[j].w && b[j].l > b[j].h)
			{
				max = b[j].l;
				if (b[j].w > b[j].h)
				{
					mid = b[j].w;
					min = b[j].h;
				}
				else
				{
					mid = b[j].h;
					min = b[j].w;
				}
			}
			else if (b[j].w > b[j].h && b[j].w > b[j].l)
			{
				max = b[j].w;
				if (b[j].l > b[j].h)
				{
					mid = b[j].l;
					min = b[j].h;
				}
				else
				{
					mid = b[j].h;
					min = b[j].l;
				}
			}
			else
			{
				max = b[j].h;
				if (b[j].l > b[j].w)
				{
					mid = b[j].l;
					min = b[j].w;
				}
				else
				{
					mid = b[j].w;
					min = b[j].l;
				}
			}

			b[j].l = max;
			b[j].w = mid;
			b[j].h = min;
			b[j].base_area = b[j].l * b[j].w;

			j++;

			b[j].l = max;
			b[j].w = min;
			b[j].h = mid;
			b[j].base_area = b[j].l * b[j].w;

			j++;

			b[j].l = mid;
			b[j].w = min;
			b[j].h = max;
			b[j].base_area = b[j].l * b[j].w;

			j++;
		}

		else //2 of the dimension same, so 2 roations possible
		{	
			int max, min, max_flag = 0;	//if flag = 1 means max is 2 times else min is 2 times out of 3
			if (b[j].l == b[j].w)
			{
				if (b[j].l > b[j].h)
				{
					max = b[j].l;
					min = b[j].h;
					max_flag = 1;
				}
				else
				{
					max = b[j].h;
					min = b[j].l;
				}
			}
			if (b[j].w == b[j].h)
			{
				if (b[j].w > b[j].l)
				{
					max = b[j].w;
					min = b[j].l;
					max_flag = 1;
				}
				else
				{
					max = b[j].l;
					min = b[j].w;
				}
			}
			if (b[j].l == b[j].h)
			{
				if (b[j].l > b[j].w)
				{
					max = b[j].l;
					min = b[j].w;
					max_flag = 1;
				}
				else
				{
					max = b[j].w;
					min = b[j].l;
				}
			}
			
			if (max_flag)
			{
				b[j].l = max;
				b[j].w = max;
				b[j].h = min;
				b[j].base_area = b[j].l * b[j].w;

				j++;

				b[j].l = max;
				b[j].w = min;
				b[j].h = max;
				b[j].base_area = b[j].l * b[j].w;

				j++;
			}

			else
			{
				b[j].l = max;
				b[j].w = min;
				b[j].h = min;
				b[j].base_area = b[j].l * b[j].w;

				j++;

				b[j].l = min;
				b[j].w = min;
				b[j].h = max;
				b[j].base_area = b[j].l * b[j].w;

				j++;
			}
					
		}
	}

	//Box b contains all boxes with required rotations where l >= w
	//Sort the Box b array now
	qsort_box(b, 0, j - 1);

	/*for (int i = 0; i < j; i++)
		printf("%d\t%d\t%d\n", b[i].l, b[i].w, b[i].h);*/

	int *arr = (int *)malloc(sizeof(int)*j);
	if (!arr)
		return 0;

	for (int i = 0; i < j; i++)
		arr[i] = b[i].h;

	int max_height = -1;
	for (int i = 1; i < j; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (b[i].l < b[j].l && b[i].w < b[j].w)
				arr[i] = arr[i] > arr[j] + b[i].h ? arr[i] : arr[j] + b[i].h;

			max_height = max_height > arr[i] ? max_height : arr[i];
		}
		//printf("%d\t", arr[i]);
	}

	return max_height ;
	
	//free mem after usage
	if (b)
		free(b);

	if (arr)
		free(arr);



}

void Box_Stacking_Max_Height()
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

		int A[H], B[W], C[L];
		for (int i = 0; i < N; i++)
		{
			fscanf(fp, "%d", &A[i]);	//Height
			fscanf(fp, "%d", &B[i]);	//Width
			fscanf(fp, "%d", &C[i]);	//Length

		}
		
		printf("%d\n", maxHeight(A, B, C, N));

	}

	//close file pointer
	fclose(fp);
}