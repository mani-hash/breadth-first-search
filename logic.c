#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"
#include "logic.h"

static void initQueue(unsigned int noOfNodes);
static void initVisitedArray(unsigned int noOfNodes);
static void initTraversalStats(TraversalStats *traversalStats);
static void enqueue(char value);
static char dequeue();
static bool isVisited(char value);
static void trackTraversalPath(TraversalStats *traversalStats, char value);
static void getUnreachableNodes(TraversalStats *traversalStats, unsigned int noOfNodes);
static TraversalStats bfsAlgorithm(Graph *graph);
static void freeTraversalStats(TraversalStats *traversalStats);
static void printTraversalPath(char *traversalPath, unsigned int traversalLength);
static void printTotalWeight(unsigned int totalWeight);
static void printUnReachableNodes(char *unReachableNodes, unsigned int unReachableLength);

char *queue;
bool *visited;

int front = -1, rear = -1;

static void initQueue(unsigned int noOfNodes)
{
    queue = (char *)malloc(noOfNodes * sizeof(char));
}

static void initVisitedArray(unsigned int noOfNodes)
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
    traversalStats->unReachableLength = 0;
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
        exit(EXIT_FAILURE);
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

static void getUnreachableNodes(TraversalStats *traversalStats, unsigned int noOfNodes)
{
    char *unreachableNodes = NULL;
    
    for (size_t index = 0; index < noOfNodes; index++)
    {
        if (!visited[index])
        {
            if (unreachableNodes == NULL)
            {
                unreachableNodes = (char *)malloc(sizeof(char));
                *unreachableNodes = (char)(index + 'A');
            }
            else
            {
                unreachableNodes = (char *)realloc
                (
                    unreachableNodes,
                    (traversalStats->unReachableLength + 1) * sizeof(char)
                );

                unreachableNodes[traversalStats->unReachableLength] = (char)(index + 'A');
            }


            traversalStats->unReachableLength++;
        }
    }

    traversalStats->unReachableNodes = unreachableNodes;
}

static TraversalStats bfsAlgorithm(Graph *graph)
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

    getUnreachableNodes(&traversalStats, graph->noOfNodes);

    free(queue);
    free(visited);

    return traversalStats;
}

static void printTraversalPath(char *traversalPath, unsigned int traversalLength)
{
    printf("BFS Traversal Path: ");
    for (size_t index = 0; index < traversalLength; index++)
    {
        printf("%c", traversalPath[index]);
        if (index + 1 != traversalLength)
        {
            printf(" -> ");
        }
    }
    printf("\n");
}

static void printTotalWeight(unsigned int totalWeight)
{
    printf("Total weight: %u\n", totalWeight);
}

static void printUnReachableNodes(char *unReachableNodes, unsigned int unReachableLength)
{
    printf("Unreachable Nodes: ");
    for (size_t index = 0; index < unReachableLength; index++)
    {
        printf("%c", unReachableNodes[index]);
        if (index + 1 != unReachableLength)
        {
            printf(", ");
        }
    }
    printf("\n");
}

static void freeTraversalStats(TraversalStats *traversalStats)
{
    free(traversalStats->traversalPath);
    free(traversalStats->unReachableNodes);
}

void displayDataFromTraversingGraph(Graph *graph)
{
    TraversalStats traversalStats = bfsAlgorithm(graph);

    printTraversalPath(traversalStats.traversalPath, traversalStats.traversalLength);
    printTotalWeight(traversalStats.totalWeight);
    printUnReachableNodes(traversalStats.unReachableNodes, traversalStats.unReachableLength);

    freeTraversalStats(&traversalStats);
}