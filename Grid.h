#pragma once
#include <vector>

class Grid {
private:
    std::vector<std::vector<int>> grid;
    int n;

public:
    Grid(int size);
    void generateGrid(int size);
    void generateObstacle(int m);
    bool isObstacle(int x, int y) const;
    int length() const;
};
