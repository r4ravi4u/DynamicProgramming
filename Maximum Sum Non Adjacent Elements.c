/*
Stickler is a thief and wants to loot money from a society of n houses placed in a line. He is a weird person and follows a rule while looting the houses and according to the rule he will never loot two consecutive houses. At the same time, he wants to maximize the amount he loots. The thief knows which house has what amount of money but is unable to find the maximum amount he can end up with. He asks for your help to find the maximum money he can get if he strictly follows the rule. Each house has a[i] amount of money present in it.

Given an array of positive numbers, find the maximum sum of a subsequence with the constraint that no 2 numbers in the sequence should be adjacent in the array. So 3 2 7 10 should return 13 (sum of 3 and 10) or 3 2 5 10 7 should return 15 (sum of 3, 5 and 7).Answer the question in most efficient way.

T : Test Cases
N : No. of elements in array
n1 n2 ... : Array elements

incl = arr[0]
excl = 0

i = 1 to N-1

incl = max(incl, excl + arr[i])
excl = last incl (hence we need to store incl first somewhere to restore it in excl)

*/