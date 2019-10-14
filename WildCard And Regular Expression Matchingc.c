/*
WildCard Matching: 
The wildcard pattern can include the characters ‘?’ and ‘*’
‘?’ – matches any single character
‘*’ – Matches any sequence of characters (including the empty sequence)

Text = "baaabab",
Pattern = “*****ba*****ab", output : true
Pattern = "baaa?ab", output : true
Pattern = "ba*a?", output : true
Pattern = "a*ab", output : false

Rows : len1 + 1 : String Text of length len1
Columns = len2 + 1 : Pattern of length len2

First Row & Column = 0
T[0][0] = 1

if(char i == char j || char j == ?)
	T[i][j] = T[i-1][j-1] //Diagonal

else if (char j == *)
	T[i][j] = T[i-1][j] || T[i][j-1];	//Top || Left

else // if (char i != char j && char j != ? && char j != *) //however we can skip this condition, as all elements have been already memset to 0
	T[i][j] = 0;	

Result = T[len1][len2]

Regular Expression Matching :
'.' Matches any single character.
'*' Matches zero or more of the preceding element.

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true

Rows : len1 + 1 : String Text of length len1
Columns = len2 + 1 : Pattern of length len2

First Row & Column = 0
T[0][0] = 1

if(char i == char j || char j == .)
T[i][j] = T[i-1][j-1] //Diagonal

else if (char j == *)
{
	T[i][j] = T[i][j-2];	//j-2 because * means we can have empty substring as well (a* means empty string also OK)
	if(!T[i][j])	//if its 0, then only, we need to check for extra special case
	{
		if(char i == char j-1 || char j-1 = .)	//check for previous char in pattern to match with char i in text
			T[i][j] = T[i-1][j]	//Top element
	}
}

else // if (char i != char j && char j != ? && char j != *) //however we can skip this condition, as all elements have been already memset to 0
T[i][j] = 0;

Result = T[len1][len2]

*/