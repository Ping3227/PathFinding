#include "Grid.h"
#include <random>
#include <algorithm>
#include <iostream>

Grid::Grid(int size) : n(size) {
    generateGrid(size);
}

void Grid::generateGrid(int size) {
    n = size;
    grid.resize(n, std::vector<int>(n, 0));
}

void Grid::generateObstacle(int m) {
    std::vector<std::pair<int, int>> positions;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            positions.emplace_back(i, j);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);
    // std::cout << "Obstacles:\n";
    for (int i = 0; i < m && i < positions.size(); ++i) {
        int x = positions[i].first;
        int y = positions[i].second;
        grid[x][y] = 1;
        // std::cout << "Obstacle at (" << x << ", " << y << ")\n";
    }
}

bool Grid::isObstacle(int x, int y) const {
    if (x < 0 || x >= n || y < 0 || y >= n) return true;
    return grid[x][y] == 1;
}

int Grid::length() const {
    return n;
}