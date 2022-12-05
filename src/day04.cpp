#include <iostream>
#include <fstream>
#include <array>
#include "aoc.cpp"

using namespace std;

namespace day04
{
    void solve()
    {
        ifstream infile("inputs/day04.txt");
        vector<array<int, 4>> lines;
        for (string line; getline(infile, line);)
        {
            auto p = line.find("-");
            auto p2 = line.find(",");
            auto p3 = line.find_last_of("-");
            int a = stoi(line.substr(0, p));
            int b = stoi(line.substr(p + 1, p2));
            int c = stoi(line.substr(p2 + 1, p3));
            int d = stoi(line.substr(p3 + 1, line.length()));
            lines.push_back(std::array<int, 4> {a, b, c, d});
        }

        auto p1Count = std::count_if(lines.begin(), lines.end(), [](auto input)
                                    { return (input[0] <= input[2] && input[1] >= input[3]) || (input[2] <= input[0] && input[3] >= input[1]); });

        auto p2Count = std::count_if(lines.begin(), lines.end(), [](auto input)
                                    { return (input[0] <= input[2] && input[2] <= input[1]) || (input[0] <= input[3] && input[3] <= input[1]) || (input[2] <= input[0] && input[0] <= input[3]) || (input[2] <= input[1] && input[1] <= input[3]); });

        assert(p1Count == 494);
        assert(p2Count == 833);
    }

}