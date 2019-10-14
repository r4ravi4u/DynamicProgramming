/*
Rabin Karp uses hash method : 

Hash method could be like : 
char 0 + char1*(any prime no.^1) + char2*(prime no.^2 ... n so on

For pattern part : 
char 0 + char 1 * (p^1) + char 2 * (p^2) ... & so on = hash value

For text string : 

ex. string is abcdef ...
& pattern contains 3 chars, so for every 3 chars check hash value ..

h(abc) = x;
so h(bcd) = ((x - a)/p) + d*p^(n-1)  //where n=len of pattern

if hash matches, we shall match that part of the string with pattern, if it matches, we found else we need to proceed like this only for rest of the string

*/