#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace day12 {

    struct Position {
        int x;
        int y;

        constexpr Position &operator+=(const Position &rhs) {
            x = x + rhs.x;
            y = y + rhs.y;
            return *this;
        }

        constexpr bool operator<(const Position &other) const {
            return this->x < other.x || (this->x == other.x && this->y < other.y);
        }

        constexpr int distance(const Position &other) const {
            return (other.x - this->x) * (other.x - this->x) + (other.y - this->y) * (other.y - this->y);
        }
    };
    struct PathCost {
        int cost = 9999999;
    };

    struct Path {
        vector<Position> nodes {};
        int steps = 0;

        constexpr bool operator<(const Path &other) const {
            return steps < other.steps;
        }
    };

    const int WIDTH = 167;
    const int HEIGHT = 41;

    map<Position, PathCost> dijkstra(char (&grid)[WIDTH][HEIGHT], Position &start, char target, std::function<int(char, int)> cost_fn) {
        map<Position, PathCost> costs {};
        vector<Path> paths {};

        Position neighbours[4] = {
            Position {1, 0},
            Position {0, 1},
            Position {-1, 0},
            Position {0, -1},
        };

        paths.push_back(Path {vector<Position> {start}});
        costs[start].cost = 0;

        while (!paths.empty()) {
            Path next = paths.back();
            paths.pop_back();

            for (auto &offset : neighbours) {
                Path n = next;
                Position current_position = n.nodes.back();

                Position next_position = current_position;
                next_position += offset;

                if (next_position.x == WIDTH || next_position.x < 0 || next_position.y == HEIGHT || next_position.y < 0) {
                    continue;
                }

                char next_node = grid[next_position.x][next_position.y];
                char current_node = grid[current_position.x][current_position.y];
                int cost = cost_fn(next_node, n.steps);

                bool can_reach = next_node - current_node <= 1 || (current_node == 'z' && next_node == target) || current_node == 'S' || current_node == next_node;
                bool is_new_or_cheaper_path = !costs.contains(next_position) || (costs.contains(next_position) && costs[next_position].cost > cost);

                if (can_reach && is_new_or_cheaper_path) {
                    n.nodes.push_back(next_position);
                    n.steps = cost;
                    paths.push_back(n);
                    int new_cost = min(costs[next_position].cost, n.steps);
                    costs[next_position].cost = new_cost;

                    if (next_node == target) {
                        return costs;
                    }
                }
            }

            make_heap(paths.begin(), paths.end(), std::less<>());
        }

        return costs;
    }

    void solve() {
        ifstream infile("inputs/day12.txt");

        Position start, end;
        char grid[WIDTH][HEIGHT] {};

        int row = 0;
        for (string line; getline(infile, line);) {
            int col = 0;
            for (auto value : line) {
                if (value == '\n' || value == ' ' || value == 0) {
                    continue;
                }
                grid[col][row] = value;
                if (value == 'S') {
                    start = Position {(int)col, row};
                }
                if (value == 'E') {
                    end = Position {(int)col, row};
                }
                col++;
            }
            row++;
        }

        auto p1_costs = dijkstra(grid, start, 'E', [](__attribute__((unused)) char _next_node, int current_cost) { return current_cost + 1; });
        assert(p1_costs[end].cost == 517);
        auto p2_costs = dijkstra(grid, start, 'E', [](char next_node, int current_cost) { return next_node == 'a' ? current_cost : current_cost + 1; });
        assert(p2_costs[end].cost == 512);
    }

} // namespace day12
