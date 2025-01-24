#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef struct GraphNode {
    char nodeName;
    int weight;
    struct GraphNode *next;
} GraphNode;

typedef struct Graph {
    size_t noOfNodes;
    bool directed;
    char *nodeList;
    GraphNode **adjacentLists;
} Graph;

#endif