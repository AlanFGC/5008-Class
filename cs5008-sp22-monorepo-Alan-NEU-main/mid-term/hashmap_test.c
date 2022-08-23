// Note: This is not an exhaustive test suite, but gives you the idea
//       of some tests you might want to create.
//
// Compile this assignment with: gcc -g -Wall hashmap_test.c -o hashmap_test
//
// Run with: ./hashmap_test
//
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_hashmap.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


// A sample collection of tests for your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.


// Tests creation and deletion of the hashmap
// Ideally does not cause any segfaults, and this
// is considered passing.
int unitTest1(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(12);    
    hashmap_delete(test);
    passed = 1;
    return passed;
}

// Tests has_key for a missing key
int unitTest2(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    
    if(hashmap_hasKey(test, "cow")==0){
      passed = 1;
    }
    
    hashmap_delete(test);
    return passed;
}


// Tests insert and has_key
int unitTest3(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    hashmap_insert(test,"cow","A common farm animal.");
    
    if(hashmap_hasKey(test, "cow")==1) {
      passed = 1;
    }
    
    hashmap_delete(test);
    return passed;
}

// Tests insert and has_key and remove key
int unitTest4(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    hashmap_insert(test,"cow","A common farm animal.");
    hashmap_removeKey(test, "cow");
    
    if(hashmap_hasKey(test, "cow")==0) {
      passed = 1;
    }
    
    hashmap_delete(test);

    return passed;
}

// Tests update_key
int unitTest5(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    hashmap_insert(test,"cow","A common farm animal.");
    hashmap_update(test, "cow", "A common farm animal in Ohio.");
    hashmap_printKeys(test);
    if(hashmap_hasKey(test, "cow")==1) {
      passed = 1;
    }
    hashmap_delete(test);
    return passed;
}


//general test for Inserting
// 1 is passed, 0 is failed
int testInserting(int status){
    int passed = 1;
    hashmap_t* map = hashmap_create(3);
    hashmap_insert(map, "a", "value of a");
    hashmap_insert(map, "ab", "value of ab");
    hashmap_insert(map, "abc", "value of ac");
    // This should not generate new keys or
    // create memory leaks
    hashmap_insert(map, "a", "this should not exist");
    hashmap_insert(map, "ab", "this should not exist");
    hashmap_insert(map, "abc", "this should not exist");
    char* val1 = hashmap_getValue(map, "a");
    if(strcmp(val1, "value of a") != 0){
        passed = 0;
    }
    // add more to each list and test again
    hashmap_insert(map, "g", "this a random value");
    hashmap_insert(map, "fd", "this a random value");
    hashmap_insert(map, "fds", "this a random value");
    char* val2 = hashmap_getValue(map, "a");
    if(strcmp(val2, "value of a") != 0){
        passed = 0;
    }
    char* val3 = hashmap_getValue(map, "fds");
    if(strcmp(val3, "this a random value") != 0){
        passed = 0;
    }
    free(val1);
    free(val2);
    free(val3);
    hashmap_delete(map);
    return passed;
}


//general test for getValue
// 1 is passed, 0 is failed
int testgetValue(int status){
    int result = 1;
    hashmap_t* map = hashmap_create(5);
    hashmap_insert(map, "hello", "value of a");
    hashmap_insert(map, "pello", "value of b");
    hashmap_insert(map, "tello", "value of c");
    hashmap_insert(map, "z", "value of d");
    char* valA = hashmap_getValue(map, "hello");
    char* valB = hashmap_getValue(map, "pello");
    char* valC = hashmap_getValue(map, "tello");
    char* valD = hashmap_getValue(map, "z");
    if(strcmp(valA, "value of a") != 0){
        printf("Failed: %s\n", valA);
		result = 0;
	}
    if(strcmp(valB, "value of b") != 0){
        printf("Failed: %s\n", valB);
		result = 0;
	}
    if(strcmp(valC, "value of c") != 0){
        printf("Failed: %s\n", valC);
		result = 0;
	}
    if(strcmp(valD, "value of d") != 0){
        printf("Failed: %s\n", valD);
		result = 0;
    }
    free(valA);
    free(valB);
    free(valC);
    free(valD);
    hashmap_delete(map);
    return result;
}

//this function should be used along with valgrind to test
// for memory leaks
int deleteEmpty(int status){
    hashmap_t* map = hashmap_create(12);
    hashmap_delete(map);
    return 1;
}


