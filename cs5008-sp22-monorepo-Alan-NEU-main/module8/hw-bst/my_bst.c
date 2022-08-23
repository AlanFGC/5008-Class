// COMPILE USING: gcc -Wall -g bst_tests.c my_bst.c -o tests

// Include our header file for our my_bst.c
#include "my_bst.h"

// Include any other libraries needed
#include <stdio.h>
#include <stdlib.h>


// Helper functions:

bstnode_t* makeNode(int item){
  bstnode_t* p_node = (bstnode_t*)malloc(sizeof(bstnode_t));
  if(p_node == NULL){
    return NULL;
  }
  p_node->data = item;
  p_node->leftChild = NULL;
  p_node->rightChild = NULL;
  return p_node;
}

// this is a recursive function that find a place where to
// put a new node
int bst_add_r(bstnode_t* current, bstnode_t* newNode){
	if(current == NULL || newNode == NULL){
		return -1;
	}
	int result = 0;
	// two options:
	// one child is empty, assign xChild to newNode
	// child is not NULL, call this function again
	if(newNode->data <= current->data){
		if(current->leftChild == NULL){
			current->leftChild = newNode;
			return 1;
		}else{
			result = bst_add_r(current->leftChild, newNode);
			return result;
		}
	}else if(newNode->data > current->data){
		if(current->rightChild == NULL){
			current->rightChild = newNode;
			return 1;
		}else{
			result = bst_add_r(current->rightChild, newNode);
			return result;
		}
	}

	printf("Something went terribly wrong\n");
	return -1;
}


// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
bst_t* bst_create(){
    // malloc space for our bst data structure.
    bst_t* myBST = (bst_t*)malloc(sizeof(bst_t));
    if(myBST == NULL){
        return NULL;
    }
    // define values for myBST
    myBST->size = 0;
    myBST->root = NULL;
    return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(bst_t* t){
    if(t == NULL){
    	exit(1);
    }
    if(t->size == 0){
    	return 1;
    } else {
	return 0;
    }
}

// Adds a new node containng item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than or equal to the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive imlementation is suggested.
int bst_add(bst_t* t, int item){
    if(t == NULL){
		return -1;
	}
	// create new node
	bstnode_t* newNode = makeNode(item);
	if(newNode == NULL){
		return -1;
	}
	// EDGE CASE: root is empty
	if(t->root == NULL){
		t->root = newNode;
		t->size++;
		return 1;	
	}

	// recursively traverse binary search tree.
	int result;
	bstnode_t* current = t->root;
	result = bst_add_r(current, newNode);
	if(result == 1){ t->size++; }
	return result;
}

// prints recursively 
void bst_print_r(bstnode_t* node, int order){
	//case 0
	if(node == NULL){
		// autograder doesn't like this printf("(NULL)");
		return;
	}

	//case 1
	if(order == 0){
		bst_print_r(node->leftChild, order);
		printf("-%d",node->data);
		bst_print_r(node->rightChild, order);
	} else {
		bst_print_r(node->rightChild, order);
		printf("-%d", node->data);
		bst_print_r(node->leftChild, order);
	}
}


// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// A BST that is NULL should print "(NULL)"
// It should run in O(n) time.
void bst_print(bst_t *t, int order){
    if(t == NULL){
        printf("(NULL)");
		return;
    }else {
		bst_print_r(t->root, order);
    }
}

//recursive function to get the sum of all nodes
void bst_sum_r(bstnode_t* node, int* sum){
	if(node == NULL){
		return;
	}
	*sum += node->data;
	bst_sum_r(node->leftChild, sum);
	bst_sum_r(node->rightChild, sum);
	return;
}



// Returns the sum of all the nodes in the bst. 
// A BST that is NULL exits the program.
// It should run in O(n) time.
int bst_sum(bst_t *t){
  	if(t == NULL){
		exit(1);
	}
	int* sum = malloc(sizeof(int));
	*sum = 0;
	bst_sum_r(t->root, sum);
	int result;
	result = *sum;
	free(sum);
	return result;
}

//recursive function to find a node
int bst_find_r(bstnode_t* node, int value){
	//if value does not exist
	if(node == NULL){
		return 0;
	}
	//if value does exist
	if(node->data == value){
		return 1;
	}
	//recursive call to traverse binary tree
	int result;
	if(value < node->data){
		// value is smaller, get the left child
		result = bst_find_r(node->leftChild, value);
	} else {
		// value is bigger, get the right child
		result = bst_find_r(node->rightChild, value);
	}
	return result;
}


// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree -- exit the program. 
// It should run in O(log(n)) time.
int bst_find(bst_t * t, int value){
  if(t == NULL){
  	return 0;
  }
  int result = bst_find_r(t->root, value);
  return result;
}

// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){
    if(NULL == t){
		exit(1);
	}
	return t->size;
}

void bst_free_r(bstnode_t* node){
	if(node == NULL){
		return;
	}	
	bst_free_r(node->rightChild);
	bst_free_r(node->leftChild);
	free(node);
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void bst_free(bst_t* t){
	if(t == NULL){
		return;
	}
	bst_free_r(t->root);
	free(t);
}

