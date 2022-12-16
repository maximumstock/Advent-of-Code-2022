#include "aoc.cpp"
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

namespace day03 {
    char findSharedChar(string &rucksack) {
        set<char> leftHalf = set(rucksack.cbegin(), rucksack.cend() - (rucksack.length() / 2));
        return *std::find_if(rucksack.cbegin() + (rucksack.length() / 2), rucksack.cend(), [&leftHalf](auto c) { return leftHalf.contains(c); });
    }

    vector<char> findSharedCharsPerGroup(vector<string> lines, int groupSize) {
        vector<char> sharedCharsPerGroup;
        for (auto it = lines.begin(); it != lines.end(); it++) {
            vector<string> group;

            for (int i = 0; i < groupSize; i++) {
                group.push_back(*it++);
            };
            it--;

            string intersection = group[0];
            sort(intersection.begin(), intersection.end());
            for (auto &rucksack : group) {
                sort(rucksack.begin(), rucksack.end());
                string tmp;
                set_intersection(rucksack.begin(), rucksack.end(),
                                 intersection.begin(), intersection.end(),
                                 inserter(tmp, tmp.begin()));
                intersection = tmp;
            }
            sharedCharsPerGroup.push_back(intersection[0]);
        }
        return sharedCharsPerGroup;
    }

    void solve() {
        ifstream infile("inputs/day03.txt");
        vector<string> lines;
        for (string line; getline(infile, line);) {
            lines.push_back(line);
        }

        int prioritySumP1 = accumulate(lines.begin(), lines.end(), 0, [](int acc, string line) { 
            char value = findSharedChar(line);
            return acc +  (value - (value < 97 ? 64 - 26 : 96)); });
        assert(prioritySumP1 == 7903);

        int prioritySumP2 = 0;
        vector<char> sharedCharPerGroup = findSharedCharsPerGroup(lines, 3);
        for (auto c : sharedCharPerGroup) {
            int priority = (c - (c < 97 ? 64 - 26 : 96));
            prioritySumP2 += priority;
        }
        assert(prioritySumP2 == 2548);
    }

} // namespace day03