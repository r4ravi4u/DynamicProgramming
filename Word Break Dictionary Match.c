/*
Given an input string and a dictionary of words, find out if the input string can be segmented into a space-separated sequence of dictionary words. See following examples for more details.

Consider the following dictionary
{ i, like, sam, sung, samsung, mobile, ice,
cream, icecream, man, go, mango}

Input:  ilike
Output: Yes
The string can be segmented as "i like".

Input:  ilikesamsung
Output: Yes
The string can be segmented as "i like samsung" or "i like sam sung".

T : Test Cases
N : number of words in dictionary. 1<=N<=12
Dictionary Words Total N words : Length of each word is less than 15
String S to be checked : S<1000

Table T : 
Fill Diagonally elements T[i][i] = 1 iff single char is present in dictionary

Rows = len of S
Columns = len of S

for rest table : 
if(string from i to j is a match in dictionary)
	T[i][j] = 1
else
	find a point k in between so that left side and right side each is a word in dictionary then 1, else 0
	//suppose i to j string has 3 letters, so we need to check for 2 paritions abc = a bc & ab c .. like this

Enhancement : 
We can sort the dictionary words to apply binary search when we try to match a string i to j in the Dictionary for fast working
However N <= 12. So there will be at max 12 dictionary words. If we dont sort, we need to scan only 12 words (of varying lengths). Can be done withour sorting
But still we shall sort the Dictionary, so that we can have a practice over that and better searching

*/

#include "Functions.h"
#define LEN 15 //Length of each word is < 15, as mentioned in ques
#define LENSTR 1000	//Length of string S (which need to be checked) < 1000

