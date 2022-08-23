// Note: This is not an exhaustive test suite, but gives you the idea
//       of some tests you might want to create.
//       Adding more tests and slowly making them more and more complicated
//       as you develop your library is recommended.
//
// Compile this assignment with: gcc -g -Wall queue_test.c -o queue_test
//
// Run with: ./queue_test
//
// This is a way to test your code.
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


// A sample test of your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.

// Tests that a new queue was created and the capacity
// was properly set.
int unitTest1(int status){
    int passed = 0;
    queue_t* testq = create_queue(30);
    if(30==testq->capacity){
        passed = 1;
    }
    free_queue(testq);
    return passed;
}

// Tests adding multiple items to a queue
int unitTest2(int status){
    int passed = 0;

    queue_t* testq = create_queue(10);
    queue_enqueue(testq,1);
    queue_enqueue(testq,2);
    queue_enqueue(testq,3);
    queue_enqueue(testq,4);
    queue_enqueue(testq,5);
    queue_enqueue(testq,6);
    queue_enqueue(testq,7);
    queue_enqueue(testq,8);
    queue_enqueue(testq,9);
    queue_enqueue(testq,10);
    if(10==queue_size(testq)){
        passed = 1;
    }

    free_queue(testq);

    return passed;
}

// Tests enqueing and dequeing
int unitTest3(int status){
    int passed = 0;

    queue_t* testq = create_queue(32);
    int i =0;
    for(i=0; i < 32; i++){
        queue_enqueue(testq,1);
    }
    for(i=0; i < 32; i++){
        queue_dequeue(testq);
    }
    
    if(0==queue_size(testq)){
        passed =1;
    }

    free_queue(testq);

    return passed;
}

// Tests enqueing and dequeing multiple times
int unitTest4(int status){
    int passed = 0;
    
    queue_t* testq = create_queue(32);
    int i =0;
    for(i=0; i < 32; i++){
        queue_enqueue(testq,1);
    }
    for(i=0; i < 32; i++){
        queue_dequeue(testq);
    }
    for(i=0; i < 32; i++){
        queue_enqueue(testq,1);
    }
    for(i=0; i < 32; i++){
        queue_dequeue(testq);
    }
    
    if(0==queue_size(testq)){
        passed =1;
    }
    
    free_queue(testq);

    return passed;
}

int unitTest5(int status){
    int passed = 0;

    queue_t* testq = create_queue(1);
    queue_enqueue(testq,1);
    if(1==queue_full(testq)){
        passed = 1;
    }else{
	    free_queue(testq);
	return 0;
    }
    queue_dequeue(testq);
    if(0==queue_full(testq)){
        passed = 1;
    }else{
        passed = 0;
    }
    free_queue(testq);
    return passed;
}

// This is my personal unit test 1
// filling emptying and checking full/empty.
int unitTestAlan1(){
	// result 1 is success, result 0 is failed.
	int cap = 10;
	int result = 1;
	queue_t* test1 = create_queue(cap);
	int i;
	//fill 
	for(i = 0; i < cap; i++){
		queue_enqueue(test1, i+1);
	}
	//check full
	if(queue_full(test1) != 1 || queue_size(test1) != cap){
		result = 0;
	}
	//dequeue
	for(i = 0; i < cap; i++){
		queue_dequeue(test1);
	}

	//check empty
	if(queue_empty(test1) != 1 || queue_size(test1) != 0){
		result = 0;
	}
    free_queue(test1);
    return result;
}



// This is my personal unit test 2
// shifting the front and back.
int unitTestAlan2(){
	// result 1 is success, result 0 is failed.
	int cap = 10;
	int result = 1;
	queue_t* test1 = create_queue(cap);
	int i;
	//fill add 5
	for(i = 0; i < 5; i++){
		queue_enqueue(test1, i+1);
	}
	//check mid full
	if(queue_full(test1) !=  0 || queue_size(test1) != 5){
		result = 0;
	}
	//dequeue rem 2
	for(i = 0; i < 2; i++){
		queue_dequeue(test1);
	}
    //fill add 3
	for(i = 0; i < 3; i++){
		queue_enqueue(test1, i+1);
	}
    //check size
	if(queue_full(test1) !=  0 || queue_size(test1) != 6){
		result = 0;
	}
    //fill add 4
	for(i = 0; i < 4; i++){
		queue_enqueue(test1, i+1);
	}
    //check full
	if(queue_full(test1) !=  1 || queue_size(test1) != cap){
		result = 0;
	}
    //dequeue rem all
	for(i = 0; i < cap; i++){
		queue_dequeue(test1);
	} 
	//check empty
	if(queue_empty(test1) != 1 || queue_size(test1) != 0){
		result = 0;
	}
    free_queue(test1);
    return result;
}



// This is my personal unit test 3
// Spamming dequeue and enqueue
int unitTestAlan3(){
	// result 1 is success, result 0 is failed.
	int cap = 9999999;
	int result = 1;
	queue_t* test1 = create_queue(cap);
	int i;

	//spam
	for(i = 0; i < 9999999; i++){
		queue_enqueue(test1, i+1);
        queue_dequeue(test1);
	}
	//check empty
	if(queue_empty(test1) != 1 || queue_size(test1) != 0){
		result = 0;
	}
    free_queue(test1);
    return result;
}



// This is my personal unit test 4
// Single element enqueueing and dequeueing
int unitTestAlan4(){
	// result 1 is success, result 0 is failed.
	int result = 1;
	queue_t* test1 = create_queue(1);

    queue_enqueue(test1, 9);
    if(queue_full(test1) !=  1 || queue_size(test1) != 1){
		result = 0;
	}
    int fail = queue_dequeue(test1);

    if(fail != 9){
        printf("Dequeue result is: %d\n", fail);
        result = 0;
    }
	//check empty
	if(queue_empty(test1) != 1 || queue_size(test1) != 0){
		result = 0;
        printf("Dequeue result is: %d\n", fail);
	}
    free_queue(test1);
    return result;
}



// TODO: Add more tests here
int (*unitTests[])(int)={
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
    unitTest5,
    unitTestAlan1,
    unitTestAlan2,
    unitTestAlan3,
    unitTestAlan4,
    NULL
};



// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){
    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter]!=NULL){
	printf("========unitTest %d========\n",counter);
        if(1==unitTests[counter](1)){
		printf("passed test\n");
		testsPassed++;	
	}else{
		printf("failed test, missing functionality, or incorrect test\n");
	}
        counter++;
    }

    printf("%d of %d tests passed\n",testsPassed,counter);

    return 0;
}
