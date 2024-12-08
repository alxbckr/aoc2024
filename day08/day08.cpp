#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum class Parts{
    All,
    Part1,
    Part2
};

const pair<int,int> not_found {-1,-1};

pair<int,int> find_next_antenna(const vector<string>& antenna_map, const int start_y, const int start_x, const char a) {
    pair<int,int> apos {not_found};
    for (int y = start_y; y < antenna_map.size(); y++){
        for (int x = 0; x < antenna_map[0].size(); x++){
            if (y == start_y && x <= start_x) continue;
            if (antenna_map.at(y).at(x) == a){
                apos.first = y;
                apos.second = x;
                return apos;
            }        
        }    
    }            
    return apos;
}

bool find_same_antenna(const vector<string>& antenna_map, const int start_y, const int start_x, const char a) {
    for (int y = 0; y < antenna_map.size(); y++){
        for (int x = 0; x < antenna_map[0].size(); x++){
            if (y == start_y && x == start_x) continue;
            if (antenna_map.at(y).at(x) == a){
                return true;
            }        
        }    
    }            
    return false;
}

void generate_anti(vector<vector<char>>& anti, int y1, int x1, int y2, int x2) {
    auto dx = x2 - x1;
    auto dy = y2 - y1;

    auto x = x1 - dx;
    auto y = y1 - dy;
    if (x >= 0 && x < anti[0].size() && y >= 0 && y < anti.size()){
        anti[y][x] = '#';
    }

    x = x2 + dx;
    y = y2 + dy;
    if (x >= 0 && x < anti[0].size() && y >= 0 && y < anti.size()){
        anti[y][x] = '#';
    }    
}

void generate_anti_2(vector<vector<char>>& anti, int y1, int x1, int y2, int x2) {
    auto dx = x2 - x1;
    auto dy = y2 - y1;

    auto x = x1 - dx;
    auto y = y1 - dy;

    while (x >= 0 && x < anti[0].size() && y >= 0 && y < anti.size()){
        anti[y][x] = '#';
        x -= dx;
        y -= dy;
    }

    x = x2 + dx;
    y = y2 + dy;
    while (x >= 0 && x < anti[0].size() && y >= 0 && y < anti.size()){
        anti[y][x] = '#';
        x += dx;
        y += dy;
    }    
}


void solve_part1(ifstream& input) {
    vector<string> antenna_map;
    vector<vector<char>> anti;

    string line;
    while(getline(input, line)) {
        antenna_map.push_back(line);
        vector<char> antiline(line.length(), '.');
        anti.push_back(antiline);
    }

    for (int y = 0; y < antenna_map.size(); y++){
        for (int x = 0; x < antenna_map[0].size();x++){
            char a = antenna_map.at(y).at(x);
            if (isalnum(static_cast<unsigned char>(a))){
                auto xx = x;
                auto yy = y;
                auto coord = find_next_antenna(antenna_map, yy, xx, a);
                while(coord != not_found){
                    generate_anti(anti, y, x, coord.first, coord.second);
                    yy = coord.first;
                    xx = coord.second;
                    coord = find_next_antenna(antenna_map, yy, xx, a);
                }                
            }
        }
    }
    
    auto count = 0;
    for (auto l : anti) {
        for (auto a : l){
            cout << a;
            if (a == '#') count++;
        }
        cout << endl;
    }

    cout << "Solution 1: " << count << endl;
}

void solve_part2(ifstream& input){
    vector<string> antenna_map;
    vector<vector<char>> anti;

    string line;
    while(getline(input, line)) {
        antenna_map.push_back(line);
        vector<char> antiline(line.length(), '.');
        anti.push_back(antiline);
    }

    for (int y = 0; y < antenna_map.size(); y++){
        for (int x = 0; x < antenna_map[0].size();x++){
            char a = antenna_map.at(y).at(x);
            if (!isalnum(static_cast<unsigned char>(a))) continue;
            auto xx = x;
            auto yy = y;
            auto coord = find_next_antenna(antenna_map, yy, xx, a);
            while(coord != not_found){
                generate_anti_2(anti, y, x, coord.first, coord.second);
                yy = coord.first;
                xx = coord.second;
                coord = find_next_antenna(antenna_map, yy, xx, a);
            }                
        }
    }
    
    auto count = 0;
    for (auto l : anti) {
        for (auto a : l){
            cout << a;
            if (a == '#') count++;
        }
        cout << endl;
    }

    for (int y = 0; y < antenna_map.size(); y++){
        for (int x = 0; x < antenna_map[0].size();x++){
            char a = antenna_map.at(y).at(x);
            if (!isalnum(static_cast<unsigned char>(a)) ||
                !find_same_antenna(antenna_map, y, x, a) || 
                anti[y][x] == '#' ) continue;
            count++;
        }
    }

    cout << "Solution 2: " << count << endl;
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