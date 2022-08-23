// gcc -Wall factorial.c -o factorial
// ./factorial

#include <stdio.h>

unsigned long long int factorial(int n){
	int i;
	unsigned long long int res = 1;
  	for(i = 1; i <= n; i++){
		res = res * i;
	}
  	return res;
}

unsigned long long int factorial_rec(int n){
	if(n == 0 || n == 1){
		return 1;	
	}
	return (n * factorial_rec(n-1));
}

int main(){
	int fact = 65;
	// Both of these should print the same result!
	printf("factorial(%d) = %llu\n", fact, factorial(fact));
	printf("factorial_rec(%d) = %llu\n", fact, factorial_rec(fact));
	return 0;
}
