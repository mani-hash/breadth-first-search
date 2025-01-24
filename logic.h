#ifndef LOGIC_H
#define LOGIC_H

typedef struct TraversalStats {
    size_t nodesVisited;
    char *traversalPath;
    size_t totalWeight;
    char *unReachableNodes;
} TraversalStats;

TraversalStats bfsAlgorithm(Graph *graph);

#endif