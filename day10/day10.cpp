#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

enum class Parts{
    All,
    Part1,
    Part2
};

void step(pair<int,int> start, int dx, int dy, const vector<vector<int>>& topo_map, 
    stack<pair<int,int>>& s, map<pair<int,int>, bool>& visited) {
    
    auto x = start.first + dx;
    auto y = start.second + dy;
    pair<int,int> p {x,y};
    if (!(x >= 0 && x < topo_map[0].size() && y >= 0 && y < topo_map.size()) 
        || topo_map[y][x] != topo_map[start.second][start.first] + 1
        || visited[p]) return;

    visited[p] = true;
    s.push(p);
}

void step_2(pair<int,int> start, int dx, int dy, const vector<vector<int>>& topo_map, 
    stack<pair<int,int>>& s) {
    
    auto x = start.first + dx;
    auto y = start.second + dy;
    pair<int,int> p {x,y};
    if (!(x >= 0 && x < topo_map[0].size() && y >= 0 && y < topo_map.size()) 
        || topo_map[y][x] != topo_map[start.second][start.first] + 1) return;

    s.push(p);
}

int calc_trails(pair<int,int> start,const vector<vector<int>>& topo_map) {
    auto count {0};
    map<pair<int,int>, bool> visited;
    stack<pair<int,int>> s;

    auto v = topo_map[start.second][start.first];
    s.push(start);
    while (!s.empty()){
        auto p = s.top();
        s.pop();  
        
        if (topo_map[p.second][p.first] == 9)  {
            count++;
            continue;
        }

        step(p, -1, 0, topo_map, s, visited);
        step(p, +1, 0, topo_map, s, visited);
        step(p, 0, -1, topo_map, s, visited);
        step(p, 0, +1, topo_map, s, visited);
    }

    return count;
}

int calc_trails_2(pair<int,int> start,const vector<vector<int>>& topo_map) {
    auto count {0};
    stack<pair<int,int>> s;

    auto v = topo_map[start.second][start.first];
    s.push(start);
    while (!s.empty()){
        auto p = s.top();
        s.pop();  
        
        if (topo_map[p.second][p.first] == 9)  {
            count++;
            continue;
        }

        step_2(p, -1, 0, topo_map, s);
        step_2(p, +1, 0, topo_map, s);
        step_2(p, 0, -1, topo_map, s);
        step_2(p, 0, +1, topo_map, s);
    }

    return count;
}


void solve_part1(ifstream& input) {
    vector<vector<int>> topo_map {};

    string line;
    while(getline(input, line)){
        vector<int> v;
        for (const auto c : line) v.push_back(atoi(&c));
        topo_map.push_back(v);
    }

    auto res {0};
    for (auto y = 0; y < topo_map.size(); y++) {
        for (auto x = 0; x < topo_map[y].size(); x++) {
            if (topo_map[y][x] != 0) continue;
            pair<int,int> p {x,y};
            res += calc_trails(p, topo_map);
        }
    }

    cout << "Solution 1: " << res << endl;
}

void solve_part2(ifstream& input){
    vector<vector<int>> topo_map {};

    string line;
    while(getline(input, line)){
        vector<int> v;
        for (const auto c : line) v.push_back(atoi(&c));
        topo_map.push_back(v);
    }

    auto res {0};
    for (auto y = 0; y < topo_map.size(); y++) {
        for (auto x = 0; x < topo_map[y].size(); x++) {
            if (topo_map[y][x] != 0) continue;
            pair<int,int> p {x,y};
            res += calc_trails_2(p, topo_map);
        }
    }

    cout << "Solution 2: " << res << endl;
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