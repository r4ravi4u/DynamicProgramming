/*
Given a string S, find the longest palindromic substring in S.

Substring of string S:

S[ i . . . . j ] where 0 ≤ i ≤ j < len(S)

T : Test Cases
str : len str <= 100

We will use Manacher's Algo O(n) : Works for odd len strings, but can make to work on even strings if we add $ at before and after each char
ex. : ABBA -> $A$B$B$A$

in case original string is itself a palindrome, then prints its len //but if we check it explicitly before calling Algo, it will be like a waste of time in case Fail comes
for odd strings : we need to go for algo (len of T = len of str)
for even strings : Add $ like above and then go for algo (len of T = 2n+1 where n = len of str)

Algo : 
T[0] = 1 ; as single string is palindrome always

Rest Table : 
i = 1 to len-1
for every char at i, we need to check its left and right till they matches and hence T[i] = 2*match + 1 (1 for self, being centre)
once we found a T[i] > 3, it means we need to check for next i position properly (i means centre of the next palindrome substring)
so for next i i.e T[i+1], we need to copy elements from T[i]'s left till we get an element >=3.
Now for this k (i.e. i+k, i-k), we need to check if i+k can be next centre or not :
Centre is only possible for 1 case : 
(i-k)position - T[i-k]/2 <= left bound of current palindrome, then only i+k could be centre, else T[i+k] = 2 * T[i-k] - T[i] (T[i-k] - (T[i] -  T[i-k]))
we will do like this till right side bound of current palindrome, in case right bound of current palindrome is len-1, we break out of the loop

*/

#include "Functions.h"
#define LEN 202	//2*n+1 for even strings

void LongestPalindromeSubstringManacherUtil(char *str, int len)
{
	
	if (1) //(len % 2 == 0)	//even len string, need to add $
	{
		
		len = 2 * len + 1;	//1 extra for Null
		char *str1 = (char *)malloc(sizeof(char)*(len+1));
		if (!str1)
			return;

		memset(str1, 0, sizeof(char)*(len+1));

		str1[0] = '$';
		for (int i = 0; i < (len - 1) / 2; i++)
		{
			str1[2 * i + 1] = str[i];
			str1[2 * i + 2] = '$';
		}

		for (int i = 0; i < len; i++)
			str[i] = str1[i];

		if (str1)
		{
			free(str1);
			str1 = NULL;
		}
	}
	
	int *T = (int *)malloc(sizeof(int)*len);
	if (!T)
		return;
	//no need to do memset, as smallest string len is 1 always even if len = 1
	//memset(T, 0, sizeof(int)*len);

	int max = 1;
	T[0] = 1;
	int index1 = 0;
	
	int k = 1;
	int i = 1;
	
	while (1)
	{
		int flag = 0;
		while (str[i - k] == str[i + k])
		{
			k++;
			flag = 1;
			if (i - k < 0 || i + k >= len)
				break;
		}

		//if (flag)
			k--; //since k++ has been done in above loop and chars not matched
		
		T[i] = 2 * k + 1;

		if (T[i] > max)
		{
			max = T[i];
			index1 = i;
		}
			

		if (i + k + 1 >= len)
			break;

		int left_bound = i - k, right_bound = i + k;
		k = 1;

		

		if (T[i] > 3)
		{
			int j = i;	//back up of i;
			i++;
			int x = 2;
			while (i <= right_bound)
			{
				T[i] = T[2 * j - i];
				int lb = (2 * j - i) - T[i] / 2;
				int rb = i + T[i] / 2;
				if (lb == left_bound && rb == right_bound)
				{
					//next centre found
					k = 1 + T[i] / 2;
					i--;
					break;
				}
				else //no centre found and hence we need to adjust values only at T[i]
				{
					if (T[i] > T[j] && j == i - 1)	//means for first time we checking
						x = 4;

					if (T[i] >= 3)
						T[i] -= x;
				}

				if (T[i] > max)
				{
					max = T[i];
					index1 = i;
				}

				i++;
			}
			
		}

		if ( i <= right_bound)
			i++;

	}
	
	/*for (int i = 0; i < len; i++)
		printf("%d  ", T[i]);*/
	
	int index2 = 0;
	if (!index1 && max==1)	
	{
		if (str[1] == str[3])
			index2 = 1;
	}

	else
	{
		index2 = index1 + (max / 2);
		index1 -= (max / 2);
	}
			
	//we need to print longest palindrome string
	for (int i = index1; i <= index2; i++)
	{
		if (str[i] != '$')
			printf("%c", str[i]);
	}
	printf("\n");
	
	if (T)
	{
		free(T);
		T = NULL;
	}
}

void LongestPalindromeSubstringManacher()
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
			printf("%c\n", str[0]);

		else if (len == 2)
		{
			if (str[0] == str[1])
				printf("%s\n", str);
			else
				printf("%c\n", str[0]);
		}

		else
			LongestPalindromeSubstringManacherUtil(str, len);

		if (str)
			free(str);
	}

	//close file pointer
	fclose(fp);
}