#include "aoc.cpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace day14 {
    void solve() {
        ifstream infile("inputs/day14.txt");

        char grid[600][120] {};
        grid[500][0] = '+';

        for (string line; getline(infile, line);) {
            vector<string> coords = aoc::split_string2(line, " -> ");
            for (int i = 0; i < coords.size() - 1; i++) {
                auto start = aoc::split_string(coords[i], ',');
                auto end = aoc::split_string(coords[i + 1], ',');
                auto start_x = stoi(start[0]);
                auto start_y = stoi(start[1]);
                auto end_x = stoi(end[0]);
                auto end_y = stoi(end[1]);

                auto x_min = min(start_x, end_x);
                auto x_max = max(start_x, end_x);
                auto y_min = min(start_y, end_y);
                auto y_max = max(start_y, end_y);

                for (int col = x_min; col <= x_max; col++) {
                    for (int row = y_min; row <= y_max; row++) {
                        grid[col][row] = '#';
                    }
                }
            }
        }
    }

} // namespace day14