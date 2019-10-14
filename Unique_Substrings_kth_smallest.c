/*
You are given n strings w1, w2, ......, wn. Let Si denote the set of strings formed by considering all unique substrings of the string wi. A substring is defined as a contiguous sequence of one or 
more characters in the string. More information on substrings can be found here. Let S = {S1 U S2 U .... Sn} .i.e. S is a set of strings formed by considering all the unique strings in all sets
S1, S2,..... Sn. You will be given many queries, and for each query, you will be given an integer 'k'. Your task is to display the lexicographically kth smallest string from the set S.
*/

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "Functions.h"

/*#define N 10
#define M 50
#define Q 5*/

int partition_str(char **str, int start, int end);
void qsort_str(char **str, int start, int end);
char** lcp(char **str, int len);
char** unique_substrings(char *a, int len, char **str);
int isSame(char *a, char *b);
void findStringsUtil(char a[51][2001], int numstring, int a_query[], int numquery);


int max_total_len = 0;

int partition_str(char **str, int start, int end)
{
	char *pivot = str[end];
	int index = start;

	char *temp;

	for (int i = start; i < end; i++)
	{
		int j = -1,k=-1;

		while ((str[i][++j] && pivot[++k]) && str[i][j] == pivot[k]);	//traversing both strings for comparison

		//Case 1 : str[i][j] = pivot[k] = Null ; Both Strings equal and hence reached end of the string : Needed
			
		//Case 2 : pivot[k] = Null ; str is larger : Not Needed

		//Case 3 : str[i][j] = Null ; str is smaller : Needed

		//Case 4 : str[i][j] != Null ; if str-pivot < 0, str is smaller else str is larger : Need for str - pivot < 0

		if (!pivot[k] && str[i][j])	//Case 2
			continue;

		if ((!str[i][j] && !pivot[k]) || (!str[i][j]) || (str[i][j] - pivot[k] < 0))	//Case1, 3 & 4(a)
		{	
			//swap i, index elements
			temp = str[index];
			str[index] = str[i];
			str[i] = temp;

			index++;
		}
		
	}
	//swap index, pivot end
	temp = str[index];
	str[index] = str[end];
	str[end] = temp;

	return index;
}

void qsort_str(char **str, int start, int end)
{
	int index = -1; //parition index
	if (start < end)
	{
		index = partition_str(str, start, end);
		qsort_str(str, start, index - 1);
		qsort_str(str, index + 1, end);
	}
}

char** lcp(char **str, int len)	//LCP array = Lowest Common Prefix
{
	int *arr = (int *)malloc(sizeof(int)*len);
	if (!arr)
		return;

	arr[0] = 0;	//since first string we can't compare with any previous one
	int total = (len*(len + 1) / 2); //total no. of distinct substrings = n(n+1)/2 - LCP Array Sum : But here we dont need count, we need substring array in sorted manner
	for (int i = 0; i < len-1; i++)	//till len-1 because we will be comparing current string with next one
	{
		int j = 0;
		while (str[i][j] == str[i + 1][j])
		{
			j++;
			if (!str[i][j] || !str[i + 1][j])
				break;
		}
		arr[i + 1] = j;
		total -= j; //total no. of distinct substrings = n(n+1)/2 - LCP Array Sum : But here we dont need count, we need substring array in sorted manner
	}

	//now generate unique substrings with the help of this new LCP array and to store all (total) substrings we need to create a new char array
	char** substr = (char **)malloc(sizeof(char *)*(total+1));
	if (!substr)
		return;
	for (int i = 0; i < total+1; i++)
	{
		substr[i] = (char *)malloc(sizeof(char)*(len+1));
		if (!substr[i])
			return;

		memset(substr[i], '\0', sizeof(substr[i]));
	}

	substr[total] = NULL;
		

	int index = 0;	//for maintaining substr index
	for (int i = 0; i < len; i++)	//len = total no. of elements into arr[] & str[], vertical scan into str array for string pickup
	{
		for (int j = 0; j < strlen(str[i]) - arr[i] - 1; j++)	//means there are more smaller substrings contained in the actual string str[i], horizontal scan of the string to pick up substrings
		{
			//first copy chars from str to substr till arr[i] and then copy extra chars (if applicable)
			int k = 0;
			while (k < arr[i]+j+1)	//to copy substrings from str to substr
			{
				substr[index][k] = str[i][k];
				k++;
			}
			substr[index][k] = '\0';	
			index++;
		}
		int l = 0;
		while ((str[i][l]) && (substr[index][l] = str[i][l++]));	//for str[i] to get copies into substr[index] as last string of that particular suffix string is also a part of substr
		substr[index][l] = '\0';
		index++;

		if (str[i])	//option 2 taken from below options
		{
			free(str[i]);
			str[i] = NULL;
		}
	}

	//till here we made substr which contains all unique substrings of original str

	/*
	So now we have following options :
	1. Free str memory -> allocate str memory same as same as substr memory -> copy substr to str and free substr
	2. Free str memory as all work done for str -> return substr[] for each string to calling function (explicitly or implicitly) -> and then in calling function we need to merge all substr for final result
	*/

//	printf("Total distinct substrings : %d", total);

	if (arr)
	{
		free(arr);
		arr = NULL;
	}

	max_total_len += total;

	return substr;
}

