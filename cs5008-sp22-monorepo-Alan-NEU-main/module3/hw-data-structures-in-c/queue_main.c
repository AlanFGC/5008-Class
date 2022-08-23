// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "myqueue.h"
// Note that we are locating this file
// within the same directory, so we use quotations 
// and provide the path to this file which is within
// our current directory.


// This is my personal unit test 1
//filling emptying and checking full/empty.
void unitTestAlan1(){
	printf("Unit Test 1:\n");
	// result 0 is success, result 1 is failed.
	int cap = 10;
	int result = 0;
	queue_t* test1 = create_queue(cap);
	int i;
	//fill 
	for(i = 0; i < cap; i++){
		queue_enqueue(test1, i+1);
	}
	//check full
	if(queue_full(test1) != 1 || queue_size(test1) != cap){
		result += 1;
	}
	//dequeue
	for(i = 0; i < cap; i++){
		queue_dequeue(test1);
	}

	//check empty
	if(queue_empty(test1) != 1 || queue_size(test1) != 0){
		result += 2;
	}
	if(result == 0){
		printf("Test passed: %d\n", result);
	}else{
		printf("Test failed: %d\n", result);
	}
}
// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){

	// List of Unit Tests to test your data structure	
	unitTestAlan1();

	return 0;
}
