#include "PathFinding.h"
#include <algorithm>
#include <iostream>
#include <limits>

PathFinding::PathFinding(Grid& g) : grid(g) {}

// Recursive solution
void PathFinding::recursiveHelper(int x, int y, int turns, bool fromLeft) {
    if (grid.isObstacle(x, y)) return;
    if (x == grid.length() - 1 && y == grid.length() - 1) {
        recursiveResult.validPaths++;
        if (turns < recursiveResult.leastTurns) {
            recursiveResult.leastTurns = turns;
            recursiveResult.optimalPaths = 1;
        } else if (turns == recursiveResult.leastTurns) {
            recursiveResult.optimalPaths++;
        }
        return;
    }


    // go right
    if (x < grid.length() - 1) {
        recursiveHelper(x + 1, y, turns + (!fromLeft ? 1 : 0), true);
    }
    // go down
    if (y < grid.length() - 1) {
        recursiveHelper(x, y + 1, turns + (fromLeft ? 1 : 0), false );
    }
}

Result PathFinding::recursive() {
    recursiveResult = {0, 0, std::numeric_limits<int>::max()};
    if(!grid.isObstacle(0, 0)) {
        // go down
        recursiveHelper(0, 1, 0, false);
        // go right
        recursiveHelper(1, 0, 0, true);
    }
    return recursiveResult;
}

//Dynamic Programming solution
Result PathFinding::DP() {
    int n = grid.length();
    std::vector<std::vector<std::vector<long long>>> dp(n, std::vector<std::vector<long long>>(n, std::vector<long long>(5, 0)));
    // dp[x][y][0]: valid paths
    // dp[x][y][1]: optimal paths from left
    // dp[x][y][2]: turns from left
    // dp[x][y][3]: optimal paths from up
    // dp[x][y][4]: turns from up

    // set turn to max value first
    for (int x= 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            dp[x][y][4] = dp[x][y][2]= std::numeric_limits<int>::max();

        }

    }

    dp[0][0][0] = 1;
    dp[0][0][1] = 1;
    dp[0][0][2] = 0;
    dp[0][0][3] = 1;
    dp[0][0][4] = 0;

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            // ignore the starting point
            if (x == 0 && y == 0) continue;
            if (grid.isObstacle(x, y)) continue;
            // from left
            if (x > 0 && !grid.isObstacle(x-1, y)) {
                // add valid path
                dp[x][y][0] += dp[x-1][y][0];

                // calculate optimal paths and turns

                // compare path from left or from up(for last point)
                if (dp[x-1][y][2] < dp[x-1][y][4]+1) {
                    dp[x][y][1] = dp[x-1][y][1];
                    dp[x][y][2] = dp[x-1][y][2];
                }
                if(dp[x-1][y][2] == dp[x-1][y][4]+1){
                    dp[x][y][1] = dp[x-1][y][1]+dp[x-1][y][3];
                    dp[x][y][2] = dp[x-1][y][2];
                }
                if (dp[x-1][y][2] > dp[x-1][y][4]+1) {
                    dp[x][y][1] = dp[x-1][y][3];
                    dp[x][y][2] = dp[x-1][y][4]+1;
                }
            }
            // from up
            if (y > 0 && !grid.isObstacle(x, y-1)) {
                // add valid path
                dp[x][y][0] += dp[x][y-1][0];

                // calculate optimal paths and turns

                // compare path from left or from up(for last point)
                if (dp[x][y-1][2]+1 > dp[x][y-1][4]) {
                    dp[x][y][3] = dp[x][y-1][3];
                    dp[x][y][4] = dp[x][y-1][4];
                }
                if(dp[x][y-1][2]+1 == dp[x][y-1][4]){
                    dp[x][y][3] = dp[x][y-1][3]+dp[x][y-1][1];
                    dp[x][y][4] = dp[x][y-1][4];
                }
                if (dp[x][y-1][2]+1 < dp[x][y-1][4]) {
                    dp[x][y][3] = dp[x][y-1][1];
                    dp[x][y][4] = dp[x][y-1][2]+1;
                }

            }
            // std::cout<< "x: "<<x<< "y: "<< y<<"optimal : " <<dp[x][y][1]<< dp[x][y][3]<<"turns: "<<dp[x][y][2]<<" , " <<dp[x][y][4]<<std::endl;
        }
    }
    if (dp[n-1][n-1][2] < dp[n-1][n-1][4]) {
       return Result{dp[n-1][n-1][0], dp[n-1][n-1][1], dp[n-1][n-1][2]};
    }
    else if(dp[n-1][n-1][2] == dp[n-1][n-1][4]){
        return Result{dp[n-1][n-1][0], dp[n-1][n-1][1]+dp[n-1][n-1][3], dp[n-1][n-1][2]};
    }
    else{
        return Result{dp[n-1][n-1][0], dp[n-1][n-1][3], dp[n-1][n-1][4]};
    }
}