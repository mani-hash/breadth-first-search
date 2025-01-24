#ifndef LOGIC_H
#define LOGIC_H

typedef struct TraversalStats {
    char *traversalPath;
    size_t traversalLength;
    size_t totalWeight;
    char *unReachableNodes;
    size_t unReachableLength;
} TraversalStats;

TraversalStats bfsAlgorithm(Graph *graph);

#endif