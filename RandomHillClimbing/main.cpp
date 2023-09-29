//
//  main.cpp
//  RandomHillClimbing
//
//  Created by Arjun Trushen Ragu on 9/28/23.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <tuple>

using namespace std;

// Function f(x, y)
double f(double x, double y) {
    return pow(1.5 + x + x*y, 2) + pow(2.25 + x - x*y*y, 2) + pow(2.625 + x - x*y*y*y, 2);
}

// Generates a list of neighboring points around a given point (x, y)
vector<pair<double, double>> generateNeighbors(double x, double y, int p, double z) {
    vector<pair<double, double>> neighbors;
    for(int i = 0; i < p; i++)
    {
        double dx = (rand() / (double)RAND_MAX * 2 - 1) * z;
        double dy = (rand() / (double)RAND_MAX * 2 - 1) * z;
        neighbors.push_back({x + dx, y + dy});
    }
    return neighbors;
}
// Randomized Hill Climbing Function
tuple<pair<double, double>, double, int> RHC(pair<double, double> sp, int p, double z, int seed) {
    srand(seed);
    // start with a given starting point 'sp' which is a pair (x, y)
    double x = sp.first;
    double y = sp.second;
    // Amount of neighbors generated
    int solutionsGenerated = 0;
    
    // Loop is repeated 'p' times
    for(int i = 0; i < p; i++)
    {
        // Generate 'p' neighbors around the current point (x, y) using the 'generateNeighbors' function
        auto neighbors = generateNeighbors(x, y, p, z);
        solutionsGenerated += neighbors.size();
        
        // Calculate the function value for the current point and all its neighbors then select highest value to move to making that the new current point and continue the search from there for the next iteration
        double currentValue = f(x, y);
        double maxValue = currentValue;
        pair<double, double> bestNeighbor = {x, y};
        
        for(const auto& neighbor : neighbors) {
            double neighborValue = f(neighbor.first, neighbor.second);
            if(neighborValue > maxValue) {
                maxValue = neighborValue;
                bestNeighbor = neighbor;
            }
        }
        // update current position
        x = bestNeighbor.first;
        y = bestNeighbor.second;
    }
    return {{x, y}, f(x, y), solutionsGenerated};
}
int main() {
    // Example run
    auto [bestSolution, bestValue, totalSolutions] = RHC({-2, -3}, 65, 0.2, 43);
    std::cout << "Best solution: (" << bestSolution.first << ", " << bestSolution.second << ")\n";
    std::cout << "Best value: " << bestValue << "\n";
    std::cout << "Total solutions generated: " << totalSolutions << "\n";

    return 0;
}
