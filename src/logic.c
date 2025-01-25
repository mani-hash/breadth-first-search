#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"
#include "logic.h"

/*
 * @brief declarations for internal functions
 *
 * List of static functions local to this file
 * Meant to be used in this file only
 * 
 * @note all internal functions are static
 */
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

/*
 * @brief Queue data structure (array)
 *
 * Keeps track of nodes that needs to be 
 * visited when traversing the graph
 * 
 * @note This variable has global scope
 * 
 */
char *queue;

/*
 * @brief Visited data structure (array)
 *
 * Keeps track of nodes that have been
 * visited when traversing the graph by
 * setting the relavant index to true/false
 * 
 * @note This variable has global scope
 * 
 */
bool *visited;

/*
 * @brief Front and Rear pointers for Queue
 *
 * Track the front and rear of the queue
 * 
 * @note These variables have global scope
 * @note Value -1 indicates empty queue
 * @warning front > rear results in queue being full
 * 
 */
int front = -1, rear = -1;

/*
 * @brief Initializes Queue Data Structure
 * 
 * @param unsigned int (number of nodes)
 * @return void
 * 
 */
static void initQueue(unsigned int noOfNodes)
{
    queue = (char *)malloc(noOfNodes * sizeof(char));

    if (queue == NULL)
    {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
}

/*
 * @brief Initializes Visited Data Structure
 * 
 * @param unsigned int (number of nodes)
 * @return void
 * 
 */
static void initVisitedArray(unsigned int noOfNodes)
{
    visited = (bool *)malloc(noOfNodes * sizeof(char));

    if (visited == NULL)
    {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    for (size_t index = 0; index < noOfNodes; index++)
    {
        visited[index] = false;
    }
}

/*
 * @brief Initializes TraversalStats struct
 * 
 * @param TraversalStats (pointer*)
 * @return void
 * 
 */
static void initTraversalStats(TraversalStats *traversalStats)
{
    traversalStats->totalWeight = 0;
    traversalStats->traversalLength = 0;
    traversalStats->unReachableLength = 0;
    traversalStats->traversalPath = NULL;
    traversalStats->unReachableNodes = NULL;
}

/*
 * @brief Enqueue function
 * 
 * Adds a value to the rear of
 * the queue array
 * 
 * @param char (value)
 * @return void
 * 
 */
static void enqueue(char value)
{
    if (front == -1)
    {
        front = 0;
    }
    rear++;

    queue[rear] = value;

}

/*
 * @brief Dequeue function
 * 
 * Removes a value from the front of
 * the queue array and returns it
 * 
 * @param char (value)
 * @return char 
 * 
 */
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

/*
 * @brief Check if a node is visited
 * 
 * @param char (value)
 * @return bool
 * 
 */
static bool isVisited(char value)
{
    return visited[value - 'A'];
}

/*
 * @brief Track path of bfs traversal
 * 
 * Keeps track of nodes that are visited
 * during bfs and adds these node names to
 * a dynamic char array
 * 
 * @param TraversalStats (pointer*)
 * @param char (value)
 * @return void
 * 
 */
static void trackTraversalPath(TraversalStats *traversalStats, char value)
{
    if (traversalStats->traversalPath == NULL)
    {
        char *newTraversalPath = (char *)malloc(sizeof(char));

        if (newTraversalPath == NULL)
        {
            perror("Failed to allocate memory\n");
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
    traversalStats->traversalLength++; // increment count of nodes traversed
}

/*
 * @brief Get unreachable node names
 * 
 * Get the names of nodes that are
 * unreachable and adds these to a
 * dynamic char array
 * 
 * @param TraversalStats (pointer*)
 * @param unsigned int (number of nodes)
 * @return void
 * 
 */
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

                if (unreachableNodes == NULL)
                {
                    perror("Failed to allocate memory\n");
                    exit(EXIT_FAILURE);
                }

                *unreachableNodes = (char)(index + 'A');
            }
            else
            {
                unreachableNodes = (char *)realloc
                (
                    unreachableNodes,
                    (traversalStats->unReachableLength + 1) * sizeof(char)
                );

                if (unreachableNodes == NULL)
                {
                    perror("Failed to allocate memory\n");
                    exit(EXIT_FAILURE);
                }

                unreachableNodes[traversalStats->unReachableLength] = (char)(index + 'A');
            }


            traversalStats->unReachableLength++;
        }
    }

    traversalStats->unReachableNodes = unreachableNodes; // attach dynamic array to struct
}

/*
 * @brief Breadth First Search Algorithm
 * 
 * Contains logic of bfs algorithm
 * Traverses the graph and keeps track of
 * relavant data
 * 
 * @param Graph (pointer*)
 * @return TraversalStats
 * 
 */
static TraversalStats bfsAlgorithm(Graph *graph)
{
    TraversalStats traversalStats;

    initTraversalStats(&traversalStats);

    initQueue(graph->noOfNodes);
    initVisitedArray(graph->noOfNodes);

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

    // free dynamically allocated structures
    free(queue);
    free(visited);

    return traversalStats;
}

/*
 * @brief Display traversal path
 * 
 * Displays traversal path in the below format
 * Node Name 1 -> Node Name 2
 * 
 * @param char pointer [array]
 * @param unsigned int (traversed path count)
 * @return void
 * 
 */
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

    if (traversalLength == 0)
    {
        printf("None");
    }

    printf("\n");
}

/*
 * @brief Display total weight
 * 
 * @param unsigned int (weight)
 * @return void
 * 
 */
static void printTotalWeight(unsigned int totalWeight)
{
    printf("Total weight: %u\n", totalWeight);
}

/*
 * @brief Display unreachable nodes
 * 
 * Displays unreachabble nodes in the below format
 * Node Name 1, Node Name 2
 * 
 * @param char pointer [array]
 * @param unsigned int (unreachable nodes count)
 * @return void
 * 
 */
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

    if (unReachableLength == 0)
    {
        printf("None");
    }

    printf("\n");
}

/*
 * @brief Free dynamically allocated structures
 * 
 * Frees dynamically allocated structures
 * that were not immediately freed upon creation
 * 
 * @param TraversalStats (pointer*)
 * @return void
 * 
 */
static void freeTraversalStats(TraversalStats *traversalStats)
{
    free(traversalStats->traversalPath);
    free(traversalStats->unReachableNodes);
}

/*
 * @brief Run and display all data from traversing graph
 * 
 * @param Graph (pointer*)
 * @return void
 * 
 * @note Runs the bfs algorithm and formulates data
 * @note Also frees dynamically allocated structures
 * 
 */
void displayDataFromTraversingGraph(Graph *graph)
{
    TraversalStats traversalStats = bfsAlgorithm(graph);

    printTraversalPath(traversalStats.traversalPath, traversalStats.traversalLength);
    printTotalWeight(traversalStats.totalWeight);
    printUnReachableNodes(traversalStats.unReachableNodes, traversalStats.unReachableLength);

    freeTraversalStats(&traversalStats);
}