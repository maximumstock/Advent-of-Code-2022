#include "aoc.cpp"
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

namespace day18 {

    struct Pocket {
        int size;
        int surface;
    };

    // Basic BFS
    Pocket calculate_pocket_surface(set<tuple<int, int, int>> &droplets, set<tuple<int, int, int>> &traversed,
                                    int min_x, int max_x, int min_y, int max_y, int min_z, int max_z,
                                    tuple<int, int, int> tuple) {

        vector<std::tuple<int, int, int>> queue {};
        set<std::tuple<int, int, int>> pocket_nodes {};
        int surface = 0;

        queue.push_back(tuple);
        pocket_nodes.insert(tuple);

        while (!queue.empty()) {
            auto node = queue.back();
            queue.pop_back();

            if (traversed.contains(node)) {
                continue;
            }
            traversed.insert(node);

            int x = get<0>(node);
            int y = get<1>(node);
            int z = get<2>(node);

            if (x < min_x || x > max_x || y < min_y || y > max_y || z < min_z || z > max_z) {
                continue;
            }

            pocket_nodes.insert(node);

            vector<std::tuple<int, int, int>> neighbours {
                make_tuple(x + 1, y, z), make_tuple(x - 1, y, z), make_tuple(x, y + 1, z),
                make_tuple(x, y - 1, z), make_tuple(x, y, z + 1), make_tuple(x, y, z - 1),
            };

            for (auto neighbour : neighbours) {
                if (droplets.contains(neighbour)) {
                    surface++;
                } else {
                    queue.push_back(neighbour);
                }
            }
        }

        return Pocket {(int)pocket_nodes.size(), surface};
    }

    bool is_pocket(set<tuple<int, int, int>> &droplets, tuple<int, int, int> tuple, int min_x, int max_x, int min_y,
                   int max_y, int min_z, int max_z) {
        int x = get<0>(tuple);
        int y = get<1>(tuple);
        int z = get<2>(tuple);

        for (int i = x; i <= max_x; i++) {
            auto id = make_tuple(i, y, z);
            if (droplets.contains(id)) {
                break;
            }
            if (i == max_x) {
                return false;
            }
        }

        for (int i = x; i >= min_x; i--) {
            auto id = make_tuple(i, y, z);
            if (droplets.contains(id)) {
                break;
            }
            if (i == min_x) {
                return false;
            }
        }

        for (int i = y; i <= max_y; i++) {
            auto id = make_tuple(x, i, z);
            if (droplets.contains(id)) {
                break;
            }
            if (i == max_y) {
                return false;
            }
        }

        for (int i = y; i >= min_y; i--) {
            auto id = make_tuple(x, i, z);
            if (droplets.contains(id)) {
                break;
            }
            if (i == min_y) {
                return false;
            }
        }

        for (int i = z; i <= max_z; i++) {
            auto id = make_tuple(x, y, i);
            if (droplets.contains(id)) {
                break;
            }
            if (i == max_z) {
                return false;
            }
        }

        for (int i = z; i >= min_z; i--) {
            auto id = make_tuple(x, y, i);
            if (droplets.contains(id)) {
                break;
            }
            if (i == min_z) {
                return false;
            }
        }

        return true;
    }

    void solve() {
        ifstream infile("inputs/day18.txt");
        set<tuple<int, int, int>> grid {};

        int min_x = 1000, max_x = 0, min_y = 1000, max_y = 0, min_z = 1000, max_z = 0;

        for (string line; getline(infile, line);) {
            vector<string> parts = aoc::split_string(line, ',');
            int x = stoi(parts[0]), y = stoi(parts[1]), z = stoi(parts[2]);
            min_x = min(min_x, x);
            min_y = min(min_y, y);
            min_z = min(min_z, z);
            max_x = max(max_x, x);
            max_y = max(max_y, y);
            max_z = max(max_z, z);
            grid.insert(make_tuple(x, y, z));
        }

        int total_surface = 0;
        for (auto cell : grid) {
            int x = get<0>(cell);
            int y = get<1>(cell);
            int z = get<2>(cell);

            if (!grid.contains(make_tuple(x + 1, y, z))) {
                total_surface++;
            }
            if (!grid.contains(make_tuple(x - 1, y, z))) {
                total_surface++;
            }
            if (!grid.contains(make_tuple(x, y + 1, z))) {
                total_surface++;
            }
            if (!grid.contains(make_tuple(x, y - 1, z))) {
                total_surface++;
            }
            if (!grid.contains(make_tuple(x, y, z + 1))) {
                total_surface++;
            }
            if (!grid.contains(make_tuple(x, y, z - 1))) {
                total_surface++;
            }
        }

        // Part 2
        // given a set of nodes which represent the droplet
        // iterate through all (0-x/y/z-max)^3 coordinates
        //  skip node if:
        //      - node is a droplet coordinate
        //      - node was already traversed from work step below
        //      - node is at border, eg. x/y/z = 0 or 19 (see narrower loop bounds)
        //      - node is outside of min_x, max_x, min_y, max_y, min_z, max_z as these nodes represent the
        //        bounding box and can't be inside the droplet
        //      - node does not have a droplet node in each direction
        //  for all other nodes, do actual work:
        //      - start a BFS from node in all 6 directions
        //      - take note of each node traversed this way
        //      - for each node, sum the number of sides that these empty nodes share with neighbouring droplet nodes
        set<tuple<int, int, int>> traversed {};
        std::vector<Pocket> pockets = {};

        for (int x = min_x; x <= max_x; x++) {
            for (int y = min_y; y <= max_y; y++) {
                for (int z = min_z; z <= max_z; z++) {
                    auto tuple = make_tuple(x, y, z);
                    if (grid.contains(tuple) || traversed.contains(tuple)) {
                        continue;
                    }

                    if (is_pocket(grid, tuple, min_x, max_x, min_y, max_y, min_z, max_z)) {
                        auto pocket =
                            calculate_pocket_surface(grid, traversed, min_x, max_x, min_y, max_y, min_z, max_z, tuple);
                        pockets.push_back(pocket);
                    }
                }
            }
        }

        std::sort(pockets.begin(), pockets.end(),
                  [](const Pocket &a, const Pocket &b) -> bool { return a.size > b.size; });
        auto lambda = [&](int sum, Pocket p) { return sum + p.surface; };
        int inner_surface = std::accumulate(pockets.begin() + 1, pockets.end(), 0, lambda); // skip largest pocket

        assert(total_surface == 3522);
        assert(total_surface - inner_surface == 2074);
    }

} // namespace day18
