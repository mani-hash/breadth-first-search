#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
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

Graph *createGraphFromFile()
{
    Graph *graph = (Graph*)malloc(sizeof(Graph));

    file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error in file");
        exit(0);
    }

    while (fgets(line, sizeof(line), file))
    {
        if (lineNumber == 1)
        {
            graph->noOfNodes = getNoOfNodes();
        }
        else if (lineNumber == 2)
        {
            graph->nodeList = getNodeList();
        }
        else if (lineNumber == 3)
        {

        }
        else
        {

        }

        lineNumber++;
        
    }

    return graph;
}