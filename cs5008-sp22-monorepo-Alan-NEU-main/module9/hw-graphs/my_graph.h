// =================== Support Code =================
// Graph.
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
} graph_t;

typedef struct graph_node{
    int visited;
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;

//declarations:
void free_graph_node(graph_node_t*);

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph= malloc(sizeof(graph_t));
    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t * g, int value){
    // list of all the nodes
    dll_t* list = g->nodes;
    // dll node
    node_t* node = list->head;

    while(node != NULL){
        // grab the curent node
        graph_node_t* graphNode = node->data;
        //compare graph node int data to value
        if(graphNode->data == value){
            return node->data;
        }
        node = node->next;
    }
    return NULL;
}

// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){
    graph_node_t * graph_node = malloc(sizeof(graph_node_t));
    
    if ( graph_node == NULL ) return NULL;
    
    graph_node->visited = 0                 ;
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    
    return graph_node;
}

// Returns n > 0 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;
    
    if (find_node(g, value) != NULL) return -1;
    
    graph_node_t * newNode = create_graph_node(value);
    if ( newNode == NULL ) return -1;
    
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    
    return 1;
}


int graph_remove_edges_node(graph_t* g, graph_node_t* node){
    int nodeValue = node->data;
    int currentValue;
    dll_t* inNeighbors = node->inNeighbors;
    dll_t* outNeighbors = node->outNeighbors;
    graph_node_t* currentNode;
    node_t* dll_node;
    int pos;
    //remove itself to prevent errors
    graph_remove_edge(g, nodeValue, nodeValue);

    // remove from in-Neighbors
    dll_node = inNeighbors->head;
    pos = 0;
    while(dll_node != NULL){
        currentNode = dll_node->data;
        currentValue = currentNode->data;
        graph_remove_edge(g, currentValue, nodeValue);
        dll_node = inNeighbors->head;
    }

    // remove from out-Neighbors
    dll_node = outNeighbors->head;
    pos = 0;
    while(dll_node != NULL){
        currentNode = dll_node->data;
        currentValue = currentNode->data;
        graph_remove_edge(g, nodeValue, currentValue);
        dll_node = outNeighbors->head;
    }

     if(node->inNeighbors->count + node->outNeighbors->count == 0){
        return 1;
    }else{
        return 0;
    }
}

// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    // TODO: Implement me!
    // The function removes the node from the graph along with any edges associated with it.
    // That is, this node would have to be removed from all the in and out neighbor's lists that countain it.
    if(g == NULL) return -1;
    graph_node_t* target_n = find_node(g, value);
    if(target_n == NULL) return 0;

    // Temporal variables.
    graph_node_t* current_node;
    node_t* dll_node;
    int pos = 0;

    
    // remove all edges;
    graph_remove_edges_node(g, target_n);


    // remove node from graph->nodes DLL
    dll_node = g->nodes->head;
    while(dll_node != NULL){
        current_node = dll_node->data;
        if(current_node == target_n){
            dll_remove(g->nodes, pos);
        }
        pos++;
        dll_node = dll_node->next;
    }
    free_graph_node(target_n);

    g->numNodes--;
    return 1;
}



// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    // TODO: Implement me!
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriatelly. 
    // destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.

    if(g == NULL) return -1;

    graph_node_t* graph_node_s = find_node(g, source);
    graph_node_t* graph_node_d = find_node(g, destination);
   
    if( graph_node_s == NULL || graph_node_d == NULL || contains_edge(g, source, destination) == 1){
        return 0;
    }

    int result = 0;
    //Insert Source
    dll_t* out_source = graph_node_s->outNeighbors;
    result += dll_push_back(out_source, graph_node_d);
    //Insert destination
    dll_t* in_destination = graph_node_d->inNeighbors;
    result += dll_push_back(in_destination, graph_node_s);

    if(result == 2){
        g->numEdges++;
        return 1;
    }
    return 0;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source_int, int destination){
    graph_node_t* source = find_node(g, source_int);
    graph_node_t* target = find_node(g, destination);

    if(source == NULL || target == NULL){
        return 0;
    }
    //The function removes an edge from source to destination but not the other way.
    dll_t* inNeighbors = source->outNeighbors;
    dll_t* outNeighbors = target->inNeighbors;
    node_t* dll_node;
    graph_node_t* g_node;
    int result = 0;
    int pos;

    if(g == NULL) return -1;

    //Make sure you remove source from the in neighbors of destination.
    dll_node = inNeighbors->head;
    pos = 0;
    while(dll_node != NULL){
        g_node = dll_node->data;
        if(g_node == target){
            result += dll_remove(inNeighbors, pos);
            break;
        }
        pos++;
        dll_node = dll_node->next;
    }

    //Make sure you remove destination from the out neighbors of source.
    dll_node = outNeighbors->head;
    pos = 0;
    while(dll_node != NULL){
        g_node = dll_node->data;
        if(g_node == source){
            result += dll_remove(outNeighbors, pos);
            break;
        }
        pos++;
        dll_node = dll_node->next;
    }

    
    if(result > 0){
        g->numEdges--;
        return 1;
    }

    return 0;
}




// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destination){
    if ( g == NULL ) return -1;

    graph_node_t* source_graph = find_node(g, source);
    graph_node_t* destination_graph = find_node(g, destination);
    // safety check, both exist.
    if(source_graph == NULL || destination_graph == NULL) return 0;

    // source dll node
    node_t* dll_node_s = NULL;
    //Check source
    dll_node_s = source_graph->outNeighbors->head;
    while(dll_node_s != NULL){
        if(dll_node_s->data == destination_graph){
            break;
        }
        dll_node_s = dll_node_s->next;
    }


    // destination dll node
    node_t* dll_node_d = NULL;
    //check destination
    dll_node_d = destination_graph->inNeighbors->head;
    while(dll_node_d != NULL){
        if(dll_node_d->data == source_graph){
            break;
        }
        dll_node_d = dll_node_d->next;
    }

    //both were found:
    if(dll_node_d != NULL && dll_node_s != NULL){
        return 1;
    }
    // one or none were found
    return 0;
}

// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    if(g == NULL){
        return NULL;
    }
    graph_node_t* g_node = find_node(g, value);
    if(g_node != NULL){
        return g_node->inNeighbors;
    }
    return NULL;
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    if(g == NULL) return -1;
    dll_t* list = getInNeighbors(g, value);
    if(list != NULL) return list->count;
    return -1;
}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    if(g == NULL) return NULL;
    graph_node_t* g_node = find_node(g, value);
    if(g_node != NULL) return g_node->outNeighbors;
    return NULL;
}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    if(g == NULL) return -1;
    dll_t* list = getOutNeighbors(g, value);
    if(list != NULL) return list->count;
    return -1;
}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    if(g == NULL) return -1;
    return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    if(g == NULL) return -1;
    return g->numEdges;
}

//Returns 1 if reachable
//Returns 0 if not reachable.
//Returns -1 if the graph is NULL or if either of the nodes doesn't exist.
int is_reachable(graph_t * g, int source, int dest){
    //Implement using BFS.
    //Make sure you don't get stuck into an infinite loop.
    if(g == NULL) return -1;
    graph_node_t* source_node = find_node(g, source);
    graph_node_t* dest_node = find_node(g, dest);
    if(source_node == NULL || dest_node == NULL) return 0;
    if(source == dest) return 1;


    // main implementation
    markAllUnvisited(g);
    dll_t* queue = create_dll();
    
    dll_push_back(queue, source_node);
    int result;
    while(dll_empty(queue) == 0){
        result = visit_reachable(g, dll_pop_front(queue), dest_node, queue);
        if(result == 1){
            free_dll(queue);
            markAllUnvisited(g);
            return 1;
        }
    }

    free_dll(queue);
    markAllUnvisited(g);
    return 0;
}

// 1 is success
// 0 is fail
int visit_reachable(graph_t * g, graph_node_t* source, graph_node_t* target, dll_t* queue){
    if(target->data == source->data) return 1;
    source->visited = 1;

    node_t* node = source->outNeighbors->head;
    while(node != NULL){

        graph_node_t* g_node;
        g_node = node->data;

        if(g_node->visited == 0){
            dll_push_back(queue, g_node);
        }
        node = node->next;
    }
    return 0;
}

//Returns 1 if the graph has a cycle.
//Returns 0 if the graph doesn't have a cycle.
//Returns -1 if the graph is NULL or if either of the nodes doesn't exist.
int has_cycle(graph_t * g){
    if(g == NULL) return -1;

    node_t* node = g->nodes->head;
    while(node != NULL){
        graph_node_t* g_node;
        g_node = node->data;
        // check all the nodes one by one as source nodes.
        if(dfs_cycle(g_node) == 1){
            return 1;
        }
        markAllUnvisited(g);
        node = node->next;
    }

    return 0;
}

