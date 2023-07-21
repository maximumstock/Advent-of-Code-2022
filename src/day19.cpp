#include "aoc.cpp"
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

namespace day19 {

    struct Blueprint {
        uint16_t id;
        int costs[4][4];
    };

    struct BlueprintState {
        int tick = 0;
        // TODO: use bitset
        int resources[4] = {0, 0, 0, 0};
        int robots[4] = {1, 0, 0, 0};

        size_t compactHash() const {
            return (resources[0] << 28) | (resources[1] << 24) | (resources[2] << 20) | (resources[3] << 16) |
                   (robots[0] << 12) | (robots[1] << 8) | (robots[2] << 4) | (robots[3] << 0);
        }
    };

    bool operator==(const BlueprintState &lhs, const BlueprintState &rhs) {
        bool v = true;
        v = v && (lhs.tick == rhs.tick);
        v = v && (lhs.compactHash() == rhs.compactHash());
        return v;
    }

    struct BlueprintStateHash {
        std::size_t operator()(const BlueprintState &k) const { return k.compactHash(); }
    };

    enum Decision { ore, clay, obsidian, geode, wait };

    std::optional<BlueprintState> tick(BlueprintState &original_state, Blueprint &blueprint, Decision d) {
        BlueprintState state = original_state;
        state.tick += 1;

        // new resources
        int new_resources[4] = {0, 0, 0, 0};
        for (auto i = 0; i < 4; i++) {
            new_resources[i] += state.robots[i];
        }

        // decide if we should build anything
        array<int, 4> new_robots = {0, 0, 0, 0};
        if (d != Decision::wait) {
            auto build = true;

            // check resources
            auto robot_costs = blueprint.costs[d];
            for (auto i = 0; i < 4; i++) {
                if (robot_costs[i] > state.resources[i]) {
                    build = false;
                    break;
                }
            }

            // build
            if (build) {
                new_robots[d] = 1;
                for (auto i = 0; i < 4; i++) {
                    state.resources[i] -= robot_costs[i];
                }
            } else {
                return std::nullopt;
            }
        }

        // add new resources
        for (auto i = 0; i < 4; i++) {
            state.resources[i] += new_resources[i];
        }

        // add new robots
        for (auto i = 0; i < 4; i++) {
            state.robots[i] += new_robots[i];
        }

        return state;
    }

    uint16_t calculate_max_possible_geodes(Blueprint &blueprint, int max_ticks) {
        BlueprintState state = BlueprintState();
        std::deque<BlueprintState> queue {};
        queue.push_back(state);
        int max_geodes = 0;
        unordered_set<BlueprintState, BlueprintStateHash> seen_states {};

        Decision decisions[5] = {Decision::ore, Decision::clay, Decision::obsidian, Decision::geode, Decision::wait};

        while (!queue.empty()) {
            auto next = queue.front();
            queue.pop_front();

            for (auto d : decisions) {

                // prefer geodes
                if (d < Decision::geode) {
                    int max_cost_for_decision = 0;
                    for (auto i = 0; i < 4; i++) {
                        max_cost_for_decision = std::max(max_cost_for_decision, blueprint.costs[i][d]);
                    }
                    if (max_cost_for_decision == next.robots[d]) {
                        continue;
                    }
                }

                auto next_state = tick(next, blueprint, d);
                if (next_state.has_value()) {
                    auto value = next_state.value();

                    max_geodes = std::max(max_geodes, next.resources[3]);
                    if (value.tick == max_ticks) {
                        continue;
                    }
                    if (seen_states.contains(value)) {
                        continue;
                    }
                    seen_states.insert(value);
                    queue.push_front(value);
                }
            }
        }

        return max_geodes;
    }

    void solve() {
        ifstream infile("inputs/day19.txt");
        vector<Blueprint> blueprints {};
        std::vector<uint16_t> params {};

        for (string line; getline(infile, line);) {
            line.replace(line.find(":"), 1, "");
            auto tokens = aoc::split_string2(line, " ");

            for (auto token : tokens) {
                if (std::isdigit(token[0])) {
                    params.push_back(stoi(token));
                }
            }

            blueprints.push_back(Blueprint {params[0],
                                            {{params[1], 0, 0, 0},
                                             {params[2], 0, 0, 0},
                                             {params[3], params[4], 0, 0},
                                             {params[5], 0, params[6], 0}}});
            params.clear();
        }

        // Part 1
        int score = 0;
        for (auto i = 0; i < blueprints.size(); ++i) {
            auto blueprint = blueprints.at(i);
            int max_geodes = calculate_max_possible_geodes(blueprint, 25);
            score += max_geodes * blueprint.id;
        }
        assert(score == 1349);

        // Part 2
        int score2 = 1;
        for (auto i = 0; i < 3; ++i) {
            auto blueprint = blueprints.at(i);
            int max_geodes = calculate_max_possible_geodes(blueprint, 33);
            score2 *= max_geodes;
        }
        assert(score2 == 21840);
    }

} // namespace day19
