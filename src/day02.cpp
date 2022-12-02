#include <iostream>
#include <fstream>
#include "aoc.cpp"

using namespace std;

namespace day02
{
    const int CHOICES = 3;

    int score(char them, char me)
    {
        char t = them - 64;
        char m = me - 64;
        if (t % CHOICES + 1 == m) { return 6; }
        if ((t + 2) % CHOICES == m % CHOICES) { return 0; }
        // if (them == 'A' && me == 'B') { return 6; } // 1, 2 -> 6
        // if (them == 'B' && me == 'C') { return 6; } // 2, 3 -> 6
        // if (them == 'C' && me == 'A') { return 6; } // 3, 1 -> 6
        // if (them == 'A' && me == 'C') { return 0; } // 1, 3 -> 0
        // if (them == 'B' && me == 'A') { return 0; } // 2, 1 -> 0
        // if (them == 'C' && me == 'B') { return 0; } // 3, 2 -> 0
        return 3;
    }

    char find_move(char outcome, char them)
    {
        if (outcome == 'X') {
            return (them == 65 ? 65 + CHOICES - 1 : them - 1);
            // if (them == 'A') { return 'C'; } // 1 -> 3
            // if (them == 'B') { return 'A'; } // 2 -> 1
            // if (them == 'C') { return 'B'; } // 3 -> 2
        }
        if (outcome == 'Z') {
            return (them - 64) % CHOICES + 65;
            // if (them == 'A') { return 'B'; } // 1 -> 2
            // if (them == 'B') { return 'C'; } // 2 -> 3
            // if (them == 'C') { return 'A'; } // 3 -> 1
        }
        return them;
    }

    void solve()
    {
        ifstream infile("inputs/day02.txt");

        int totalScoreP1 = 0;
        int totalScoreP2 = 0;
        
        for (string line; getline(infile, line);)
        {
            char them = line.at(0);
            char me = line.at(2);

            char meP1 = me - 23;
            totalScoreP1 += ((meP1 - 64) + score(them, meP1));

            char meP2 = find_move(me, them);
            totalScoreP2 += ((meP2 - 64) + score(them, meP2));
        }

        assert(totalScoreP1 == 15572);
        assert(totalScoreP2 == 16098);
    }

}