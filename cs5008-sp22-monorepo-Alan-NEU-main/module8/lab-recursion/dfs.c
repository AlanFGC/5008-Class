// Compile with: clang -Wall dfs.c -o dfs
// Run with: ./dfs
//
// This is a great lab to practice debugging.
// First compile with debugging symbols
// Compile with: clang -Wall -g dfs.c -o dfs
// Run with: gdb ./dfs --tui
//   Then type 'start'
//   Then type 'next' or 'n' and enter
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
  struct TreeNode* left;
  struct TreeNode* right;
  char data;
} TreeNode_t;


//
void free_tree(TreeNode_t* node){
	if(node == NULL){
		return;
	}
	free_tree(node->left);
	free_tree(node->right);
	free(node);
}


// Depth-First Tree Traversal
// Make sure to print out each node you visit, and only print it out once!
// **Hint** Think recursively
void dfs(TreeNode_t* start){
    if(start == NULL){
    	return;
    }
    // marks as visited
    printf("%c", start->data);
    // some authors prefer to mark the last to the left as visited first
    // then mark the current one. Lastly, mark the ones to the right.
    dfs(start->left);
    dfs(start->right);
}

int main(){

  // Manually create a tree for this lab
  TreeNode_t* start = malloc(sizeof(TreeNode_t));
  TreeNode_t* a= malloc(sizeof(TreeNode_t));
  TreeNode_t* b= malloc(sizeof(TreeNode_t));
  TreeNode_t* c= malloc(sizeof(TreeNode_t));
  TreeNode_t* d= malloc(sizeof(TreeNode_t));
  TreeNode_t* e= malloc(sizeof(TreeNode_t));
  TreeNode_t* f= malloc(sizeof(TreeNode_t));
  TreeNode_t* g= malloc(sizeof(TreeNode_t));
  TreeNode_t* h= malloc(sizeof(TreeNode_t));

  // The root of our tree  
  // The root also has two 'branches' a and b.
  start->data = 's';
  start->left = a;
  start->right = b;
  
  a->data = 'a';
  a->left = c;
  a->right = d;
  
  b->data = 'b';
  b->left = e;
  b->right = f;
  
  c->data = 'c';
  c->left = g;
  c->right = h;

  // All of the 'leaves' in our tree
  d->data = 'd';
  d->left = NULL;
  d->right = NULL;   
  
  e->data = 'e';
  e->left = NULL;
  e->right = NULL;

  f->data = 'f';
  f->left = NULL;
  f->right = NULL;
  
  g->data='g';
  g->left = NULL;
  g->right = NULL;

  h->data = 'h';
  h->left = NULL;
  h->right = NULL;
  
  // Perform the dfs
  dfs(start);
  printf("\n");
  // Perform the dfs at a different spot)
  dfs(b);
  // free memory
  free_tree(start);
  return 0;
}

