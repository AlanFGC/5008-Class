// Compile this assignment with: gcc -g -Wall main.c -o main
// Use this file to implement testing for your
// doubly linked list implementation
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


//For all the tests: 
// 1 means passed, 0 means failed.

// genral test filling and emptying
int fill_empty(){
    int result = 1;
    dll_t * l = create_dll();
    dll_push_front(l, 1);
    dll_push_front(l, 2);
    dll_push_front(l, 3);
    dll_push_front(l, 4);
    dll_push_front(l, 5);
    dll_push_front(l, 6);
    dll_push_front(l, 7);
    dll_push_front(l, 8);
    if(l->count != 8 || dll_empty(l) != 0){
        result = 0;
    }
    dll_pop_back(l);
    dll_pop_back(l);
    dll_pop_back(l);
    dll_pop_back(l);
    dll_pop_back(l);
    dll_pop_back(l);
    dll_pop_back(l);
    dll_pop_back(l);
    if(l->count != 0){
        result = 0;
    }else if(dll_empty(l) != 1){
        result = 0;
    }
    free_dll(l);
    return result;
}

//general test for push and pop
int pop_push_test(){
    int result = 1;
    dll_t * l = create_dll();
    int i;
    for(i = 0; i < 5; i++){
        dll_push_front(l, i + 1);
    }
    for(i = 0; i < 5; i++){
        dll_push_back(l, i + 1);
    }

    if(l->count != 10){
        result = 0;
    }
    for(i = 0; i < 5; i++){
        dll_pop_front(l);
    }
    for(i = 0; i < 5; i++){
        dll_pop_back(l);
    }
     if(l->count != 0){
        result = 0;
    }
    free_dll(l);
    return result;
}

//tests all possible gets
int get_test(){
   int result = 1;
    dll_t * l = create_dll();
    int i;
    int size = 50;
    for(i = 0; i < size; i++){
        dll_push_back(l, i + 1);
    } 
    for(i = 0; i < size; i++){
        if(dll_get(l, i) != (i + 1)){
            print_dll(l);
            return 0;
        }
    }
    free_dll(l);
    return result;
}

//tests all cases of insertion
int insert_test(){
    int result = 1;
    dll_t * l = create_dll();
    int i;
    int size = 10;
    int data = 89;
    // inserting on 0 place in empty
    dll_insert(l, 1, data);
    int actual = dll_get(l, 0);
    
    if(actual != data){
        print_dll(l);
        printf("Expected: %d, Actual: %d\n", data, actual);
        result = 0;
    }
    // inserting 0 in non empty
    data = 24;
    dll_insert(l, 1, data);
    actual = dll_get(l, 0);
    
    if(actual != data){
        print_dll(l);
        printf("Expected: %d, Actual: %d\n", data, actual);
        result = 0;
    }
    //inserting back
    data = 50;
    dll_insert(l, 2, data);
    actual = dll_get(l, 2);
    
    if(actual != data){
        print_dll(l);
        printf("Expected: %d, Actual: %d\n", data, actual);
        result = 0;
    }
    //inserting middle
    data = 12;
    dll_insert(l, 2, data);
    actual = dll_get(l, 2);
    
    if(actual != data){
        print_dll(l);
        printf("Expected: %d, Actual: %d\n", data, actual);
        result = 0;
    }


    free_dll(l);
    return result;
}


int remove_test(){
    int result = 1;
    dll_t * l = create_dll();
    int i;
    for(i = 0 ;i < 10; i++ ){
        dll_push_back(l, i+1);
    }
    //remove front
    int data = 1;
    int actual = dll_get(l, 0);
    dll_remove(l, 0);
    if(data != actual){
        print_dll(l);
        printf("Data: %d, Actual: %d\n", data, actual);
        result = 0;
    }
    //remove back
    data = 9;
    dll_remove(l, 8);
    actual = dll_get(l, 7);
    if(data != actual){
        print_dll(l);
        printf("Data: %d, Actual: %d\n", data, actual);
        result = 0;
    }
    //remove from middle
    data = 5;
    dll_remove(l, 2);
    actual = dll_get(l, 2);
    if(data != actual){
        print_dll(l);
        printf("Data: %d, Actual: %d\n", data, actual);
        result = 0;
    }


    free_dll(l);
    return result;
}



// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){
    printf("===================   DEBUG  ===================\n");
    dll_t * dll = create_dll();
    if(dll == NULL){
        printf("You couldn't even create a dll, you are a disgrace!\n");
    }
    free_dll(dll);


    int unit_test[] = {
        fill_empty(),
        pop_push_test(),
        get_test(),
        insert_test(),
        remove_test()
    };
    printf("===================   Unit Tests  ===================\n");
    int size = sizeof(unit_test) / sizeof(int);
    int i;
    for(i = 0; i < size; i++){
        printf("Test %d:", i + 1);
        if(unit_test[i] == 1){
            printf("PASSED\n");
        }else {
            printf("Failed\n");
        }
    }
    return 0;
}
