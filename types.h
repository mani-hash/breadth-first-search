#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef struct GraphNode {
    char nodeName;
    unsigned int weight;
    struct GraphNode *next;
} GraphNode;

typedef struct Graph {
    unsigned int noOfNodes;
    bool directed;
    char *nodeList;
    GraphNode **adjacentLists;
} Graph;

#endif