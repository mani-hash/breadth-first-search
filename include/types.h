#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

/*
 * @brief Graph Node data structure
 *
 * GraphNode struct is used when building the
 * adjacency list. It keeps track of nearby vertex
 * from a particular node
 * 
 * @member char (name of node) => stores name of a node
 * @member unsigned int (weight) => stores the weight of a edge
 * @member GraphNode (next pointer*) =>  stores pointer to next vertex
 *
 */
typedef struct GraphNode {
    char nodeName;
    unsigned int weight;
    struct GraphNode *next;
} GraphNode;

/*
 * @brief Graph data structure
 *
 * Graph structure is used to keep track of
 * overall structure and additional notes 
 * of the deciphered graph 
 * 
 * @member unsigned int (number of nodes) => Total number of nodes in the graph
 * @member unsigned int (total weight) => total weight of graph
 * @member bool (directed) => Stores whether a graph is directed or undirected
 * @member GraphNode [2d array] (pointer to pointer*) =>  stores the adjacency list
 *
 */
typedef struct Graph {
    unsigned int noOfNodes;
    unsigned int totalWeight;
    bool directed;
    char *nodeList;
    GraphNode **adjacentLists;
} Graph;

#endif