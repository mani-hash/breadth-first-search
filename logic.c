#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"
#include "logic.h"

static void initQueue(size_t noOfNodes);
static void initVisitedArray(size_t noOfNodes);

char *queue;
bool *visited;

static void initQueue(size_t noOfNodes)
{
    queue = (char *)malloc(noOfNodes * sizeof(char));
}

static void initVisitedArray(size_t noOfNodes)
{
    visited = (bool *)malloc(noOfNodes * sizeof(char));
    for (size_t index = 0; index < noOfNodes; index++)
    {
        visited[index] = false;
    }
}

void bfsAlgorithm(Graph *graph)
{
    initQueue(graph->noOfNodes);
    initVisitedArray(graph->noOfNodes);

    
}