/*
Problem statement: Consider a row of n coins of values v1 . . . vn, where n is even. We play a game against an opponent by alternating turns. In each turn, a player selects either the first or last coin from the row, removes it from the row permanently, and receives the value of the coin. Determine the maximum possible amount of money we can definitely win if we move first.

T : Test Case
N : no. of coins (always even)
n1 n2 ... " Value of coins

struct table
{
	int p1;	//player 1 amount won till now
	int p2;	//player 2
}

2D Table : of above structure
Rows = Columns = N

Filled up in Diagonal manner

If there is only 1 coin, so p2 can take only 0, p1 will take that coin
T[i][i].p1 = arr[i]
T[i][i].p2 = 0

T[i][j].p1 = max(arr[i] + T[i+1][j].p2 , arr[j] + T[i][j-1].p2);
T[i][j].p2 = min(p1 of left and down) = min(T[i][j-1].p1, T[i+1][j].p1);

*/
