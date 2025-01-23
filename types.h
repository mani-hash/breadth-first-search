#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef struct {
    char nodeName;
    int weight;
    GraphNode *next;
} GraphNode;

typedef struct {
    int noOfNodes;
    bool directed;
    GraphNode **adjacentLists;
} Graph;

#endif