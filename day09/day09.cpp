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

void parse_input(ifstream& input, vector<int>& fs){
    string line {};

    getline(input, line);
    fs.reserve(line.length() * 10);

    int file_pointer {0};
    int file_id {0};
    
    for (int cursor = 0; cursor < line.length(); cursor++){
        const int numblk = int(line.at(cursor))-48;
        for (int p = file_pointer; p < file_pointer + numblk; p++ ){
            if (cursor%2 == 0) fs.push_back(file_id);
            else fs.push_back(-1);
        }
        if (cursor%2 == 0) file_id++;
    }
}

void print_fs(vector<int>& fs) {
    for (auto c : fs) {
        if (c == -1) cout << '.';
        else cout << c;
    }
    cout << endl;
}

void solve_part1(ifstream& input) {
    vector<int> fs {}; 

    parse_input(input,fs);

    size_t c1 {0};
    size_t c2 {fs.size()-1};

    while (c2 > c1) {
        if (fs.at(c1) != -1) { c1++; continue; }

        while(fs.at(c2) == -1 && c2 > c1) c2--;

        fs[c1] = fs[c2];
        fs[c2] = -1;
        c2--;
        c1++;
    }   

    long long res {0};
    for (auto f = 0; f < fs.size(); f++) {
        if (fs.at(f) == -1) continue;
        res += fs.at(f) * f;
    }

    cout << "Solution 1: " << res << endl;
}

void solve_part2(ifstream& input){
    vector<int> fs {}; 

    parse_input(input,fs);

    size_t c1 {0};
    size_t c2 {fs.size()-1};

    while (c2 > c1) {
        if (fs.at(c1) != -1) { c1++; continue; }

        while(fs.at(c2) == -1 && c2 > c1) c2--;

        fs[c1] = fs[c2];
        fs[c2] = -1;
        c2--;
        c1++;
    }   

    long long res {0};
    for (auto f = 0; f < fs.size(); f++) {
        if (fs.at(f) == -1) continue;
        res += fs.at(f) * f;
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