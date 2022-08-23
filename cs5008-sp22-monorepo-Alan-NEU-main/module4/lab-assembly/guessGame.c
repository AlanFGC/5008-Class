/*
Author: Alan Garcia
Description: binary search guessing game.
compiled using GCC.no arguments needed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Definitions
int playGame();
int randInRange(int lower, int upper);
int getAverage(int [], int);
void printScores(int [], int);

// MAIN DRIVER
int  main(){
    //this is the main driver of the program.
    //It plays the games 5 times before ending.
  int totalGames = 5;
  int scores[totalGames];
  int games = 0;
  while(games < totalGames){
      scores[games] = playGame();
      games++;
  }
  printScores(scores, totalGames);
  int averageScore = getAverage(scores, totalGames);
  printf("The average number of guesses of the last %d games is: %d\n", totalGames, averageScore); 
  return 0;
}

void printScores(int scores[], int size){
    // This function takes an arra of ints with its size.
    // then prints each int inside the array.
    //return none
  int i;
  printf("=================================================\n");
  printf("|Here are the results of your guessing abilities|\n");
  printf("=================================================\n");
  for(i = 0;i < size;i++){
    printf("Game %d took you %d guesses\n", i + 1, scores[i]);
  }
  return;
}

int getAverage(int scores[], int size){
    // This function takes an arra of ints with its size.
    // calculates the averages and rounds the result
    // to the nearest integer.
    //return average score (int)
  int result;
  float average, difference, sum = 0, size_f = (float)size;
  int i, averageInt;
  for(i = 0;i < size;i++){
    // printf("%d\n", scores[i]);
    sum += scores[i];
  }
  
  average = sum / size_f;
  averageInt = (int) average;

  //Rounding result:
  //note to self: dividing two integer results into a float results in
  //no decimal number.
  //ex. 12/5 = 2.00. To solve must only use floats.
  difference = average - averageInt;
  // printf("Difference: %f\tAverage: %f\tAverage Int:%d\n", difference, average, averageInt);
  if(difference > 0.5000){
    result = average + 1;
  }else {
    result = average;
  }
  return result;
}


int playGame(){
    //This function plays the guessing game.
    //It prompts the user for an int number between 1
    // and 20.
    //return none
  int num_guess = 0;
  //random number between 1 and 20
  int r_number = randInRange(1, 20);
  int guess = r_number + 1;
  printf("============================================\n");
  printf("CPU says: Pick a random number from 1 - 20\n");
  printf("============================================\n");
  //printf("Rand num is: %d\n", r_number);
  while(guess != r_number){
    printf("Make a guess:\t");
    scanf("%d", &guess);
    num_guess++;
    if(guess < r_number){
      printf("Too Low\n");
    }else if(guess > r_number){
      printf("Too High\n");
    }else{
      printf("Correct! - Number of guesses:%d\n", num_guess);
    }
  }
  return num_guess;
}


int randInRange(int lower, int upper){
    //This functions returns a random int
    // using a lower and upper value of ints.
    // return: random int, in range of lower to upper.
  float randNumber;
  int range = (upper - lower) + 1;
  srand(time(NULL));
  randNumber = rand() % range;
  randNumber += lower;
  return randNumber;
}
