// Compile this assignment with: gcc -Wall bst_tests.c -o tests
//
// This is a great assignment to practice debugging.
// First compile with debugging symbols
// Compile with: gcc -Wall -g bst_tests.c my_bst.c -o tests
// Run with: gdb ./tests --tui
// Then type 'start'
// Then type 'next' or 'n' and enter
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_bst.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// You may add as many unit tests as you like here
// A few have been provided for your convenience.
// We will use our own test suite (i.e. replacing this file)
// in order to test your implementation from my_bst.

// Testing allocation
int unitTest1(){
    int result = 0;
    bst_t * testBST = bst_create();
    if (testBST!=NULL){
        result = 1;
    }else{
        result = 0;
    }
    bst_free(testBST);
    return result;
}

// Add and find a node
int unitTest2(){
    int result = 0;
    bst_t * testBST = bst_create();
    bst_add(testBST,78);
    result = bst_find(testBST,78);
    bst_free(testBST);
    return result;
}

// Sums the nodes in a BST
int unitTest3(){
    int result = 0;
    bst_t * testBST = bst_create();
    bst_add(testBST, 5);
    result = bst_sum(testBST);
    bst_free(testBST);

    if(result==5){ 
        return 1;
    }
    return 0;
}

// 1 if passed 0 if not
// this test will indirectly test many different features.
int sumTest(){
	int result = 0;
	int i;
	bst_t * testBST = bst_create();
	bst_add(testBST, 50);
	for(i = 1; i < 50; i++){
		bst_add(testBST, i);
	}
	for(i = 51; i <= 100; i++){
		bst_add(testBST, i);
	}
	result = bst_sum(testBST);
	bst_free(testBST);
	if(result == 5050){
		return 1;
	}
	return 0;
}

// THIS TEST NEED TO BE MANUALLY LOOKED AT
int printTest(){
	int result = 0;
	int i;
	bst_t * testBST = bst_create();
	for(i = 1; i < 10; i++){
		bst_add(testBST, i);
	}
    bst_print(testBST, 0);
    printf("\n");
    bst_print(testBST, 1);
    printf("\n");
	bst_free(testBST);
    // output:
    /*
    *   -(NULL)-1-(NULL)-2-(NULL)-3-(NULL)-4-(NULL)-5-(NULL)-6-(NULL)-7-(NULL)-8-(NULL)-9-(NULL)
    *   -(NULL)-9-(NULL)-8-(NULL)-7-(NULL)-6-(NULL)-5-(NULL)-4-(NULL)-3-(NULL)-2-(NULL)-1-(NULL)
    *   Correct
    */
    result = 1;
	return result;
}

//Find test
int findTest(){
	int result = 0;
	int i;
	bst_t * testBST = bst_create();
	bst_add(testBST, 101);
	for(i = 1; i <= 50; i++){
		bst_add(testBST, i);
	}
	for(i = 125; i <= 170; i++){
		bst_add(testBST, i);
	}
	result = bst_find(testBST, 101);
	bst_free(testBST);
	return result;
}


// TODO: Add more tests here at your discretion
int (*unitTests[])(int) = {
    unitTest1,
    unitTest2,
    unitTest3,
	sumTest,
    printTest,
    findTest,
    NULL
};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){
	
    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter] != NULL){
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
