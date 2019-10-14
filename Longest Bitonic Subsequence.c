/*
Given an array of positive integers. The task is to print the maximum length of Bitonic subsequence.
a subsequenceof array is called Bitonic if it is first increasing, then decreasing.

T : Test Cases
N = Array Length
n1 n2 .. Array elements

LIS Array 1 : from left to Right
LIS Array 2 : From right to left

For each i = 0 to N-1
LIS Array 1 at i + LIS Array 2 at i - 1 

max of above is our final answer .. 
*/