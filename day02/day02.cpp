#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class Parts{
    All,
    Part1,
    Part2
};

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void split_string(const string& input, const char delimiter, vector<string>& buffer) {
    istringstream stream(input);
    string token;
    while(getline(stream, token, delimiter)) {
        buffer.push_back(token);
    }
}

void read_file(ifstream& input, vector<string>& lines) {
    string line;
    while(getline(input, line)) {
        lines.push_back(line);
    }
}

bool probe_safety(const vector<string>& levels){
    auto level_prev = 0;
    auto sign = 0;
    auto safe = true;
    for (int i = 0; i < levels.size(); i++) {
        auto level_curr = stoi(levels[i]);
        if (i == 1) {
            sign = sgn(level_curr - level_prev);
        }
        if (i > 0) {
            auto delta = abs(level_curr - level_prev);
            if ( delta < 1 || delta > 3 || sign != sgn( level_curr - level_prev ) ){
                return false;
            }
        }
        level_prev = level_curr;
    }
    return true;
}

void solve_part1(ifstream& input) {
    vector<string> reports;
    read_file(input, reports);

    auto safe_levels = 0;

    for (auto report : reports) {        
        vector<string> levels;
        split_string(report, ' ', levels);        
        if (probe_safety(levels)) safe_levels++;
    }

    cout << "Solution 1: " << safe_levels << endl;
}

void solve_part2(ifstream& input){
    vector<string> reports;
    read_file(input, reports);

    auto safe_levels = 0;

    for (auto report : reports) {
        vector<string> levels;
        split_string(report, ' ', levels);             
        if (probe_safety(levels)) safe_levels++;
        else {
            for (auto attempt = 0; attempt < levels.size(); attempt++){
                auto levels_copy = levels;
                levels_copy.erase(next(levels_copy.begin(), attempt));
                if (probe_safety(levels_copy)) { 
                    safe_levels++;
                    break;
                }
            }
        }
    }

    cout << "Solution 2: " << safe_levels << endl;
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