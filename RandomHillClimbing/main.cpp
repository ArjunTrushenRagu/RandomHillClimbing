#include <iostream>
#include <vector>
#include <random>
#include <tuple>

using namespace std;

// Function f(x, y)
double f(double x, double y) {
    return pow(1.5 + x + x*y, 2) + pow(2.25 + x - x*y*y, 2) + pow(2.625 + x - x*y*y*y, 2);
}

// Generates a random number between min and max
double generateRandom(double min, double max, mt19937 &gen) {
    uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

// Generates a list of neighboring points around a given point (x, y)
vector<pair<double, double>> generateNeighbors(double x, double y, int p, double z, mt19937 &gen) {
    vector<pair<double, double>> neighbors;
    for(int i = 0; i < p; i++) {
        double dx = generateRandom(-z, z, gen);
        double dy = generateRandom(-z, z, gen);
        neighbors.push_back({x + dx, y + dy});
    }
    return neighbors;
}

// Randomized Hill Climbing Function
tuple<pair<double, double>, double, int> RHC(pair<double, double> sp, int p, double z, int seed) {
    mt19937 gen(seed);
    double x = sp.first;
    double y = sp.second;
    int num_solutions_generated = 0;

    while (true) {
        auto neighbors = generateNeighbors(x, y, p, z, gen);
        num_solutions_generated += neighbors.size();

        double best_value = f(x, y);
        pair<double, double> best_neighbor = {x, y};

        for (const auto& neighbor : neighbors) {
            if (neighbor.first >= -4.2 && neighbor.first <= 4.2 && neighbor.second >= -4.2 && neighbor.second <= 4.2) {
                double neighbor_value = f(neighbor.first, neighbor.second);
                if (neighbor_value > best_value) {
                    best_value = neighbor_value;
                    best_neighbor = neighbor;
                }
            }
        }

        if (best_value <= f(x, y)) {
            break;
        }

        x = best_neighbor.first;
        y = best_neighbor.second;
    }

    return {{x, y}, f(x, y), num_solutions_generated};
}

int main() {
    vector<pair<double, double>> starting_points = {{2,2}, {1, 4}, {-2,-3}, {1,-2}};
    vector<int> p_values = {65, 400};
    vector<double> z_values = {0.2, 0.01};
    vector<int> seeds = {42, 43};

    for (const auto& sp : starting_points) {
        for (int p : p_values) {
            for (double z : z_values) {
                for (int seed : seeds) {
                    auto [best_solution, best_value, num_solutions_generated] = RHC(sp, p, z, seed);
                    cout << "Starting Point: (" << sp.first << ", " << sp.second << "), p: " << p << ", z: " << z << ", seed: " << seed << "\n";
                    cout << "Best solution: (" << best_solution.first << ", " << best_solution.second << ")\n";
                    cout << "Best value: " << best_value << "\n";
                    cout << "Number of solutions generated: " << num_solutions_generated << "\n\n";
                }
            }
        }
    }

    return 0;
}

