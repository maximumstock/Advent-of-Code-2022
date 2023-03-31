#include <fstream>
#include <iostream>
#include <set>

using namespace std;

namespace day06 {

    uint32_t find_marker(string &input, uint8_t width) {
        set<char> uniques;
        for (uint32_t pos = 0; pos < input.length() - width; pos++) {
            std::for_each(input.begin() + pos, input.begin() + pos + width, [&](auto c) { uniques.insert(c); });
            if (uniques.size() == width) {
                return pos + width;
            }
            uniques.clear();
        }
        return 0;
    }

    void solve() {
        ifstream infile("inputs/day06.txt");
        string input;
        getline(infile, input);
        assert(find_marker(input, 4) == 1987);
        assert(find_marker(input, 14) == 3059);
    }

} // namespace day06
