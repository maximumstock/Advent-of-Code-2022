#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

namespace day11 {

    struct Monkey {
        vector<uint64_t> items;
        std::function<uint64_t(uint64_t)> op;
        std::function<uint64_t(uint64_t)> test;
    };

    uint64_t solve_part(int rounds, bool reduce_worry) {
        Monkey monkeys[8] = {
            Monkey {vector<uint64_t>({93, 98}), [](uint64_t worry) { return worry * 17; },
                    [](uint64_t worry) { return worry % 19 == 0 ? 5 : 3; }},
            Monkey {vector<uint64_t>({95, 72, 98, 82, 86}), [](uint64_t worry) { return worry + 5; },
                    [](uint64_t worry) { return worry % 13 == 0 ? 7 : 6; }},
            Monkey {vector<uint64_t>({85, 62, 82, 86, 70, 65, 83, 76}), [](uint64_t worry) { return worry + 8; },
                    [](uint64_t worry) { return worry % 5 == 0 ? 3 : 0; }},
            Monkey {vector<uint64_t>({86, 70, 71, 56}), [](uint64_t worry) { return worry + 1; },
                    [](uint64_t worry) { return worry % 7 == 0 ? 4 : 5; }},
            Monkey {vector<uint64_t>({77, 71, 86, 52, 81, 67}), [](uint64_t worry) { return worry + 4; },
                    [](uint64_t worry) { return worry % 17 == 0 ? 1 : 6; }},
            Monkey {vector<uint64_t>({89, 87, 60, 78, 54, 77, 98}), [](uint64_t worry) { return worry * 7; },
                    [](uint64_t worry) { return worry % 2 == 0 ? 1 : 4; }},
            Monkey {vector<uint64_t>({69, 65, 63}), [](uint64_t worry) { return worry + 6; },
                    [](uint64_t worry) { return worry % 3 == 0 ? 7 : 2; }},
            Monkey {vector<uint64_t>({89}), [](uint64_t worry) { return worry * worry; },
                    [](uint64_t worry) { return worry % 11 == 0 ? 0 : 2; }},
        };

        const uint64_t mod = 19 * 13 * 5 * 7 * 17 * 2 * 3 * 11;
        const int MONKEYS = 8;
        uint64_t inspections[MONKEYS] = {0};

        for (int round = 0; round < rounds; round++) {
            for (int i = 0; i < MONKEYS; i++) {
                Monkey &m = monkeys[i];
                for (auto item : m.items) {
                    uint64_t worry_level = m.op(item);
                    if (reduce_worry) {
                        worry_level /= 3;
                    }
                    uint64_t next_monkey = m.test(worry_level);
                    monkeys[next_monkey].items.push_back(worry_level % mod);
                    inspections[i]++;
                }
                m.items.clear();
            }
        }

        std::sort(std::rbegin(inspections), std::rend(inspections));
        return inspections[0] * inspections[1];
    }

    void solve() {
        assert(solve_part(20, true) == 78678);
        assert(solve_part(10000, false) == 15333249714);
    }

} // namespace day11