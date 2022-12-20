#ifndef AOC_H
#define AOC_H

#include <sstream>
#include <vector>
using namespace std;

namespace aoc {
    vector<string> split_string(string input, char delim) {
        vector<string> out;
        string s;
        istringstream iss(input);
        while (getline(iss, s, delim)) {
            out.push_back(s);
        }
        return out;
    }

    vector<string> split_string2(string input, string delim) {
        vector<string> out;
        string s;
        int i = 0;
        while (i < input.length()) {
            if (input.substr(i).starts_with(delim)) {
                out.push_back(input.substr(0, i));
                input = input.substr(i + delim.length());
                i = 0;
            } else {
                i++;
            }
        }
        if (!input.empty()) {
            out.push_back(input);
        }
        return out;
    }
} // namespace aoc

#endif