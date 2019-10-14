/*
Given a string, a partitioning of the string is a palindrome partitioning if every sub-string of the partition is a palindrome. For example, “aba|b|bbabb|a|b|aba” is a palindrome partitioning of “ababbbabbababa”. Determine the fewest cuts needed for palindrome partitioning of a given string. For example, minimum 3 cuts are needed for “ababbbabbababa”. The three cuts are “a|babbbab|b|ababa”.

T : Test Cases
str : String to be checked : Len of string <= 1000

N = strlen(S)

if str is itself a palindrome, return 0 i.e. No Splits needed

else

Form a 2D table T : To be filled diagonally
Rows = N
Columns = N

Diagonal elements T[i][i] = 0, means if only 1 char so it would be a palindrome always, no splits required

so if len = 1, T[i][i] = 0;

len = 2, 3 .. N : we need to build table to be filled diagonally in Top Right direction

if str from i to j is palindrome already
T[i][j] = 0

else
we need to check for len-1 splits and take minimum
T[i][j] = 1 + min(T[i][m-1], T[m][j]); m is the splits for that particular string i to j

T[N-1][N-1] = Result

*/