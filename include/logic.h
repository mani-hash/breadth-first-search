#ifndef LOGIC_H
#define LOGIC_H

/*
 * @brief Traversal statistics data structure
 *
 * TraversalStats struct is used to store
 * the data recieved from traversing the
 * graph
 * 
 * @member char pointer [array] (traversal path) => stores name of nodes in traversal order
 * @member unsigned int (traversal length) => stores the number of nodes traversed
 * @member char pointer [array] (unreachable nodes) => stores the name of nodes that cannot be reached
 * @member unsigned int (unreachable nodes length) => stores number of nodes that cannot be reached
 * 
 */
typedef struct TraversalStats {
    char *traversalPath;
    unsigned int traversalLength;
    char *unReachableNodes;
    unsigned int unReachableLength;
} TraversalStats;

void displayDataFromTraversingGraph(Graph *graph);

#endif