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
static bool isVisited(char value);
static void trackTraversalPath(TraversalStats *traversalStats, char value);

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
    traversalStats->totalWeight = 0;
    traversalStats->traversalLength = 0;
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

static bool isVisited(char value)
{
    return visited[value - 'A'];
}

static void trackTraversalPath(TraversalStats *traversalStats, char value)
{
    if (traversalStats->traversalPath == NULL)
    {
        char *newTraversalPath = (char *)malloc(sizeof(char));

        if (newTraversalPath == NULL)
        {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }

        *newTraversalPath = value;
        traversalStats->traversalPath = newTraversalPath;
    }
    else
    {
        char *updatedTraversalPath = (char *)realloc
        (
            traversalStats->traversalPath, (traversalStats->traversalLength+1) * sizeof(char)
        );

        if (updatedTraversalPath == NULL)
        {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }

        updatedTraversalPath[traversalStats->traversalLength] = value;
        traversalStats->traversalPath = updatedTraversalPath;
    }
    traversalStats->traversalLength++;
}

TraversalStats bfsAlgorithm(Graph *graph)
{
    TraversalStats traversalStats;

    initTraversalStats(&traversalStats);

    initQueue(graph->noOfNodes);
    initVisitedArray(graph->noOfNodes);

    // size_t loopCounter = 0;
    char startNodeName = graph->nodeList[0];
    enqueue(startNodeName);

    while (front <= rear)
    {
        char visitedNodeName = dequeue();

        if (!isVisited(visitedNodeName))
        {
            visited[visitedNodeName - 'A'] = true;
            trackTraversalPath(&traversalStats, visitedNodeName);
        }

        GraphNode *currentNode = graph->adjacentLists[visitedNodeName - 'A'];

        while (currentNode != NULL)
        {
            if (!isVisited(currentNode->nodeName))
            {
                enqueue(currentNode->nodeName);
                traversalStats.totalWeight += currentNode->weight;
                visited[currentNode->nodeName - 'A'] = true;
                trackTraversalPath(&traversalStats, currentNode->nodeName);
            }

            currentNode = currentNode->next;
        }
    }

    free(queue);
    free(visited);

    return traversalStats;
}