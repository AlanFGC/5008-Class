// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node {
	int data;
	struct node* next;
  	struct node* previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
	int count;		// count keeps track of how many items are in the DLL.
	node_t* head;		// head points to the first node in our DLL.
    node_t * tail;          //tail points to the last node in our DLL.
} dll_t;




//declarations:
void print_dll(dll_t* t);

// finds a node and returns a pointer to that node.
node_t* dll_find(dll_t* l, int pos){
	if(l == NULL){
		return NULL;
	}
	// verify position
	if(pos >= l->count || pos < 0 || l->count == 0){
		return NULL;
	}
	// navigate linked list
	node_t* current = l->head;
	int index = 0;
	while(index != pos){
		current = current->next;
		index++;
	}
	return current;
}

//Creates a new node
node_t* make_node(int item){
  node_t* p_node = (node_t*)malloc(sizeof(node_t));
  if(p_node == NULL){
    return NULL;
  }
  p_node->data = item;
  p_node->previous = NULL;
  p_node->next = NULL;
  return p_node;
}



// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
	// Modify the body of this function as needed.
	dll_t* myDLL= (dll_t*)malloc(sizeof(dll_t));
	if(myDLL == NULL){
		return NULL;
	}

	myDLL->count = 0;
	myDLL->head = NULL;
	myDLL->tail = NULL;
	return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns -1 if the dll is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* l){
	if(l == NULL){
		return -1;
	}

	if(l->count == 0){
		return 1;
	}else if(l->count > 0){
		return 0;
	}
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, int item){
	if(l == NULL){
		return -1;
	}
	
	node_t* newNode = make_node(item);
	if(newNode == NULL){
		return 0;
	}
	if(l->head != NULL){
		l->head->previous = newNode;
	}
	newNode->next = l->head;
	newNode->previous = NULL;
	l->head = newNode;
	if(l->count == 0){
		l->tail = newNode;
	}
	l->count++;
	return 1;
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, int item){
	if(l == NULL){
		return -1;
	}

	node_t* newNode = make_node(item);
	if(newNode == NULL){
		return 0;
	}

	if(l->tail != NULL){
		l->tail->next = newNode;
	}
	newNode->previous = l->tail;
	newNode->next = NULL;
	l->tail = newNode;
	if(newNode->previous == NULL){
		l->head = newNode;
	}
	l->count++;
	return 1;
}

// Returns the first item in the DLL and also removes it from the list.
// Returns -1 if the DLL is NULL. 
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_front(dll_t* t){
	if(t == NULL){
		return -1;
	}

	node_t* node;
	node = t->head;

	if(node == NULL){
		return 0;
	}

	int item;
	item = node->data;
	t->head = node->next;
	if(t->head != NULL){
		t->head->previous = NULL;
	}
	if(t->count == 1){
		t->tail = NULL;
	}

	free(node);
	t->count--;
	return item;
}

// Returns the last item in the DLL, and also removes it from the list.
// Returns a -1 if the DLL is NULL. 
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_back(dll_t* t){
	if(t == NULL){
		return -1;
	}
	node_t* node;
	node = t->tail;

	if(node == NULL){
		return 0;
	}
	
	int item;
	item = node->data;
	t->tail = node->previous;
	if(t->tail != NULL){
		t->tail->next = NULL;
	}

	if(t->count == 1){
		t->head = NULL;
	}

	free(node);
	t->count--;
	return item;
}

// Inserts a new node before the node at the specified position.
// Returns -1 if the list is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t* l, int pos, int item){
	// inserts node BEFORE the given positon
	if(l == NULL){
		return -1;
	}
	if(pos < 0){
		return 0;
	}
	if(pos > l->count + 1 && l->count > 0){
		return 0;
	}

	int result;
	if(pos == 1 || pos == 0){
		result = dll_push_front(l, item);
		return result;
	} else if(pos == l->count){
		result = dll_push_back(l, item);
		return result;
	} 

	node_t* current_pos = dll_find(l, pos);
	node_t* newNode = make_node(item);
	if(current_pos == NULL || newNode == NULL){
		return 0;
	}
	// do the good old switcheru
	// configure new node
	newNode->next = current_pos;
	newNode->previous = current_pos->previous;
	if(current_pos != NULL){
		current_pos->previous->next = newNode;
	}
	current_pos->previous = newNode;
	l->count++;
	return 1;
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
//  (does not remove the item)
// Returns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
int dll_get(dll_t* l, int pos){
	if(l == NULL){
		return -1;
	}
	if(pos > (l->count + 1) || pos < 0){
		return 0;
	}
	node_t* current = dll_find(l, pos);
	if(current == NULL){
		return 0;
	}
	int item = 0;
	item = current->data;
	return item;
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
// Returns 0 on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
int dll_remove(dll_t* l, int pos){
	if(l == NULL){
		return -1;
	}
	//failed
	if(pos > (l->count - 1) || pos < 0){
		return 0;
	}
	// pop front or back
	int item;
	if(pos == l->count - 1){
		dll_pop_back(l);
		return 1;
	}else if(pos == 0){
		dll_pop_front(l);
		return 1;
	}
	// find node
	node_t* current_pos = dll_find(l, pos);
	if(current_pos == NULL){
		return 0;
	}
	// reconfigure list
	current_pos->previous->next = current_pos->next;
	current_pos->next->previous = current_pos->previous;
	item = current_pos->data;
	free(current_pos);
	l->count--;
	return 1;
}

// DLL Size
// Returns -1 if the DLL is NULL.
// Queries the current size of a DLL
int dll_size(dll_t* t){
	if(t == NULL){
		return -1;
	}
	return t->count;
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
	while(t->count>0){
		dll_pop_front(t);
	}
	free(t);
}

// self explanatory function here
// this is a debugging tool for myself
void print_dll(dll_t* t){
	if(t == NULL){
		printf("List is NULL\n");
	}
	node_t* current_node = t->head;
	int int_count = 0;
	printf("Number of nodes: %d\t HEAD: %p TAIL: %p\n", t->count, t->head, t->tail);
	while(current_node != NULL){
		printf("N:%d item: %d \tPrev: %p\t", int_count, current_node->data,
		 current_node->previous);
		printf("pointer: %p\t pointer Next: %p\n", current_node, current_node->next);
		int_count++;
		current_node = current_node->next;
	}
}

#endif
