 /*
 *Alan Garcia 
 *Lab 2 -- Linked List
 *Compiled with: gcc
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int wins;
  int year;
  struct node* next;
}node_t;

/*
 *This function takes a year and the number of wins,
 *returns a node of single linked list.
 *param:
 *wins - number of wins that year.
 *year - year when wins took place.
 *return: a node from a single linked list.
 */
node_t* make_node(int wins, int year){
  node_t* p_node = (node_t*)malloc(sizeof(node_t));
  if(p_node == NULL){
    return NULL;
  }
  p_node->wins = wins;
  p_node->year = year;
  p_node->next = NULL;
  return p_node;
}


/*
 *This function takes in two arrays of equal size
 *containing years and wins, then creates a single linked list.
 *param:
 *years - array contianing each year.
 *wins - array contianing number of wins in that year.
 *size - size of the two arrays.
 *return: The head of a linked list containing the information.
*/
node_t* create_list(int years[], int wins[], int size){
  if(size <= 0){
    return NULL;
  }
  //create a temporal list
  node_t* temp_list_p[size];
  //make head
  node_t* head = make_node(wins[0], years[0]);
  temp_list_p[0] = head;
  //fill the list
  int i;
  for(i = 1;i<size;i++){
    temp_list_p[i] = make_node(wins[i], years[i]);
  }
  //link the list
  for(i = 0;i < (size - 1); i++){
    temp_list_p[i]->next = temp_list_p[i+1];
  }
  return head;
}

/*
 *This function prints a linked list
 *param: the head of a linked list.
 */
void print_list(node_t* current){
  while(current != NULL){
    printf("%d, %d wins\n", current->year, current->wins);
    current = current->next;
  }
  return;
}

/*
 *This function frees memory one by one node
 *from a linked list.
 *param:the head of a linked list.
 */
void free_list(node_t* current){
  node_t* next = current->next;
  while(next != NULL){
    next = current->next;
    free(current);
    current = next;
  }
  return;
}

// main driver
int main(){
  int years[] = {2018, 2017, 2016, 2015, 2014, 2013, 2012};
  int wins[] = {108, 93, 93, 78, 71, 38, 100};
  node_t* list = create_list(years, wins, sizeof(years)/sizeof(int));
  print_list(list);
  free_list(list);
  return 0;
}