//this is general test for update
int testUpdate(int status){
    int result  = 1;
    hashmap_t* map = hashmap_create(8);
    //insert 
    hashmap_insert(map, "hello", "value of a");
    hashmap_insert(map, "pello", "value of b");
    hashmap_insert(map, "tello", "value of c");
    hashmap_insert(map, "firetruck", "value of d");
    //update
    hashmap_update(map, "hello", "new value of a");
    hashmap_update(map, "pello", "new value of b");
    hashmap_update(map, "tello", "new value of c");
    hashmap_update(map, "firetruck", "new value of d");


    char* valA = hashmap_getValue(map, "hello");
    char* valB = hashmap_getValue(map, "pello");
    char* valC = hashmap_getValue(map, "tello");
    char* valD = hashmap_getValue(map, "firetruck");
    
    if(strcmp(valA, "new value of a") != 0){
        result = result - 1;
    }
    if(strcmp(valB, "new value of b") != 0){
        result = result - 1;
    }

    if(strcmp(valC, "new value of c") != 0){
        result = result - 1;
    }

    if(strcmp(valD, "new value of d") != 0){
        
        result = result - 1;
    }

    free(valA);
    free(valB);
    free(valC);
    free(valD);
    hashmap_delete(map);
    return result;
}

//test remove elements in different orders
int testRemove(int status){
    int result  = 1;
    hashmap_t* map = hashmap_create(8);
    hashmap_insert(map, "hello", "value of a");
    hashmap_insert(map, "pello", "value of b");
    hashmap_insert(map, "tello", "value of c");
    hashmap_insert(map, "firetruck", "value of d");
    //remove in order
    hashmap_removeKey(map, "hello");
    hashmap_removeKey(map, "pello");
    hashmap_removeKey(map, "tello");
    hashmap_removeKey(map, "firetruck");
    // check
    if(hashmap_hasKey(map, "hello") == 1){
        result = result - 1;
    }
    if(hashmap_hasKey(map, "pello") == 1){
        result = result - 1;
    }
    if(hashmap_hasKey(map, "tello") == 1){
        result = result - 1;
    }
    if(hashmap_hasKey(map, "firetruck") == 1){
        result = result - 1;
    }

    //insert again
    hashmap_insert(map, "hello", "value of a");
    hashmap_insert(map, "pello", "value of b");
    hashmap_insert(map, "tello", "value of c");
    //remove middle first
    hashmap_removeKey(map, "pello");
    hashmap_removeKey(map, "hello");
    hashmap_removeKey(map, "tello");
    // check
    if(hashmap_hasKey(map, "hello") == 1){
        result = result - 1;
    }
    if(hashmap_hasKey(map, "pello") == 1){
        result = result - 1;
    }
    if(hashmap_hasKey(map, "tello") == 1){
        result = result - 1;
    }


    //insert again
    hashmap_insert(map, "hello", "value of a");
    hashmap_insert(map, "pello", "value of b");
    hashmap_insert(map, "tello", "value of c");
    //remove last first
    hashmap_removeKey(map, "tello");
    hashmap_removeKey(map, "hello");
    hashmap_removeKey(map, "pello");
    // check
    if(hashmap_hasKey(map, "hello") == 1){
        result = result - 1;
    }
    if(hashmap_hasKey(map, "pello") == 1){
        result = result - 1;
    }
    if(hashmap_hasKey(map, "tello") == 1){
        result = result - 1;
    }

    // test remove on updated element
    hashmap_insert(map, "hello", "value of a");
    hashmap_update(map, "hello", "new value of a");
    //remove
    hashmap_removeKey(map, "hello");
    //check
    if(hashmap_hasKey(map, "hello") == 1){
        result = result - 1;
    }

    hashmap_delete(map);
    return result;
}

// TODO: Add more tests here at your discretion
int (*unitTests[])(int)={
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
    unitTest5,
    testInserting,
    testgetValue,
    deleteEmpty,
    testUpdate,
    testRemove,
    NULL
};


// ====================================================
// ================== Program Entry ===================
// ====================================================
int main() {
    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter]!=NULL){
	printf("========unitTest %d========\n", counter);
        if(1==unitTests[counter](1)){
		printf("passed test\n");
		testsPassed++;	
	}else{
		printf("failed test, missing functionality, or incorrect test\n");
	}
        counter++;
    }

    printf("%d of %d tests passed\n", testsPassed, counter);

    return 0;
}