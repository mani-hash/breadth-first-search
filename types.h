#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef struct GraphNode {
    char nodeName;
    int weight;
    struct GraphNode *next;
} GraphNode;

typedef struct Graph {
    int noOfNodes;
    bool directed;
    GraphNode **adjacentLists;
} Graph;

#endif