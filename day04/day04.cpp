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

void parse_input(ifstream& input, vector<vector<char>>& words) {
    string line;
    while(getline(input, line)) {
        std::vector<char> words_line(line.begin(), line.end());
        words.push_back(words_line);
    }
}

int scan(const vector<vector<char>>& words, int x, int y, int dx, int dy) {
    string word { };
    auto xx { x };
    auto yy { y };
    while ( xx >= 0 && xx < words[0].size() &&
            yy >= 0 && yy < words.size() ) {
        word += words[yy][xx];
        if (word == "XMAS") return 1;
        else if (word.length() > 4) return 0;
        xx += dx;
        yy += dy;
    }   
    return 0;
}

void solve_part1(ifstream& input) {
    vector<vector<char>> words;
    parse_input(input, words);

    auto found { 0 };

    for (auto x = 0; x < words[0].size(); x++){
        for (auto y = 0; y < words.size(); y++) {
            if (words[y][x] != 'X') continue;
                found += scan(words, x,y, +1, 0) + scan(words, x,y, -1, 0) +
                         scan(words, x,y, 0, +1) + scan(words, x,y, 0, -1) +
                         scan(words, x,y, +1, +1 ) + scan(words, x,y, -1, -1) +
                         scan(words, x,y, -1, +1 ) + scan(words, x,y, +1, -1);           
        }
    }

    cout << "Solution 1: " << found << endl;
}

void solve_part2(ifstream& input){
    vector<vector<char>> words;
    parse_input(input, words);

    int found { 0 };

    for (auto y = 0; y < words.size(); y++) {
        for (auto x = 0; x < words[0].size(); x++){
            if (words[y][x] != 'A' || x == 0 || x == words[0].size() - 1 || 
                y == 0 || y == words.size() - 1 ) continue;     

            string up = string() + words[y-1][x-1] + words[y-1][x+1];
            string bottom = string() + words[y+1][x-1] + words[y+1][x+1];
            string left = string() + words[y-1][x-1] + words[y+1][x-1];
            string right = string() + words[y-1][x+1] + words[y+1][x+1];

            if (up == "MM" && bottom == "SS" ||
                up == "SS" && bottom == "MM" ||
                left == "MM" && right == "SS" || 
                left == "SS" && right == "MM" ) {                            

               found += 1;
            }
        }
    }

    cout << "Solution 2: " << found << endl;
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