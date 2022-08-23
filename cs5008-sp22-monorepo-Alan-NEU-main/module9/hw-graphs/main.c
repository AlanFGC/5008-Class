// Compile this assignment with: gcc -Wall main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"


// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.
int testRemoveNode() {
    graph_t * graph = create_graph();
    graph_add_node(graph, 0);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_node(graph, 3);
    graph_add_node(graph, 4);
    graph_add_node(graph, 6);
    graph_add_node(graph, 7);
    graph_add_node(graph, 8);
    graph_add_node(graph, 9);
    // edges 
    graph_add_edge(graph, 0, 2);
    graph_add_edge(graph, 0, 3);
    graph_add_edge(graph, 3, 4);
    graph_add_edge(graph, 4, 6);

    graph_add_edge(graph, 6, 7);
    graph_add_edge(graph, 7, 8);
    graph_add_edge(graph, 8, 9);
    graph_add_edge(graph, 8, 6);

    graph_remove_node(graph, 8);
    
    int result;
    int result2;
    result = getNumOutNeighbors(graph, 9);
    result2 = getNumInNeighbors(graph, 6);

    free_graph(graph);
    if( result == 0 && result2 == 1){
        return 1;
    }
    printf("IN  %d", result2);
    printf("out  %d\n", result);
    return 0;
}

int testRemoveEdge(){
    graph_t * graph = create_graph();
    graph_add_node(graph, 0);
    graph_add_node(graph, 1);
    // edges
    graph_add_edge(graph, 0, 1);
    graph_add_edge(graph, 1, 0);
    graph_remove_edge(graph, 0, 1);

    int result;
    int result2;
    result = getNumOutNeighbors(graph, 0);
    result2 = getNumInNeighbors(graph, 1);

    free_graph(graph);
    if( result == 0 && result2 == 0){
        return 1;
    }
    printf("IN 1 %d", result2);
    printf("out 0 %d\n", result);
    return 0;
}

int testReachable(){
    graph_t * graph = create_graph();
    graph_add_node(graph, 0);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_node(graph, 3);
    graph_add_node(graph, 4);
    graph_add_node(graph, 6);
    graph_add_node(graph, 7);
    graph_add_node(graph, 8);
    graph_add_node(graph, 9);
    // edges 
    graph_add_edge(graph, 0, 2);
    graph_add_edge(graph, 0, 3);
    graph_add_edge(graph, 3, 4);
    graph_add_edge(graph, 4, 6);

    graph_add_edge(graph, 6, 7);
    graph_add_edge(graph, 7, 8);
    graph_add_edge(graph, 8, 9);
    graph_add_edge(graph, 8, 6);
    int result = is_reachable(graph, 0, 9);
    // print_path(graph, 0, 9);
    free_graph(graph);
    if( result == 1){
        return 1;
    }
    return 0;
}


int testReachable2(){
    graph_t * graph = create_graph();
    graph_add_node(graph, 0);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_node(graph, 3);
    graph_add_node(graph, 4);

    graph_add_node(graph, 6);
    graph_add_node(graph, 7);
    graph_add_node(graph, 8);
    graph_add_node(graph, 9);
    // edges 
    graph_add_edge(graph, 0, 2);
    graph_add_edge(graph, 0, 3);
    graph_add_edge(graph, 3, 4);
    graph_add_edge(graph, 4, 6);

    graph_add_edge(graph, 6, 7);
    graph_add_edge(graph, 8, 9);
    graph_add_edge(graph, 8, 6);
    int result = is_reachable(graph, 0, 9);
    free_graph(graph);

    if( result == 0){
        return 1;
    }
    return 0;
}


int testHasCycle(){
    graph_t * graph = create_graph();
    graph_add_node(graph, 0);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_node(graph, 3);
    graph_add_node(graph, 4);

    graph_add_node(graph, 6);
    graph_add_node(graph, 7);
    graph_add_node(graph, 8);
    graph_add_node(graph, 9);
    // edges 
    graph_add_edge(graph, 0, 2);
    graph_add_edge(graph, 0, 3);
    graph_add_edge(graph, 3, 4);
    graph_add_edge(graph, 4, 6);

    graph_add_edge(graph, 6, 7);
    graph_add_edge(graph, 8, 9);
    graph_add_edge(graph, 9, 0);
    int result1 = has_cycle(graph);
    graph_add_edge(graph, 7, 8);
    int result2 = has_cycle(graph);
    free_graph(graph);
    if( result1 == 0 && result2 == 1){
        return 1;
    }
    return 0;
}

