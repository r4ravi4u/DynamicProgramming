/*
Given an integer N, how many structurally unique binary search trees are there that store values 1...N?

1D Table of length N+1 : 0 to N

T[0] = 0
T[1] = 1
T[2] = 2

for(int i=2;i<=N;i++)
{
	for(int j=0;j<i;j++)
	{
		T[i] += T[j] * T[i-j-1]	//Catalan No.		((2n)!/(n+1)!*n!)
	}
}


Same above concept is used in case preorder of a Binary tree is given of length N
*/