// =================== Support Code =================
// Hashmap 
//
// - Implement each of the functions to create a working hashmap.
// - Do not change any of the function declarations
//   - (i.e. hashmap_t* hashmap_create() should not have additional arguments)
// - You should not have any 'printf' statements in your functions other 
//   than functions that explicitly ask for printf output. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
// - You may add any helper functions that you think you need
//   (if any, or otherwise for debugging)
// ==================================================
#ifndef MY_HASHMAP_T
#define MY_HASHMAP_T

// DELETE THIS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// An entry consisting of a key-value pair.
// This is specifically for a (char*, char*) key-value pair
typedef struct pair {
    char* key;
    char* value;
} pair_t;

// Each node holds a key and a value
typedef struct node {
    pair_t* kv; // key/value pair
    struct node* next;
} node_t;


// Simple hash function that will put a key into a bucket
// You should not modify this
int stringHash(char* myKey, int numberOfBuckets){
    return strlen(myKey) % numberOfBuckets;
}

// Create a function prototype to a function that takes
// in a char* and an int.
typedef int(*hashFunctionPointer)(char*, int); 

// Chained implementation of a hashmap
typedef struct hashmap {
    unsigned int buckets;   // i.e. size of the hashmap
    node_t** arrayOfLists;  // An array of linked lists for our buckets
                            // Read another way -- an array of node_t*

    // A function pointer to a hash function
    // The hash_function must take in a 'char*' as a key, and have a
    // second parameter specifying the number of buckets.
    hashFunctionPointer hashFunction;
} hashmap_t;


//function declarations
void hashmap_freeNode(node_t* node);





// Creates a new hashmap
// Allocates memory for a new hashmap.
// Initializes the capacity(i.e. number of buckets)
// The algorithm is:
//  - allocate memory for our hashmap
//  - set the number of buckets
//  - initialize our array of lists for each bucket
//  - setup our hash function to point to our stringHash function
//  - return new map that we have created
hashmap_t* hashmap_create(unsigned int _buckets) {
	
	hashmap_t* hash_ptr = (hashmap_t*)malloc(sizeof(hashmap_t));
	if(hash_ptr == NULL){
		return NULL;
	}
	hash_ptr->buckets = _buckets;

	hash_ptr->arrayOfLists = (node_t**)malloc(sizeof(node_t*)*_buckets);
	if(hash_ptr->arrayOfLists == NULL){
		free(hash_ptr);
		return NULL;
	}

	int i;
	for(i = 0; i < _buckets; i++){
		hash_ptr->arrayOfLists[i] = NULL;
	}
	hash_ptr->hashFunction = stringHash;	
    return hash_ptr;
}

// Frees a hashmap
// Responsibility to free a hashmap that has been previously allocated.
// Must also free all of the chains in the hashmap
// This function should run in O(n) time
void hashmap_delete(hashmap_t* _hashmap) {
	if(_hashmap == NULL){
		return;
	}
	node_t* current = NULL;
	node_t* next = NULL;
	int i;
	for(i = 0 ; i < _hashmap->buckets; i++){
		current = _hashmap->arrayOfLists[i];
		while(current != NULL){
			next = current->next;
			hashmap_freeNode(current);
			current = next;
		}
	}
	free(_hashmap->arrayOfLists);
	free(_hashmap);
}

// Returns a boolean value if a key has been put into
// the hashmap
//  - Returns a '1' if a key exists already
//  - Returns a '0' if the key does not exist
//  - Returns a '-9999' if the hashmap is NULL
// The algorithm is:
//  - Call the _hashmap's hash function on the key
//  - Search that bucket to see if the key exists.
// This function should run in average-case constant time
int hashmap_hasKey(hashmap_t* _hashmap, char* key) {
	if(_hashmap == NULL){
		return -9999;
	}
	int result = 0;
	// run the hashmap function and search in bucket
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* current =  _hashmap->arrayOfLists[bucket];
	while(current != NULL){
		if(strcmp(key, current->kv->key) == 0){
			result = 1;
			return result;
		}
		current = current->next;
	}
	return result;
}

