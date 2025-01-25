#ifndef LOGIC_H
#define LOGIC_H

typedef struct TraversalStats {
    char *traversalPath;
    unsigned int traversalLength;
    unsigned int totalWeight;
    char *unReachableNodes;
    unsigned int unReachableLength;
} TraversalStats;

TraversalStats bfsAlgorithm(Graph *graph);

#endif