#pragma once

#include "Grid.h"


struct Result {
    long long validPaths;
    long long optimalPaths;
    int leastTurns;
};

class PathFinding {
private:
    Grid& grid;
    Result recursiveResult;
    Result dpResult;

    void recursiveHelper(int x, int y, int turns, bool fromLeft);

public:
    PathFinding(Grid& g);
    Result recursive();
    Result DP();
};
