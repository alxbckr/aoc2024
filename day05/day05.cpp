#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

enum class Parts{
    All,
    Part1,
    Part2
};

void solve_part1(ifstream& input) {
    map<int, vector<int>> rules_after;
    map<int, vector<int>> rules_before;
    vector<vector<int>> updates;

    string line { };    
    auto update_mode { false };
    while (getline(input, line)) {
        if (line == "") update_mode = true;
        if (!update_mode) {
            //rules
            auto p1 = 0, p2 = 0;
            sscanf(line.c_str(), "%d|%d", &p1, &p2);
            rules_after[p1].push_back(p2);
            rules_before[p2].push_back(p1);
            cout << p1 << " " << p2 << endl;
        } else {
            vector<int> update;
            vector<int> update_reverse;
            stringstream ss(line);
            for (int i; ss >> i;) {
                update.push_back(i);
                if (ss.peek() == ',')
                    ss.ignore();                
            }
            updates.push_back(update);
        }
    }

    for (const auto update : updates) {
        for (auto i = 0; i < update.size(); i++ ) {
            // rules "after"
            for (auto j = i+1; j < update.size(); j++) {
                const auto& v = rules_before[update[j]];
                if (find(v.begin(),v.end(), update[i]) != v.end()) {
                    cout << update[i] << " violates after " << update[j];
                }
            }
        }
    }

    cout << "Solution 1: " << 0 << endl;
}

void solve_part2(ifstream& input){
    cout << "Solution 2: " << 0 << endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Not enough arguments" << endl;
        return -1;
    };

    filesystem::path path{ argv[1] };
    if (!filesystem::exists(path)) {
        cout << "Input not found" << endl;
        return -1;
    }

    auto parts = Parts::All;
    if (argc == 3) {
        switch (*argv[2]) {
            case '1':
                parts = Parts::Part1;
                break;
            case '2':
                parts = Parts::Part2;
                break;
            default:
                cout << "Invalid Part Input (1-2)" << endl;
                return -1;
        }
        
    }

    if (parts == Parts::All || parts == Parts::Part1){
        ifstream input { path, ios::in };        
        if (input.is_open()) {
            solve_part1(input);
            input.close();
        }
    }

    if (parts == Parts::All || parts == Parts::Part2){
        ifstream input { path, ios::in };        
        if (input.is_open()) {
            solve_part2(input);
            input.close();
        }
    }

    return 0;
}