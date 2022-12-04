#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <optional>
#include "aoc.cpp"

using namespace std;

namespace day03
{
    optional<char> findSharedChar(string &rucksack)
    {
        set<char> leftHalf, rightHalf;
        size_t i = 0;
        size_t k = rucksack.length() / 2;

        for (; i < rucksack.length() / 2; i++, k++)
        {
            leftHalf.insert(rucksack.at(i));
            rightHalf.insert(rucksack.at(k));
        }

        for (auto c : leftHalf)
        {
            if (rightHalf.contains(c))
            {
                return c;
            }
        }

        return nullopt;
    }

    vector<char> findSharedCharsPerGroup(vector<string> lines, int groupSize)
    {
        vector<char> sharedCharsPerGroup;
        for (auto it = lines.begin(); it != lines.end(); it++)
        {
            map<char, int> groupCounts;
            vector<string> group;

            for (int i = 0; i < groupSize; i++)
            {
                group.push_back(*it++);
            };
            it--;

            for (auto &rucksack : group)
            {
                map<char, int> rucksackCounts;
                for (auto &item : rucksack)
                {
                    if (!rucksackCounts.contains(item))
                    {
                        rucksackCounts[item] = 1;
                        if (groupCounts.contains(item))
                        {
                            groupCounts[item] = groupCounts[item] + 1;
                        }
                        else
                        {
                            groupCounts[item] = 1;
                        }
                    }
                }
            }

            for (auto pair : groupCounts)
            {
                if (pair.second == 3)
                {
                    char c = pair.first;
                    sharedCharsPerGroup.push_back(c);
                }
            }
        }
        return sharedCharsPerGroup;
    }

    void solve()
    {
        ifstream infile("inputs/day03.txt");
        vector<string> lines;
        for (string line; getline(infile, line);)
        {
            lines.push_back(line);
        }

        int prioritySumP1 = 0;
        for (auto &line : lines)
        {
            optional<char> c = findSharedChar(line);
            if (c.has_value())
            {
                char value = c.value();
                int priority = (value - (value < 97 ? 64 - 26 : 96));
                prioritySumP1 += priority;
            }
        }
        assert(prioritySumP1 == 7903);

        int prioritySumP2 = 0;
        vector<char> sharedCharPerGroup = findSharedCharsPerGroup(lines, 3);
        for (auto c : sharedCharPerGroup)
        {
            int priority = (c - (c < 97 ? 64 - 26 : 96));
            prioritySumP2 += priority;
        }
        assert(prioritySumP2 == 2548);
    }

}