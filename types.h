#ifndef TYPES_H
#define TYPES_H

typedef struct {
    char nodeName;
    int weight;
    GraphNode *next;
} GraphNode;

#endif