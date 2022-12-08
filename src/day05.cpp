#include <iostream>
#include <fstream>
#include <array>
#include <stack>
#include <sstream>
#include "aoc.cpp"

using namespace std;

namespace day05
{
    string crane(vector<array<uint32_t, 3>> instructions, vector<stack<char>> stacks, bool keepOrder)
    {
        for (auto i : instructions)
        {
            size_t steps = i[0];
            size_t from = max(i[1] - 1, (uint32_t)0);
            size_t to = max(i[2] - 1, (uint32_t)0);

            // For some reason I wasn't able to minimize these two branches by juggling references
            // to the respective source/target stacks per path - might have to take a look at it again.
            if (keepOrder)
            {
                stack<char> tmp;
                for (size_t step = 0; step < steps; step++)
                {
                    tmp.push(stacks[from].top());
                    stacks[from].pop();
                }
                for (size_t step = 0; step < steps; step++)
                {
                    stacks[to].push(tmp.top());
                    tmp.pop();
                }
            }
            else
            {
                for (size_t step = 0; step < steps; step++)
                {
                    stacks[to].push(stacks[from].top());
                    stacks[from].pop();
                }
            }
        }

        string output;
        for (auto s : stacks)
        {
            output += s.top();
        }

        return output;
    }

    void solve()
    {
        ifstream infile("inputs/day05.txt");
        vector<tuple<char, int>> items;
        vector<array<uint32_t, 3>> instructions;
        vector<stack<char>> stacks;

        for (int i = 0; i < 9; i++)
        {
            stacks.push_back(stack<char>{});
        }

        for (string line; getline(infile, line);)
        {
            if (line.empty())
            {
                break;
            }
            for (uint32_t i = 0; i < 9; i++)
            {
                auto item = line.at(1 + i * 4);
                if (item == '1')
                {
                    break;
                }
                int stack = i % 9;
                items.push_back(make_tuple(item, stack));
            }
        }
        reverse(items.begin(), items.end());

        for (auto pair : items)
        {
            char c = get<0>(pair);
            int stack = get<1>(pair);
            if (c != ' ')
            {
                stacks[(size_t)stack].push(c);
            }
        }

        for (string line; getline(infile, line);)
        {
            auto tokens = aoc::split_string(line, ' ');
            instructions.push_back(array<uint32_t, 3>{(uint32_t)stoi(tokens.at(1)), (uint32_t)stoi(tokens.at(3)), (uint32_t)stoi(tokens.at(5))});
        }

        auto instructions2 = instructions;
        auto stacks2 = stacks;
        assert(crane(instructions, stacks, false) == "ZBDRNPMVH");
        assert(crane(instructions2, stacks2, true) == "WDLPFNNNB");
    }

}