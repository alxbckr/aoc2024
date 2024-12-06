#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

enum class Parts{
    All,
    Part1,
    Part2
};

struct Coord {
    int x;
    int y;

    bool operator<(const Coord& coord) const {
        if(x < coord.x) return true;
        if(x > coord.x) return false;
        //x == coord.x
        if(y < coord.y) return true;
        if(y > coord.y) return false;
        //*this == coord
        return false;
    }
    
    bool operator==(const Coord& coord) const {
        if (this->x == coord.x && this->y == coord.y) return true;
        return false;
    }
};

const Coord DirLeft {-1,0};
const Coord DirRight {1,0};
const Coord DirUp {0,-1};
const Coord DirDown {0,1};

char peek_next(const vector<string>& zmap, const Coord& guard_pos, const Coord& dir) {
    auto x {guard_pos.x + dir.x};
    auto y {guard_pos.y + dir.y};
    if (x >= 0 && y >= 0 && x < zmap[0].length() && y < zmap.size()) {
        return zmap.at(y).at(x);
    }
    return '\0';
}

void solve_part1(ifstream& input) {
    vector<string> zmap;
    map<Coord, bool> visited {};

    Coord guard_pos {};
    auto y {0};
    string line;
    while(getline(input, line)) {
        zmap.push_back(line);        
        auto x = line.find('^');
        if (x != string::npos) { guard_pos.x = x; guard_pos.y = y; }
        y++;
    }

    auto exit = false;
    auto dir = DirUp;
    while (!exit){
        visited[guard_pos] = true;
        auto next = peek_next(zmap, guard_pos, dir);
        switch (next)
        {
        case '\0':
            exit = true;
            break;
        case '#':        
            if (dir == DirUp) dir = DirRight;
            else if (dir == DirRight) dir = DirDown;
            else if (dir == DirDown) dir = DirLeft;
            else dir = DirUp;
        default:
            guard_pos.x += dir.x;
            guard_pos.y += dir.y;
            break;
        }
    }

    cout << "Solution 1: " << visited.size() << endl;
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