// Insert a new key/value pair into a hashmap
// The algorithm is:
//  - If a key already exists, do not add it--return
//  - Call the _hashmap's hash function on the key
//  - Store the key/value pair at the end of the buckets chain
//      - You should malloc the key/value in this function
// This function should run in average-case constant time
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value) {
    if(_hashmap == NULL){
		return;
	}
	//Define the contents of the new pair
	pair_t* newPair = (pair_t*)malloc(sizeof(pair_t));
    newPair->key = (char*)malloc(strlen(key)*sizeof(char));
    newPair->value = (char*)malloc(strlen(value)*sizeof(char));
	strcpy(newPair->key, key);
	strcpy(newPair->value, value);    
	//Check if any are null
	if(newPair == NULL || newPair->key == NULL || newPair->value == NULL){
		free(newPair->key);
		free(newPair->value);
		free(newPair);
		return;
	}
	// node 
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if(newNode == NULL){
		free(newPair->key);
		free(newPair->value);
		free(newPair);
		return;
	}
	newNode->next = NULL;	
	newNode->kv = newPair;
	//calculate node
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	//insert at the bottom of the bucket
	if(_hashmap->arrayOfLists[bucket] == NULL){
		_hashmap->arrayOfLists[bucket] = newNode;
		return;
	}

	node_t* current = _hashmap->arrayOfLists[bucket];
	node_t* prev = NULL;
	while(current != NULL){
		if(strcmp(current->kv->key, key) == 0){
			hashmap_freeNode(newNode);	
			return;
		}
		prev = current;
		current = current->next;
	}
	prev->next = newNode;
}

// Return a value from a key 
// Returns NULL if the _hashmap is NULL
// Returns NULL if the key is not found
// The algorithm is:
//  - If the key does not exist, then--return NULL if not found.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and return the value
// This function should run in average-case constant time
char* hashmap_getValue(hashmap_t* _hashmap, char* key) {
	if(_hashmap == NULL){
		return NULL;
	}
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* current = _hashmap->arrayOfLists[bucket];

	while(current != NULL){
		if(strcmp(key, current->kv->key) == 0){
			char* copy;
			copy = (char*)malloc(sizeof(char)*strlen(current->kv->value));
			strcpy(copy, current->kv->value);	
			return copy;
		}
		current = current->next;
	}
	// NOT FOUND
	return NULL;
}

// Remove a key from a hashmap
// The algorithm is:
//  - Determine if the key exists--return if it does not.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and then remove it
// This function should run in average-case constant time
void hashmap_removeKey(hashmap_t* _hashmap, char* key) {
	if(_hashmap == NULL || hashmap_hasKey(_hashmap, key) == 0){
		return;
	}
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* current = _hashmap->arrayOfLists[bucket];
	node_t* prev = NULL;
	node_t* next = current->next;
	// node is at the start of the bucket;
	if(strcmp(key, current->kv->key) == 0){
		_hashmap->arrayOfLists[bucket] = next;
		hashmap_freeNode(current);
		return;
	}	
	//Free node that it's inside the current linked list
	prev = current;
	current = current->next;
	while(current != NULL){
		if(strcmp(key, current->kv->key) == 0){
			next = current->next;
			prev->next = next;
			// free node
			hashmap_freeNode(current);
			return;
		}
		prev = current;
		current = current->next;
	}
	return;	
}

//This function free's a node structure completely.
void hashmap_freeNode(node_t* node){
	if(node == NULL){
		return;
	}
	free(node->kv->value);
	free(node->kv->key);
	free(node->kv);
	free(node);
	return;
}

// Update a key with a new Value
// The algorithm is:
//  - Returns immediately if the key does not exist
//  - Call the _hashmap's hash function on the key
//  - Updates the value of the key to the new value
// This function should run in average-case constant time
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue) {	
	if(_hashmap == NULL){
		return;
	}
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* current = _hashmap->arrayOfLists[bucket];
	if(current == NULL){
		return;
	}
	while(current != NULL){
		if(strcmp(key, current->kv->key) == 0){
			// allocate memory for new value
			current->kv->value = realloc(current->kv->value, strlen(newValue)*sizeof(char));
			if(current->kv->value == NULL){
				return;
			}
			// assign kv->value a value of newValue
			strcpy(current->kv->value, newValue);  
			return;
		}
		current = current->next;
	}
	// NOT FOUND
	return;
}

// Prints all of the keys in a hashmap
// The algorithm is:
//  - Iterate through every bucket and print out the keys
// This function should run in O(n) time
void hashmap_printKeys(hashmap_t* _hashmap){
	if(_hashmap == NULL){
		return;
	}
	int i;
	for(i=0; i<_hashmap->buckets; i++){
		printf("Bucket: %d\n", i);
		node_t* current = _hashmap->arrayOfLists[i];
		while(current != NULL){
			char* key = current->kv->key;
			char* value = current->kv->value;
			printf("%s:%s\n", key, value);
			current = current->next;
		}
	}
}

#endif
