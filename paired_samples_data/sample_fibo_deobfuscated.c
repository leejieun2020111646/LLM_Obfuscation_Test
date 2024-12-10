#include<stdio.h> 
int fibonacci(int n) 
{ 
if (n==1||n==0)
	return n; 
return fibonacci(n-1) + fibonacci(n-2); 
} 

int main () 
{ 
  int num;
  printf("Enter the number");
  scanf("%d",&num); 
  printf("Fibonacci number of %d : %d\n", num, fibonacci(num)); 
  return 0; 
}
