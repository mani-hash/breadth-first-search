#ifndef DECIPHER_FILE_H
#define DECIPHER_FILE_H

#include <stdbool.h>
#include "types.h"

int getNoOfNodes();
char *getNodeList();
bool isGraphDirected();
void constructAdjacencyList(GraphNode **adjacencyList);

Graph *createGraphFromFile();

#endif