int partition_Str(char **str, int start, int end)
{
	char *pivot = str[end];
	int index = start;

	char *temp = NULL;

	for (int i = start; i < end; i++)
	{
		int j = -1, k = -1;

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

	temp = NULL;

	return index;
}

void qsort_Str(char **str, int start, int end)
{
	int index = -1; //parition index
	if (start < end)
	{
		index = partition_Str(str, start, end);
		qsort_Str(str, start, index - 1);
		qsort_Str(str, index + 1, end);
	}
}

int IsPresentInDict(char **Dict, char *s, int *len, int lens, int start, int end) //Binary search ; lens is length of string s to be checked in Dict
{
	int mid = -1;
	
	if (start <= end)
	{
		mid = (start + end) / 2;
		
		int i = -1;
		while (s[++i] && Dict[mid][i] && s[i] == Dict[mid][i]);
		
		if (i == len[mid] && i == lens && s[i-1] == Dict[mid][i-1])	//Base condition if string matches
			return 1;

		if ((!Dict[mid][i] && s[i]) || (s[i] && Dict[mid][i] && (s[i] - Dict[mid][i] > 0)))//Null char reached in Dict but char present in s at same index, means s is larger than mid
			return IsPresentInDict(Dict, s, len, lens, mid+1, end);

		else if ((!s[i] && Dict[mid][i]) || (s[i] && Dict[mid][i] && (s[i] - Dict[mid][i] < 0)))	//means s is smaller 
			return IsPresentInDict(Dict, s, len, lens, 0, mid-1);
	}
	
	return 0;

}

void WordBreakUtil(char **Dict, int  N, int *len, char *Str, int lenS)	//Here Dictionary we got is in Sorted Form
{
	//This time we form a table which has lenS elments in 0th row & then -1 at each below level so as to save space. Lets Try !!
	int **T = (int **)malloc(sizeof(int *)*lenS);	
	if (!T)
		return;

	/*Below Table is like this : 
	0 0 0 0 0 0
	0 0 0 0 0
	0 0 0 0
	0 0 0
	0 0
	0

	First Column represents T[i][i] = Diagonal elements if whole matrix is made
	*/
	for (int i = 0; i < lenS; i++)
	{
		T[i] = (int *)malloc(sizeof(int)*(lenS - i));	//Total Columns = 1 less at each below level
		if (!T[i])
			return;

		memset(T[i], 0, sizeof(int)*(lenS - i));

	}

	int max = 0;
	int min = LEN;	//as max length of word in Dict is < 15
	for (int i = 0; i < N; i++)	//to check most max & min length in that array len, so that we can get a straight away idea without checking whole array that whether our inside strings matches in dict or not
	{
		max = max > len[i] ? max : len[i];
		min = min < len[i] ? min : len[i];
	}

	//make copy of lenS as each time it will gets less 1
	int count = lenS;
	int j = 1; //length of substring to be matched in Dict
	int k;	//no. of partitions. k is always j-1 i.e. length-1
	
	while (count--)	//for doing Column wise iteration as we have only half diagonal matrix
	{
		k = j - 1;
		for (int i = 0; i <= count; i++)	//going down in column i.e row changes
		{
			char *s = (char *)malloc(sizeof(char)*(j + 1));	//1 extra for NULL
			if (!s)
				return;

			memset(s, 0, sizeof(char)*(j + 1));

			for (int x = 0; x < j; x++)	//Copying string to be matched in dictionary
				s[x] = Str[i+x];

			if (j > max || j < min)	//length of string s to be checked in Str against Dict is j vs max, min (j = length of s)
				T[i][j - 1] = 0;

			else if (IsPresentInDict(Dict, s, len, j, 0, N-1))	//Binary Search in Dict for s : start =0; end = N-1, only executed if above condition gets False j against max, min
				T[i][j - 1] = 1;

			if (s)	
				free(s);	//As we its work is over for this iteration

			if (!T[i][j - 1] && k > 0)
			{
				for (int l = 0; l <= k; l++)
				{
					T[i][j - 1] = T[i][l] && T[i + l + 1][k - l - 1];
					if (T[i][j - 1])
						break;	//as we found True for this breakup partition, hence no need to check further
				}
			}
			//printf("%d\t", T[i][j - 1]);
		}
		j++;	//length++ as column changes
		//printf("\n");
	}

	printf("%d\n", T[0][lenS - 1]);

	//Free mem after usage
	if (T)
	{
		for (int i = 0; i < lenS; i++)
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

void Word_Break()
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

		char **Dict = (char **)malloc(sizeof(char *)*N);
		if (!Dict)
			return;

		for (int i = 0; i < N; i++)
		{
			Dict[i] = (char *)malloc(sizeof(char)*LEN);	//Length of each word is < 15, as mentioned in ques, Last char for storing NULL
			if (!Dict[i])
				return;

			memset(Dict[i], '\0', sizeof(char)*LEN);
		}

		int *len = (int *)malloc(sizeof(int)*N);	//to store lengths of N dictionary words at parallel index
		if (!len)
			return;

		for (int i = 0; i < N; i++)
		{
			fscanf(fp, "%s", Dict[i]);
			//len[i] = strlen(Dict[i]);
			//printf("%s : %d\n", Dict[i], len[i]);
		}
		
		// We shall calculate len[i] after Dictionary Sorting
		qsort_Str(Dict, 0, N-1);

		for (int i = 0; i < N; i++)
		{
			len[i] = strlen(Dict[i]);
			//printf("%s : %d\n", Dict[i], len[i]);
		}

		char Str[LENSTR] = "\0";

		fscanf(fp, "%s", Str);
		int lenS = strlen(Str);

		//To check if Str itself is a dictionary word, so that to avoid going into the function directly
		if (IsPresentInDict(Dict, Str, len, lenS, 0, N - 1))
			printf("%d\n", 1);	// no need to call function and go to next TC

		//printf("\n%s : %d\n", Str, lenS);
		else
			WordBreakUtil(Dict, N, len, Str, lenS);

		//Free memory after printing result
		if (Dict)
		{
			for (int i = 0; i < N; i++)
			{
				if (Dict[i])
				{
					free(Dict[i]);
					Dict[i] = NULL;
				}

			}
			free(Dict);
			Dict = NULL;
		}

		if (len)
			free(len);

	}

	//close file pointer
	fclose(fp);
}