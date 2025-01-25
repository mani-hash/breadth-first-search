#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "decipherFile.h"
#include "logic.h"

int main()
{
    Graph *graph = createGraphFromFile();

    displayDataFromTraversingGraph(graph);
    
    freeGraph(graph);
    
    return 0;
}