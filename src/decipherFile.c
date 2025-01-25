#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "decipherFile.h"
#include "types.h"

// declaration of static functions
static unsigned int getNoOfNodes();
static char *getNodeList();
static bool isGraphDirected();
static void createNewNode
(
    GraphNode **adjacencyList,
    char startingVectorName,
    char endingVectorName,
    int weight
);
static void constructAdjacencyList(GraphNode **adjacencyList, bool isDirected);

FILE *file;
const char fileName[] = "data/graph.txt"; 
char line[256];


static unsigned int getNoOfNodes()
{
    unsigned int number;
    if (!sscanf(line, "%u", &number))
    {
        perror("Error in getting number\n");
        exit(EXIT_FAILURE);
    }

    return number;
}

static char *getNodeList()
{
    unsigned int fullLength = 0;
    unsigned int filledLength = 0;
    while (line[fullLength] != '\n')
    {
        if (!isspace(line[fullLength]))
        {
            filledLength++;
        }
        fullLength++;
    }

    char *nodeList = (char*)malloc(filledLength * sizeof(char));
    if (nodeList == NULL)
    {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    for (size_t index = 0, nodeIndex = 0; index < fullLength; index++)
    {
        if (!isspace(line[index]))
        {
            nodeList[nodeIndex++] = line[index];
        }
    }

    return nodeList;
}

static bool isGraphDirected()
{
    bool isDirected = false;

    size_t length = 0;
    while (line[length] != '\n' && line[length] != '\0')
    {
        length++;
    }

    char *directionName = (char*)malloc((length+1) * sizeof(char));
    if (directionName == NULL)
    {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    size_t index;
    for (index = 0; index < length; index++)
    {
        directionName[index] = line[index];
    }

    directionName[index] = '\0';

    if (strcmp(directionName, "directed") == 0)
    {
        isDirected = true;
    }
    else if (strcmp(directionName, "undirected") == 0)
    {
        isDirected = false;
    }
    else
    {
        perror("Incorrect graph type specified!\n");
        exit(EXIT_FAILURE);
    }

    free(directionName);

    return isDirected;
}

static void createNewNode
(
    GraphNode **adjacencyList,
    char startingVectorName,
    char endingVectorName,
    int weight
)
{
    GraphNode *currentGraphNode = adjacencyList[startingVectorName - 'A'];
    GraphNode *lastGraphNode = NULL;

    while (currentGraphNode != NULL)
    {
        lastGraphNode = currentGraphNode;
        currentGraphNode = currentGraphNode->next;
    }

    GraphNode *newGraphNode = (GraphNode*)malloc(sizeof(GraphNode));

    if (newGraphNode == NULL)
    {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    newGraphNode->nodeName = endingVectorName;
    newGraphNode->weight = weight;
    newGraphNode->next = NULL;

    if (lastGraphNode != NULL)
    {
        lastGraphNode->next = newGraphNode;
    }
    else
    {
        adjacencyList[startingVectorName - 'A'] = newGraphNode;
    }
}

static void constructAdjacencyList(GraphNode **adjacencyList, bool isDirected)
{
    char startingVectorName, endingVectorName;
    int weight;

    if (sscanf(line, " %c %c %d", &startingVectorName, &endingVectorName, &weight))
    {
        createNewNode(adjacencyList, startingVectorName, endingVectorName, weight);

        if (!isDirected)
        {
            createNewNode(adjacencyList, endingVectorName, startingVectorName, weight);
        }
    }
    else {
        perror("Error reading file\n");
        exit(EXIT_FAILURE);
    }
}

Graph *createGraphFromFile()
{
    Graph *graph = (Graph*)malloc(sizeof(Graph));

    if (graph == NULL)
    {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(fileName, "r");
    if (file == NULL)
    {
        perror("Error in file\n");
        exit(EXIT_FAILURE);
    }

    int lineNumber = 1;

    while (fgets(line, sizeof(line), file))
    {
        if (lineNumber == 1)
        {
            graph->noOfNodes = getNoOfNodes();
            graph->adjacentLists = (GraphNode**)malloc(graph->noOfNodes * sizeof(GraphNode));

            if (graph->adjacentLists == NULL)
            {
                perror("Failed to allocate memory\n");
                exit(EXIT_FAILURE);
            }

            // initialize adjacency list
            for (size_t index = 0; index < graph->noOfNodes; index++)
            {
                graph->adjacentLists[index] = NULL;
            }
        }
        else if (lineNumber == 2)
        {
            graph->nodeList = getNodeList();

            for (size_t index = 0; index < graph->noOfNodes; index++)
            {
                graph->adjacentLists[index] = NULL;
            }
        }
        else if (lineNumber == 3)
        {
            graph->directed = isGraphDirected();
        }
        else
        {
            constructAdjacencyList(graph->adjacentLists, graph->directed);
        }

        lineNumber++;
        
    }

    return graph;
}

void freeGraph(Graph *graph)
{
    // free individual linked lists
    for (size_t index = 0; index < graph->noOfNodes; index++)
    {
        GraphNode *current = graph->adjacentLists[index];
        while (current != NULL)
        {
            GraphNode *temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(graph->adjacentLists);

    free(graph->nodeList);

    free(graph);
}