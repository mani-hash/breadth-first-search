#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

Graph *createGraphFromFile()
{
    int noOfNodes = 0;
    bool directed = false;

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
            noOfNodes = getNoOfNodes();
        }
        else if (lineNumber == 2)
        {
            
        }
        else if (lineNumber == 3)
        {

        }
        else
        {

        }

        lineNumber++;
        
    }
}