//Returns 1 if the graph has a cycle.
//Returns 0 if the graph doesn't have a cycle
int dfs_cycle(graph_node_t* node){
    if(node == NULL) return -1;

    
    int visited = node->visited;
    if(visited == 1){
        return 1;
    }else{
        node->visited = 1;
    }


    dll_t* edges = node->outNeighbors;
    node_t* neighbor;
    neighbor = edges->head;
    int result = 0;
    while(neighbor != NULL){
        graph_node_t* node_g;
        node_g = neighbor->data;
        int neighborVisited = node_g->visited;

        if(neighborVisited == 0){
            result = dfs_cycle(node_g);
        } else {
            return neighborVisited;
        }

        if(result != 0){
            return result;
        }

        neighbor = neighbor->next;
    }
    return 0;
}

//Marks all nodes to unvisited status
// 1 = success
// 0 = fail
int markAllUnvisited(graph_t * g){
    if(g == NULL) return -1;

    node_t* node = g->nodes->head;
    while(node != NULL){
        graph_node_t* g_node;
        g_node = node->data;
        g_node->visited = 0;
        node = node->next;
    }

    return 1;
}

//Prints all the nodes from source to destination ( including the source and destination),
//i.e. print_path(1,5) => 1 2 3 4 5


void print_path(graph_t * g, int source, int dest){
    if(g == NULL){
        printf("Path does not exist\n");
        return;
    }

    graph_node_t* source_node = find_node(g, source);
    graph_node_t* dest_node = find_node(g, dest);

    
    if(source_node == NULL || dest_node == NULL || is_reachable(g, source, dest) == 0){
        printf("Path does not exist\n");
        return;
    }
    if(source == dest){
        printf("%d %d", source, dest);
        return;
    }

    // create dll for our path.
    dll_t* path = create_dll();


    dll_t* neighbors = source_node->outNeighbors;
    node_t* currentNode = neighbors->head;
    graph_node_t* g_node;
    

    // This function picks the first path it finds, IT DOES NOT PICK THE SHORTEST PATH.
    source_node->visited = 1;
    int found = 0;
    while(currentNode != NULL){
        g_node = currentNode->data;
        found = path_visit(g, g_node, dest_node, path);
        if(found == 1){
            break;
        }
        currentNode = currentNode->next;
    }

    if(found != 1){
        printf("Error! ");
    }

    // push source and print.
    dll_push_front(path, source_node);
    print_path_dll(path);
    markAllUnvisited(g);
    // free dll
    free_dll(path);
}



// visit given node and adds nodes to the given dll if it finds a path.
int path_visit(graph_t * g, graph_node_t* source_node, graph_node_t* dest_node, dll_t* path){
    if(dest_node->data == source_node->data) {
        dest_node->visited = 1;
        dll_push_front(path, dest_node);
        return 1;
    }
    // mark as visited
    source_node->visited = 1;

    dll_t* neighbors = source_node->outNeighbors;
    node_t* currentNode = neighbors->head;
    graph_node_t* g_node;
    int found = 0;
    while(currentNode != NULL){
        g_node = currentNode->data;
        if(g_node->visited == 0){
            found = path_visit(g, g_node, dest_node, path);
        }
        if(found == 1){
            dll_push_front(path, source_node);
            return 1;
        }
        currentNode = currentNode->next;
    }

    //nothing was found
    return 0;
}

// prints a path using a dll.
print_path_dll(dll_t* path){
    node_t* node = path->head;
    graph_node_t* g_node;
    while(node != NULL){
     g_node = node->data;
     g_node = dll_pop_front(path);
     printf("%d ", g_node->data);
     node = path->head;
    }
    printf("\n");
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){
    if(g == NULL) return;
    node_t* node = g->nodes->head;
    // free all graph nodes
    while(node != NULL){
        free_graph_node(node->data);
        node = node->next;
    }
    //free internal graph_t dll
    free_dll(g->nodes);
    //free graph
    free(g);
}


// free a single graph node
void free_graph_node(graph_node_t* node){
    free_dll(node->inNeighbors);
    free_dll(node->outNeighbors);
    free(node);
}

#endif
