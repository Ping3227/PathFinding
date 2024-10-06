#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <numeric>
#include "Grid.h"
#include "PathFinding.h"

struct TestResult {
    double dpAvgValidPaths;
    double dpAvgOptimalPaths;
    double recAvgValidPaths;
    double recAvgOptimalPaths;
    int n;
    double p;
};

TestResult runTests(int n, int m, int k) {
    std::vector<long long> dpValidPaths, dpOptimalPaths, recValidPaths, recOptimalPaths;

    for (int i = 0; i < k; ++i) {
        Grid grid(n);
        grid.generateObstacle(m);
        PathFinding pathFinding(grid);
        // auto start  = std::chrono::high_resolution_clock::now();
        Result dpResult = pathFinding.DP();
        // auto end1  = std::chrono::high_resolution_clock::now();
        Result recResult = pathFinding.recursive();
        // auto end2  = std::chrono::high_resolution_clock::now();
        // std::cout<< "DP: " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start).count() << " ms\n";
        // std::cout<< "Rec: " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - end1).count() << " ms\n";
        if (dpResult.validPaths > 0) {
            dpValidPaths.push_back(dpResult.validPaths);
            dpOptimalPaths.push_back(dpResult.optimalPaths);
        }
        if (recResult.validPaths > 0) {
            recValidPaths.push_back(recResult.validPaths);
            recOptimalPaths.push_back(recResult.optimalPaths);
        }

    }

    auto avg = [](const std::vector<long long>& v) {
        return v.empty() ? 0.0 : std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    };

    return {
        avg(dpValidPaths),
        avg(dpOptimalPaths),
        avg(recValidPaths),
        avg(recOptimalPaths),
        n,
        static_cast<double>(m) / (n * n)
    };
}

void saveResultsToCSV(const std::vector<TestResult>& results, const std::string& filename) {
    std::ofstream file(filename);
    file << std::fixed << std::setprecision(6);
    file << "n,p,DPAvgValidPaths,DPAvgOptimalPaths,RecAvgValidPaths,RecAvgOptimalPaths\n";

    for (const auto& result : results) {
        file << result.n << "," << result.p << ","
             << result.dpAvgValidPaths << "," << result.dpAvgOptimalPaths << ","
             << result.recAvgValidPaths << "," << result.recAvgOptimalPaths << "\n";
    }

    file.close();
}

int main() {
    int n_start, n_end, k;
    std::cout << "Enter start n, end n, and k: ";
    std::cin >> n_start >> n_end >> k;

    std::vector<TestResult> results;

    for (int n = n_start; n <= n_end; ++n) {
        for (int m = 0; m <= n*n; ++m) {
            results.push_back(runTests(n, m, k));
        }
        std::cout << "Completed n = " << n << "/" << n_end << "\n";
    }

    std::string filename = "results_n" + std::to_string(n_start) + "_" + std::to_string(n_end) + "_k" + std::to_string(k) + ".csv";
    saveResultsToCSV(results, filename);

    std::cout << "Results have been saved to '" << filename << "'.\n";
    std::cout << "You can now use the Python script to create plots using this CSV file.\n";

    return 0;
}