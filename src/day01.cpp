#include "aoc.cpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

namespace day01 {
    void solve() {
        ifstream infile("inputs/day01.txt");
        vector<int> caloriesPerElf;

        int totalCalories = 0;
        for (string line; getline(infile, line);) {
            if (line.empty()) {
                caloriesPerElf.push_back(totalCalories);
                totalCalories = 0;
                continue;
            }
            totalCalories += stoi(line);
        }

        nth_element(caloriesPerElf.rbegin(), caloriesPerElf.rend() + 2, caloriesPerElf.rend());

        assert(caloriesPerElf[0] == 69693);
        assert(accumulate(caloriesPerElf.begin(), caloriesPerElf.begin() + 3, 0) == 200945);
    }
} // namespace day01