#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "decipherFile.h"
#include "types.h"

/*
 * @brief declarations for internal functions
 *
 * List of static functions local to this file
 * Meant to be used in this file only
 * 
 * @note all internal functions are static
 */
static unsigned int getNoOfNodes();
static char *getNodeList();
static bool isGraphDirected();
static void createNewNode
(
    GraphNode **adjacencyList,
    char startingVectorName,
    char endingVectorName,
    unsigned int weight
);
static void constructAdjacencyList(GraphNode **adjacencyList, bool isDirected);

/*
 * @brief FILE pointer
 *
 * File structure used to read from the
 * target file
 * 
 * @note This variable has global scope
 */
FILE *file;

/*
 * @brief constant string file name 
 *
 * Relative file path of graph data file
 * 
 * @note This constant has global scope
 */
const char fileName[] = "data/graph.txt";

/*
 * @brief line buffer
 *
 * Line buffer to read a line from
 * the file
 * 
 * @note This variable has global scope
 */
char line[256];

/*
 * @brief Extract number of nodes from line
 * 
 * @return unsigned int (number of nodes)
 * 
 */
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

/*
 * @brief Extract node names from line
 * 
 * Retrieve the names of nodes to a
 * dynamic array and return its pointer
 * 
 * @return char array (pointer*)
 * 
 */
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

/*
 * @brief Check if graph is directed or not from line
 * 
 * Check if graph is either directed or undirected
 * from the file and return true if directed and false
 * if not
 * 
 * @return bool
 * 
 */
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

    directionName[index] = '\0'; // add null termination for strings

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

    free(directionName); // free dynamically allocated array

    return isDirected;
}

/*
 * @brief Create a node in adjacency list
 * 
 * Creates a node in adjacency list as per the data
 * from the graph file
 * 
 * @param GraphNode [2D array] (pointer to pointer*)
 * @param char (starting vector name)
 * @param char (ending vector name)
 * @param unsigned int (weight)
 * @return void
 * 
 */
static void createNewNode
(
    GraphNode **adjacencyList,
    char startingVectorName,
    char endingVectorName,
    unsigned int weight
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

/*
 * @brief Construct adjacency list
 * 
 * Creates the full adjacency list from
 * the data in graph file
 * 
 * @param GraphNode [2D array] (pointer to pointer*)
 * @param bool (directed or undirected)
 * @return void
 * 
 */
static void constructAdjacencyList(GraphNode **adjacencyList, bool isDirected)
{
    char startingVectorName, endingVectorName;
    unsigned int weight;

    if (sscanf(line, " %c %c %u", &startingVectorName, &endingVectorName, &weight))
    {
        createNewNode(adjacencyList, startingVectorName, endingVectorName, weight);

        // add a bidirectional edge if undirected
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

/*
 * @brief Create graph structure from file
 * 
 * Creates the complete graph structure
 * and return its pointer
 * 
 * @return Graph (pointer)
 * 
 */
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

    // reads line by line from graph data file
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

/*
 * @brief Free dynamically created graph structs
 * 
 * Frees the dynamically created structs that were
 * not immediately freed upon creation
 * 
 * @param Graph (pointer*)
 * @return void
 * 
 */
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