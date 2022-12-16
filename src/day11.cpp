#include <algorithm>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

namespace day11 {

    struct Monkey {
        queue<long long> items;
        std::function<long long(long long)> op;
        std::function<long long(long long)> test;
    };

    void solve() {
        Monkey monkeys[8] = {
            Monkey {queue<long long>({93, 98}), [](long long worry) { return worry * 17; }, [](long long worry) { return worry % 19 == 0 ? 5 : 3; }},
            Monkey {queue<long long>({95, 72, 98, 82, 86}), [](long long worry) { return worry + 4; }, [](long long worry) { return worry % 13 == 0 ? 7 : 6; }},
            Monkey {queue<long long>({85, 62, 82, 86, 70, 65, 83, 76}), [](long long worry) { return worry + 8; }, [](long long worry) { return worry % 5 == 0 ? 3 : 0; }},
            Monkey {queue<long long>({86, 70, 71, 56}), [](long long worry) { return worry + 1; }, [](long long worry) { return worry % 7 == 0 ? 4 : 5; }},
            Monkey {queue<long long>({77, 71, 86, 52, 81, 67}), [](long long worry) { return worry + 4; }, [](long long worry) { return worry % 17 == 0 ? 1 : 6; }},
            Monkey {queue<long long>({89, 87, 60, 78, 54, 77, 98}), [](long long worry) { return worry * 7; }, [](long long worry) { return worry % 2 == 0 ? 1 : 4; }},
            Monkey {queue<long long>({69, 65, 63}), [](long long worry) { return worry + 6; }, [](long long worry) { return worry % 3 == 0 ? 7 : 2; }},
            Monkey {queue<long long>({89}), [](long long worry) { return worry * worry; }, [](long long worry) { return worry % 11 == 0 ? 0 : 2; }},
        };

        const int MONKEYS = 8;

        // TODO: find relationship between mod transitions to keep numbers low enough to not overflow
        // Monkey monkeys[MONKEYS] = {
        //     Monkey {queue<long long>({79, 98}), 23, [](long long worry) { return worry * 19; }, [](long long worry) { return worry % 23 == 0 ? 2 : 3; }},
        //     Monkey {queue<long long>({54, 65, 75, 74}), 19, [](long long worry) { return worry + 6; }, [](long long worry) { return worry % 19 == 0 ? 2 : 0; }},
        //     Monkey {queue<long long>({79, 60, 97}), 13, [](long long worry) { return worry * worry; }, [](long long worry) { return worry % 13 == 0 ? 1 : 3; }},
        //     Monkey {queue<long long>({74}), 17, [](long long worry) { return worry + 3; }, [](long long worry) { return worry % 17 == 0 ? 0 : 1; }},
        // };

        long inspections[MONKEYS] = {0};
        for (int round = 0; round < 20; round++) {
            // if (round % 10 == 0) {
            //     cout << endl
            //          << "Before round " << round << endl;
            //     for (int i = 0; i < MONKEYS; i++) {
            //         queue<long long> q = monkeys[i].items;
            //         cout << "Monkey " << i << ": ";
            //         while (!q.empty()) {
            //             cout << q.front() << " ";
            //             q.pop();
            //         }
            //         cout << endl;
            //     }
            // }
            for (int i = 0; i < MONKEYS; i++) {
                Monkey &m = monkeys[i];
                size_t items = m.items.size();
                for (size_t k = 0; k < items; k++) {
                    long long item = m.items.front();
                    m.items.pop();
                    long long worry_level = m.op(item) / 3;
                    long long next_monkey = m.test(worry_level);
                    // if (round < 2) {

                    //     cout << "\tMonkey " << i << ": item " << item << " to worry level " << worry_level << " to monkey " << next_monkey << endl;
                    // }
                    monkeys[next_monkey].items.push(worry_level);
                    inspections[i]++;
                }
            }

            // if (round < 20 || (round + 1) % 1000 == 0) {
            //     cout << "Inspections after " << round + 1 << " rounds: ";
            //     for (int i = 0; i < MONKEYS; i++) {
            //         cout << inspections[i] << " ";
            //     }
            //     cout << endl
            //          << endl;
            // }
        }

        std::sort(std::rbegin(inspections), std::rend(inspections));
        assert(inspections[0] * inspections[1] == 78678);
        // cout << inspections[0] * inspections[1] << endl;
    }

} // namespace day11