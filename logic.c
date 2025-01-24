#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"
#include "logic.h"

static void initQueue(size_t noOfNodes);
static void initVisitedArray(size_t noOfNodes);
static void initTraversalStats(TraversalStats *traversalStats);
static void enqueue(char value);
static char dequeue();

char *queue;
bool *visited;

int front = -1, rear = -1;

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

static void initTraversalStats(TraversalStats *traversalStats)
{
    traversalStats->nodesVisited = 0;
    traversalStats->totalWeight = 0;
    traversalStats->traversalPath = NULL;
    traversalStats->unReachableNodes = NULL;
}

static void enqueue(char value)
{
    if (front == -1)
    {
        front = 0;
    }
    rear++;

    queue[rear] = value;

}

static char dequeue()
{
    if (front == -1 || front > rear)
    {
        perror("Queue is empty");
        exit(1);
    }

    char removedValue = queue[front];
    front++;

    return removedValue;
}

TraversalStats bfsAlgorithm(Graph *graph)
{
    TraversalStats traversalStats;

    initTraversalStats(&traversalStats);

    initQueue(graph->noOfNodes);
    initVisitedArray(graph->noOfNodes);

    return traversalStats;
}