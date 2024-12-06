#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

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
    bool operator!=(const Coord& coord) const {
        if (this->x != coord.x || this->y != coord.y) return true;
        return false;
    }         
};

const Coord DirLeft {-1,0};
const Coord DirRight {1,0};
const Coord DirUp {0,-1};
const Coord DirDown {0,1};

Coord get_next_coord(const Coord& coord, const Coord& dir) {
    return Coord{coord.x+dir.x, coord.y+dir.y};
}

char peek_next(const vector<string>& zmap, const Coord& guard_pos, const Coord& dir) {
    auto coord = get_next_coord(guard_pos, dir);
    if (coord.x >= 0 && coord.y >= 0 && coord.x < zmap[0].length() && coord.y < zmap.size()) {
        return zmap.at(coord.y).at(coord.x);
    }
    return '\0';
}

void parse_input(ifstream& input, vector<string>& zmap, Coord& guard_pos) {
    auto y {0};
    string line;
    while(getline(input, line)) {
        zmap.push_back(line);        
        auto x = line.find('^');
        if (x != string::npos) { guard_pos.x = x; guard_pos.y = y; }
        y++;
    }
}

void switch_dir(Coord& dir) {
    if (dir == DirUp) dir = DirRight;
    else if (dir == DirRight) dir = DirDown;
    else if (dir == DirDown) dir = DirLeft;
    else dir = DirUp;
}

void draw_loop(const  vector<string> zmap, const vector<Coord>& loop_points, const Coord& obstacle){
    for (auto y = 0; y < zmap.size(); y++) {
        for (auto x = 0; x < zmap[y].length(); x++) {
            Coord c {x, y};
            if (c == obstacle) cout << "O";
            else if (find(loop_points.begin(),loop_points.end(),c) != loop_points.end()){
                cout << '*';
            } 
            else {
                cout << zmap.at(y).at(x);
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool detect_loop(const  vector<string> zmap, const Coord& start, const Coord& obstacle, const Coord& start_dir) {   
    map<Coord,vector<Coord>> visited;

    auto& history = visited[start];
    history.push_back(start_dir);

    vector<Coord> loop_points;
    Coord dir {start_dir};
    Coord pos = start;

    do {
        auto next = peek_next(zmap, pos, dir);
        switch (next)
        {
        case '\0':
            return false;
        case '#':        
            switch_dir(dir);
            break;
        default:            
            //loop_points.push_back(pos);
            pos = get_next_coord(pos, dir);

            auto& history = visited[pos];
            if (find(history.begin(), history.end(), dir) != history.end()) return true;
            history.push_back(dir);

            break;
        }
    } while(true);
    //draw_loop(zmap, loop_points, obstacle);
    return true;
}

void solve_part1(ifstream& input) {
    vector<string> zmap;
    map<Coord, bool> visited {};

    Coord guard_pos {};
    parse_input(input, zmap, guard_pos);

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
            switch_dir(dir);
            break;
        default:
            guard_pos = get_next_coord(guard_pos, dir);
            break;
        }
    }

    cout << "Solution 1: " << visited.size() << endl;
}

void solve_part2(ifstream& input){
    vector<string> zmap;
    map<Coord, bool> visited {};

    Coord guard_pos {};
    parse_input(input, zmap, guard_pos);

    auto start {guard_pos};
    auto exit = false;
    auto start_dir = DirUp;
    auto dir = DirUp;
    auto cycles { 0 };
    
    while (!exit){
        auto next = peek_next(zmap, guard_pos, dir);
        switch (next)
        {
        case '\0':
            exit = true;
            break;
        case '#':        
            switch_dir(dir);
            break;
        default:
            Coord obstacle = get_next_coord(guard_pos,dir);
            if (start != obstacle && visited.count(obstacle) == 0) {
                // put an "obstacle" before and see if that will be a loop
                auto map_copy = zmap;
                map_copy[obstacle.y][obstacle.x] = '#';
                if (detect_loop(map_copy, start, obstacle, start_dir)) {
                    visited[obstacle] = true;
                    cycles++;
                //cout << "loop at " << obstacle.y + 1 << " " << obstacle.x + 1 << endl;
                }
            }

            guard_pos = get_next_coord(guard_pos,dir);
            break;
        }
    }

    cout << "Solution 2: " << cycles << endl;
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