#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "decipherFile.h"
#include "types.h"

FILE *file;
const char fileName[] = "graph.txt"; 
char line[256];
int lineNumber = 1;


int getNoOfNodes()
{
    int number;
    if (!sscanf(line, "%d", &number))
    {
        printf("Error in getting number");
        exit(0);
    }

    return number;
}

char *getNodeList()
{
    size_t fullLength = 0;
    size_t filledLength = 0;
    while (line[fullLength] != '\n')
    {
        if (isspace(line[fullLength]))
        {
            filledLength++;
        }
        fullLength++;
    }

    char *nodeList = (char*)malloc(filledLength * sizeof(char));
    if (nodeList == NULL)
    {
        perror("Failed to allocate memory");
        exit(1);
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

bool isGraphDirected()
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
        perror("Failed to allocate memory");
        exit(1);
    }

    size_t index;
    for (index = 0; index < length; index++)
    {
        directionName[index] = line[index];
    }

    directionName[index+1] = '\0';

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
        perror("Incorrect graph type specified!");
        exit(1);
    }

    return isDirected;
}

void constructAdjacencyList(GraphNode **adjacencyList)
{
    char startingVectorName, endingVectorName;
    int weight;

    if (sscanf(line, " %c %c %d", &startingVectorName, &endingVectorName, &weight))
    {
        printf("%c %c %d\n", startingVectorName, endingVectorName, weight);
        GraphNode *currentGraphNode = adjacencyList[startingVectorName - 'A'];

        if (currentGraphNode == NULL)
        {
            perror("There was an error accessing initialized graph");
            exit(1);
        }

        while (currentGraphNode->next != NULL)
        {
            currentGraphNode = currentGraphNode->next;
        }

        GraphNode *newGraphNode = (GraphNode*)malloc(sizeof(GraphNode));

        newGraphNode->nodeName = endingVectorName;
        newGraphNode->weight = weight;
        newGraphNode->next = NULL;

        currentGraphNode->next = newGraphNode;
    }
    else {
        printf("errr\n");
    }
}

Graph *createGraphFromFile()
{
    Graph *graph = (Graph*)malloc(sizeof(Graph));

    file = fopen(fileName, "r");
    if (file == NULL)
    {
        perror("Error in file");
        exit(1);
    }

    while (fgets(line, sizeof(line), file))
    {
        if (lineNumber == 1)
        {
            graph->noOfNodes = getNoOfNodes();
            graph->adjacentLists = (GraphNode**)malloc(graph->noOfNodes * sizeof(GraphNode));

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
                GraphNode *graphNode = (GraphNode*)malloc(sizeof(GraphNode));
                graphNode->nodeName = graph->nodeList[index];
                graphNode->weight = 0;
                graphNode->next = NULL;
                graph->adjacentLists[index] = graphNode;
            }
        }
        else if (lineNumber == 3)
        {
            graph->directed = isGraphDirected();
        }
        else
        {
            constructAdjacencyList(graph->adjacentLists);
        }

        lineNumber++;
        
    }

    return graph;
}