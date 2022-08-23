/*
=============================
Alan Garcia 
Lab 1
Compiled: gcc 
=============================
 */

#include <stdlib.h>
#include <stdio.h>

// definitions
double power(double base, double n);

int main(){
    // main drive of the program
  int i;
  for(i = 1; i <= 10; i++){
        printf("%f \n", power(2, i));
  }
}

double power(double base, double n){
  //Power: this function takes two numbers and raises n to the
  //power of base.
  //returns the result of base^n. 
  double i = 0;
  double result = 1;
  if(n == 0 && base != 0){
    return result;
  }

  if(n == 0 && base == 0){
    result = 0;
    return result;
  }

  while(i < n){
    result = result * base;
    i++;  
  }

  return result;
}
