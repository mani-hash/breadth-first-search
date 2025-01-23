#ifndef DECIPHER_FILE_H
#define DECIPHER_FILE_H

#include <stdbool.h>
#include "types.h"

int getNoOfNodes();
char *getNodeList();
bool isGraphDirected();

Graph *createGraphFromFile();

#endif