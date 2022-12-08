#ifndef AOC_H
#define AOC_H

#include <vector>
using namespace std;

namespace aoc
{
    vector<string> split_string(string input, char delim)
    {
        vector<string> out;
        string s;
        istringstream iss(input);
        while (getline(iss, s, delim))
        {
            out.push_back(s);
        }
        return out;
    }

}

#endif