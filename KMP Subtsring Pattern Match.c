/*
Given a string of character, find the length of longest proper prefix which is also a proper suffix.
Example:
S = abab
lps is 2 because, ab.. is prefix and ..ab is also a suffix.

In above problem, only half problem is given, later part is to match whether a pattern is present in string or not

T : Test Cases <= 100
str : String to be checked for LPS (Longest Prefix Suffix) len of str < 100000

Expected time compexity is O(N)

1D array T of same len str : 
T[0] = 0 : single char

Rest Table we need to fill like this : 
int j=0;
for(i=1;i<len;i++)
	if(char at i == char at j)	//Step 1
		arr[i] = 1 + j;
		j++;
	else
		if(j == 0)
			arr[i] = 1 i.e. 1 + j
		j = arr[j-1] //just last char that has been matched	//Step 2
		if now char at j == char at i
			we need to do Step 1

		Need to step2 until a char is matched or j becomes 0


		Max of this array = Result

Once this array has been built, we will use this info for pattern searching in main string effectively for next index to search ON
*/

#include "Functions.h"
#define LEN 100000

void KmpLpsUtil(char *str, int len)
{
	int *T = (int *)malloc(sizeof(int)*len);
	if (!T)
		return;
	memset(T, 0, sizeof(int)*len);
	
	int j = 0, max = 0;
	for (int i = 1; i < len; i++)
	{
		if (str[i] == str[j])
		{
			T[i] = j + 1;
			j++;
		}
		else //means char not matches, in this case we need to find a j where char matches, if matches stop there, else lets j reach to 0 and then stop
		{
			while (1)	
			{
				if (!j)
				{
					//means even char at j = 0 do not matches chat at i hence T[i] shall remain 0 .. as we memset it to 0
					break;
				}

				j = T[j - 1];
				
				if (str[i] == str[j])
				{
					T[i] = j + 1;
					j++;
					break;
				}
				
			}
		}
		//printf("%d  ", T[i]);
		max = max > T[i] ? max : T[i];
		
	}

	printf("%d\n", T[len-1]);	//we are not printing max, as ques needs that they want to compare from 0 till last and hence last index value
	
	if (T)
	{
		free(T);
		T = NULL;
	}
}

void KMP_Substring_LPS()
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
		char *str = (char *)malloc(sizeof(char)*LEN);	//1 extra for last NULL char
		if (!str)
			return;

		memset(str, 0, sizeof(char)*LEN);

		fscanf(fp, "%s", str);

		int len = strlen(str);

		if (len < 2)
		{
			printf("%d\n", len-1);
			continue;
		}

		if (len == 2)
		{
			if (str[0] == str[1])
				printf("%d\n", len-1);
			else
				printf("%d\n", len - 2);

			continue;
		}
		
		KmpLpsUtil(str, len);

		if (str)
			free(str);
	}

	//close file pointer
	fclose(fp);
}