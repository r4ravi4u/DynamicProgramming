/*
Assigning a Meeting Room
In our company, there is a popular meeting room. Many meetings are reserved to use this room with starting time and finishing time, and the place can’t hold two meetings at the same time if the time is
overlapped. Thus only one of the same time-framed meetings can be held in here and the others should give up. However, it is not overlapped for the same starting time of a meeting and the finishing
time of another meeting.

When the number of meetings, starting time and finishing time of each meetings are given, you want to hold as many meetings as possible.
In a given number of meetings and each given starting/finishing time, you want to hold as many meetings as possible. Create a program that can assign meetings to the meeting room as many as it can.
*/

#include "Functions.h"
#define N 15	//no. of meetings

typedef struct interval
{
	int t1;	//start time
	int t2;	//end time
}interval;

void qsort(interval M[], int start, int end);
int partition(interval M[], int start, int end);

void meeting_interval()
{
	interval M[N] = { 
		{ 4, 8 },
		{ 2, 5 },
		{ 2, 6 },
		{ 4, 6 },
		{ 2, 3 },
		{ 1, 6 },
		{ 4, 7 },
		{ 3, 5 },
		{ 3, 8 },
		{ 1, 2 },
		{ 1, 7 },
		{ 2, 4 },
		{ 5, 6 },
		{ 4, 5 },
		{ 7, 8 },
						};	//Mettings interval storage

	//Sort the array items as per t2 in increasing (non decreasing) order

	//QuickSort Algo

	printf("Before Sort : \n");

	for (int i = 0; i < N; i++)
		printf("%d\t%d\t%d\n", i, M[i].t1, M[i].t2);

	qsort(M, 0, N-1);	//quick sort call

	printf("After Sort : \n");

	for (int i = 0; i < N; i++)
		printf("%d\t%d\t%d\n", i, M[i].t1, M[i].t2);

	//will use DP (Dynamic Programming linearly

	//i will go from 0 to N-1 and j will go from 0 to i
	//t2 of j should be less than or equal to t1 of i -> means not overlap

	//each interval weight is 1, as all meetings have value 1, all meetings are on same priority. Just we need to maximise no.

	int A[N];
	for (int i = 0; i < N; i++)	//memset to 1
		A[i] = 1;

	int max = 1;	//max value in the array A = No. of meetings that can be done without overlapping
	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (M[i].t1 >= M[j].t2)	//overlap condition check
			{
				if (A[i] < A[j] + 1)	//if already present value is greater than last meeting + 1, then only update value of A[i] else not
				{
					A[i] = A[j] + 1;
					max = max > A[i] ? max : A[i];
				}
			}
		}
	}

	printf("\n\n No. of Meetings possible : %d", max);
}

void qsort(interval M[], int start, int end)
{
	int index = -1; //parition index
	if (start < end)
	{
		index = partition(M, start, end);
		qsort(M, start, index - 1);
		qsort(M, index + 1, end);
	}
}
int partition(interval M[], int start, int end)
{
	interval pivot = M[end];
	int index = start;
	interval temp;
	for (int i = start; i < end; i++)
	{
		if (M[i].t2 <= pivot.t2)
		{
			//swap i, index elements
			temp = M[index];
			M[index] = M[i];
			M[i] = temp;

			index++;
		}
	}
	//swap index, pivot end
	temp = M[index];
	M[index] = M[end];
	M[end] = temp;

	return index;
}