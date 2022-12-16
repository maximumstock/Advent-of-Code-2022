#include <fstream>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

namespace day10 {

    void draw_pixel(char crt[240], int reg_x, int pixel) {
        char c = (pixel % 40 - 1 <= reg_x && reg_x <= pixel % 40 + 1) ? '#' : ' ';
        crt[pixel] = c;
    }

    void solve() {
        ifstream infile("inputs/day10.txt");
        int x = 1;
        int cycle = 0;
        int signal_strength = 0;
        queue<int> adds;
        static char crt[240];

        for (string line; getline(infile, line);) {
            while (1) {
                cycle++;
                if (cycle % 20 == 0 && (cycle / 20) % 2 == 1 && cycle <= 220) {
                    signal_strength += x * cycle;
                }
                draw_pixel(crt, x, cycle - 1);
                if (!adds.empty()) {
                    x += adds.front();
                    adds.pop();
                    break;
                } else if (line.starts_with("addx")) {
                    int value = stoi(line.substr(5));
                    adds.push(value);
                } else if (line.starts_with("noop")) {
                    break;
                }
            }
        }

        assert(signal_strength == 12880);

        // should print out FCJAPJRE
        // for (int i = 0; i < 240; i++)
        // {
        //     if (i % 40 == 0)
        //     {
        //         cout << endl;
        //     }
        //     cout << crt[i];
        // }
    }

} // namespace day10