#include<stdio.h> 
int fibonacci(int n) 
{ 
if (n==1||n==0)
	return n; 
return fibonacci(n-1) + fibonacci(n-2); 
} 

int main () 
{ 
  int n;
  printf("Enter the number");
  scanf("%d",&n); 
  printf("Fibonacci number of %d : %d", n, fibonacci(n)); 
  return 0; 
}
