/*
Given three strings A, B and C your task is to complete the function isInterleave which returns true if C is an interleaving of A and B else returns false. C is said to be interleaving A and B, if it contains all characters of A and B and order of all characters in individual strings is preserved.

T : Test Cases
strA strB strC : 3 strings of length <= 100

2D table : 
Rows = len of strB + 1 -> i
Columns = len of strA + 1 -> j

We will be checking row chars and column chars with strC chars

T[0][0] = 1;

Row0 :
if j-1th char of strA == j-1th char of strC && T[0][j-1] == 1 (Left)
T[0][j] = 1

Column0 : 
if i-1th char of strB == i-1th char of strC && T[i-1][0] == 1 (Top)
T[i][0] = 1

i = 1 to len(strB)
j = 1 to len(strA)

//if column char matches with strC && left is 1 || row char matches with strC && top is 1
if( (strA[j-1] == strC[j] && T[i][j-1] == 1) || (strB[i-1] == strC[j] && T[i-1][j] == 1)
T[i][j] = 1;

T[len strB][len strA] = Result	//1 means Yes strC is interleaved string of A n B
*/