char** unique_substrings(char *a, int len, char **str)
{
	int j;

	for (int i = 0; i < len; i++)	//generating suffix array
	{
		str[i] = (char *)malloc(sizeof(char)*(len+1));	//1 extra for null char
		if (!str[i])
			return;

		memset(str[i], '\0', sizeof(char)*(len+1));

		for (j = 0; j+i < len; j++)
			str[i][j] = a[j + i];

//		str[i][j] = '\0';
	}

	//str contains suffix strings, now we need to sort this array to get LCP array in next step

	qsort_str(str, 0, len - 1);

	char **substr = lcp(str, len);	//gen LCP array for sorted suffix array, so as to get unique/distinct substring array in next step

	return substr;
}

int isSame(char *a, char *b)
{
	int i = 0;
	if (a && !b)
		return 0;
	if (b && !a)
		return 0;

	while (a[i] || b[i])
	{
		if (a[i] != b[i])
			return 0;

		i++;
	}
	return 1;
}

void findStringsUtil(char a[51][2001], int numstring, int a_query[], int numquery)
{
	int *len = (int *)malloc(sizeof(int)*numstring);	//to store lengths of N strings
	if (!len)
		return;

	char ***str = (char ***)malloc(sizeof(char **)*numstring);	//to store unique substrings of a[i] in sorted order
	if (!str)
		return;



	char ***substr = (char ***)malloc(sizeof(char **)*numstring);
	int max_len = 0;
	for (int i = 0; i < numstring; i++)
	{
		len[i] = strlen(a[i]);

		max_len = max_len > len[i] ? max_len : len[i];

		str[i] = (char **)malloc(sizeof(char*)*len[i]);
		if (!str[i])
			return;
		

		substr[i] = unique_substrings(a[i], len[i], str[i]);

		int j = 0;

/*		while(substr[i][j])
		{
			printf("\n%s\n", substr[i][j++]);
		}
	*/

	}

	//So we got all distinct substrings in substr array substr[0], substr[1] .. contains unique substrings of main string 
	//Now we need to merge these substr's into 1 single array (sorted & removing duplicates) so that we can access the lexicographically kth smallest string in O(1) time then

	//We will create a 2D char array of length max_total_len (Total substrings incl. duplicates) to merge substr arrays and we will free substr arrays afterwards

	//Merging is only needed when we have numstring > 1
	
	char** final_substr = (char **)malloc(sizeof(char *)*(max_total_len + 1));	//In case we have duplicates, then extra space is wasted but however we can make it free explicitly if needed
	if (!final_substr)
		return;
	for (int i = 0; i < max_total_len + 1; i++)
	{
		final_substr[i] = (char *)malloc(sizeof(char)*(max_len + 1));
		if (!final_substr[i])
			return;

		memset(final_substr[i], '\0', sizeof(final_substr[i]));
	}

	final_substr[max_total_len] = NULL;

	//Copy all arrays into 1 and then qsort call

	int index = 0;
	for (int i = 0; i < numstring; i++)	//numstring = total no. of arrays into substr for each original string
	{
		int j = 0;
		while (substr[i][j])
		{
			int k = 0;
			while (substr[i][j][k])
			{
				final_substr[index][k] = substr[i][j][k++];
			}

			if (substr[i][j])	//substr array getting free after work done
			{
				free(substr[i][j]);
				substr[i][j] = NULL;
			}
			
			final_substr[index][k] = '\0';
			j++;
			index++;
		}
	}

	//Sort the array but it contains duplicates, which shall be removed later on
	qsort_str(final_substr, 0, max_total_len-1);

	/*for (int i = 0; i < max_total_len; i++)	//range = max - Total duplicates
	{
		printf("%s\n", final_substr[i]);
	}*/

	//Now once sorted, remove duplicates by scanning array from left to right as duplicate elements will be adjacent by now
	int count = 0;	//to know how many duplicates we have in the array
	for (int i = 0; i < max_total_len-1-count; i++)
	{
		if (isSame(final_substr[i], final_substr[i + 1]))
		{
			//we need to shift elements left 1 block
			int j;
			for (j = i + 1; j < max_total_len - 1- count; j++)
			{
				int k = 0;
				while ((final_substr[j + 1][k]) && (final_substr[j][k] = final_substr[j + 1][k++]));
				final_substr[j][k] = '\0';
			}
			count++;
			free(final_substr[j]);
			final_substr[j] = NULL;
				
		}
	}

	
	/*for (int i = 0; i < max_total_len-count; i++)	//range = max - Total duplicates
	{
		printf("%s\n", final_substr[i]);
	}*/
	

	//now extrack k from a_query and print line by line answers

	for (int i = 0; i < numquery; i++)
	{
		if (a_query[i] > max_total_len - count)
			printf("INVALID\n");
		else
			printf("%s\n", final_substr[a_query[i] - 1]);
	}

	if (str)
	{
		for (int i = 0; i < numstring;i++)
		{
			if (str[i])
			{
				free(str[i]);
				str[i] = NULL;
			}
				
		}
		free (str);
		str = NULL;
	}

	if (substr)
	{
		for (int i = 0; i < numstring; i++)
		{
			if (substr[i])
			{
				free(substr[i]);
				substr[i] = NULL;
			}

		}
		free(substr);
		substr = NULL;
	}

	if (final_substr)
	{
		for (int i = 0; i < max_total_len; i++)
		{
			if (final_substr[i])
			{
				free(final_substr[i]);
				final_substr[i] = NULL;
			}

		}
		free(final_substr);
		final_substr = NULL;
	}

	if (len)
		free(len);

//	printf("hi");	//Till here we are able to print suffix array in sorted array
		
}

void findStrings(char a[51][2001], int numstring, int a_query[], int numquery)
{
	if (numstring > 0)
		findStringsUtil(a, numstring, a_query, numquery);

	else
		return;
}

void unique_substring_kth_smallest()
{
	int res;

	//dummy check
	/*char **str = (char **)malloc(sizeof(char *)*4);
	for (int i = 0; i < 4; i++)
	{
		str[i] = (char *)malloc(sizeof(char)* 5);
		memset(str[i], '\0', sizeof(str[i]));
	}
	
	str[0] = "abc";
	str[1] = "$";
	str[2] = "def";
	str[3] = "#";

	qsort_str((char *)str, 0, 3);*/

	int _cases, _query, _a_i;
	_cases = 4;

	char _a[51][2001] = {"ababa", "aac", "adbc", "babab" };

	_query = 6;

	int _a_query[501];
	_a_query[0] = 3;
	_a_query[1] = 4;
	_a_query[2] = 15;
	_a_query[3] = 22;
	_a_query[4] = 18;
	_a_query[5] = 150;


	findStrings(_a, _cases, _a_query, _query);

	return 0;
}