int testNumNodes(){
    graph_t * graph = create_graph();
    graph_add_node(graph, 0);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_node(graph, 3);
    graph_add_node(graph, 4);

    int result = graph_num_nodes(graph);

    graph_add_node(graph, 6);
    graph_add_node(graph, 7);
    graph_add_node(graph, 8);
    graph_add_node(graph, 9);

    int result2 = graph_num_nodes(graph);
    

    free_graph(graph);
    if( result == 5 && result2 == 9){
        return 1;
    }
    return 0;
}


int testPrintPath1(){
    graph_t * graph = create_graph();
    graph_add_node(graph, 0);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_node(graph, 3);
    graph_add_node(graph, 4);

    graph_add_node(graph, 6);
    graph_add_node(graph, 7);
    graph_add_node(graph, 8);
    graph_add_node(graph, 9);
    graph_add_node(graph, 527);

    graph_add_edge(graph, 0, 1);
    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 1, 0);
    graph_add_edge(graph, 2, 7);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 3, 4);
    graph_add_edge(graph, 4, 8);
    graph_add_edge(graph, 4, 527);
    graph_add_edge(graph, 527, 9);


    print_path(graph, 0, 9);
    free_graph(graph);
    return 1;
}

int testPrintPath2(){
    graph_t * graph = create_graph();
    graph_add_node(graph, 0);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_node(graph, 3);
    graph_add_node(graph, 4);

    graph_add_node(graph, 6);
    graph_add_node(graph, 7);
    graph_add_node(graph, 8);
    graph_add_node(graph, 9);
    graph_add_node(graph, 527);

    graph_add_edge(graph, 0, 1);
    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 1, 0);
    graph_add_edge(graph, 2, 7);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 3, 4);
    graph_add_edge(graph, 4, 8);
    graph_add_edge(graph, 4, 527);
    graph_add_edge(graph, 527, 9);
    graph_add_edge(graph, 8, 4);
    graph_add_edge(graph, 2, 6);
    graph_add_edge(graph, 4, 3);
    graph_add_edge(graph, 3, 2);

    print_path(graph, 8, 6);
    free_graph(graph);
    return 1;
}


int testNoPath(){
    graph_t * graph = create_graph();
    graph_add_node(graph, 0);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_node(graph, 3);
    graph_add_node(graph, 4);

    graph_add_node(graph, 6);
    graph_add_node(graph, 7);
    graph_add_node(graph, 8);
    graph_add_node(graph, 9);
    graph_add_node(graph, 527);

    graph_add_edge(graph, 0, 1);
    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 1, 0);
    graph_add_edge(graph, 2, 7);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 3, 4);
    graph_add_edge(graph, 4, 8);
    graph_add_edge(graph, 4, 527);
    graph_add_edge(graph, 527, 9);
    graph_add_edge(graph, 8, 4);
    graph_add_edge(graph, 2, 6);
    graph_add_edge(graph, 3, 2);

    print_path(graph, 8, 6);
    free_graph(graph);
    return 1;
}

int main(int argc, const char * argv[]) {
  
    printf("==================  TESTS: (1 is passed, 0 is failed) \n");
    printf("test 1: %d\n", testRemoveEdge());
    printf("test 2: %d\n", testRemoveNode());
    printf("test 3: %d\n", testReachable());
    printf("test 4: %d\n", testReachable2());
    printf("test 5: %d\n", testHasCycle());
    printf("test 6: %d\n", testNumNodes());
    printf("test 7 (print path manual inspection):\n\t");
    testPrintPath1();
    printf("test 8 (print path manual inspection):\n\t");
    testPrintPath2();
    printf("test 9 (impossible PATH):\n\t");
    testNoPath();
    
    return 0;
}
