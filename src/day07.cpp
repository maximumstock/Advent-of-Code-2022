#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "aoc.cpp"

using namespace std;

namespace day07
{

    unsigned int calculate_size(map<string, vector<string>> dirs, map<string, vector<tuple<string, unsigned int>>> files, map<string, unsigned int> &cache, string dir)
    {
        unsigned int sum = 0;

        for (auto d : dirs[dir])
        {
            if (cache.contains(d))
            {
                sum += cache[d];
            }
            else
            {
                sum += calculate_size(dirs, files, cache, d);
            }
        }

        for (auto f : files[dir])
        {
            sum += std::get<1>(f);
        }

        cache[dir] = sum;

        return sum;
    }

    void solve()
    {
        map<string, vector<string>> subdirs;
        map<string, vector<tuple<string, unsigned int>>> files;
        map<string, string> dir_parents;
        string current_directory;

        ifstream infile("inputs/day07.txt");

        for (string line; getline(infile, line);)
        {
            if (line.starts_with("$ cd"))
            {
                string target = line.substr(5);
                if (target == "..")
                {
                    current_directory = dir_parents[current_directory];
                }
                else if (target == "/")
                {
                    current_directory = "/";
                }
                else
                {
                    string next_dir = current_directory + (current_directory.ends_with("/") ? "" : "/") + target;
                    current_directory = next_dir;
                    if (!subdirs.contains(next_dir))
                    {
                        subdirs[next_dir];
                        files[next_dir];
                    }
                }
            }
            else if (line.starts_with("$ ls"))
            {
                continue;
            }
            else if (line.starts_with("dir"))
            {
                auto subdir_name = (current_directory.ends_with("/") ? current_directory : current_directory + "/") + aoc::split_string(line, ' ').at(1);
                dir_parents[subdir_name] = current_directory;
                subdirs[current_directory].push_back(subdir_name);
            }
            else
            {
                auto file = aoc::split_string(line, ' ');
                auto file_size = (unsigned int)stoi(file.at(0));
                auto file_name = file.at(1);
                auto file_node = make_tuple(file_name, file_size);
                files[current_directory].push_back(file_node);
            }
        }

        unsigned int p1 = 0;
        map<string, unsigned int> cache;
        for (auto pair : subdirs)
        {
            auto size = calculate_size(subdirs, files, cache, pair.first);
            if (size <= 100000)
            {
                p1 += size;
            }
        }
        assert(p1 = 1141028);

        const unsigned int space_to_free = 30000000 - (70000000 - cache["/"]);
        unsigned int p2 = INT_MAX;
        for (auto pair : cache)
        {
            if (pair.second >= space_to_free && pair.second <= p2)
            {
                p2 = pair.second;
            }
        }

        assert(p2 == 8278005);
    }

}