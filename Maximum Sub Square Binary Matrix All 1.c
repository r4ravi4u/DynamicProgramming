/*
Given a binary matrix, find out the maximum size square sub-matrix with all 1s.

T = Test Cases
n m : n rows, m columns
Matrix elements only 0 or 1 : n x m elements

2D Table T : 
Rows = n+1
Columns = m+1

Row 0 = Column 0 = 0

if M[i][j] == 1
T[i][j] = min(Top, Left, Diagonal) + 1;

Final Answer = Max of T[i][j] matrix
*/