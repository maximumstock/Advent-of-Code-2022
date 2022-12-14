#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

namespace day09
{

    tuple<int, int> find_move(char dir)
    {
        switch (dir)
        {
        case 'R':
            return make_tuple(1, 0);
        case 'L':
            return make_tuple(-1, 0);
        case 'U':
            return make_tuple(0, 1);
        case 'D':
            return make_tuple(0, -1);
        default:
            throw new exception();
        }
    }

    void solve()
    {
        ifstream infile("inputs/day09.txt");
        static int positions[9][2]; // static to initialize with zeros
        set<tuple<int, int>> visited_knot_1 = {make_tuple(0, 0)};
        set<tuple<int, int>> visited_knot_9 = {make_tuple(0, 0)};

        for (string line; getline(infile, line);)
        {
            char dir = line.at(0);
            int stride = stoi(line.substr(2));
            tuple<int, int> _move = find_move(dir);

            for (int i = 0; i < stride; i++)
            {
                for (int knot = 0; knot < 10; knot++)
                {
                    if (knot == 0)
                    {
                        // move head
                        positions[knot][0] += std::get<0>(_move);
                        positions[knot][1] += std::get<1>(_move);
                        continue;
                    }

                    // adjust tails
                    if (abs(positions[knot][0] - positions[knot - 1][0]) == 2 || abs(positions[knot][1] - positions[knot - 1][1]) == 2)
                    {
                        int dx = positions[knot - 1][0] - positions[knot][0];
                        int dy = positions[knot - 1][1] - positions[knot][1];

                        // find unit vectors
                        dx = dx == 0 ? dx : dx / abs(dx);
                        dy = dy == 0 ? dy : dy / abs(dy);
                        positions[knot][0] += dx;
                        positions[knot][1] += dy;

                        if (knot == 1)
                        {
                            visited_knot_1.insert(make_tuple(positions[knot][0], positions[knot][1]));
                        }
                        if (knot == 9)
                        {
                            visited_knot_9.insert(make_tuple(positions[knot][0], positions[knot][1]));
                        }
                    }
                }
            }
        }

        assert(visited_knot_1.size() == 6498);
        assert(visited_knot_9.size() == 2531);
    }

}