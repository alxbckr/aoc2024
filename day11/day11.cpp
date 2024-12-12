#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <utility>

using namespace std;

enum class Parts{
    All,
    Part1,
    Part2
};

bool is_even(long long a) {
    if (a < 10) return false;
    int digits = static_cast<long long>(log10(a));
    return digits % 2 == 1;
}

pair<long long, long long> split(long long a) {
    long long digits = static_cast<long long>(log10(a)+1);
    long long divisor = static_cast<long long>(pow(10, digits / 2));
    return make_pair(a / divisor, a % divisor);
}

void solve_part1(ifstream& input) {
    map<long long, long long> stones {};

    long long s;
    while(input >> s) stones[s] += 1;

    for (const auto& s : stones) {
        cout << " " << s.first;
    }
    cout << endl;

    auto step {0};
    while (step < 75) {
        map<long long,long long> new_stones;

        for (const auto& s : stones) {
            if (s.first == 0) {
                new_stones[1] += s.second;      
            } else if (is_even(s.first)) {
                auto p = split(s.first);
                new_stones[p.first] += s.second;                
                new_stones[p.second] += s.second;                
            } else {
                auto d {s.first * 2024};
                new_stones[d] += s.second;
            }
        }    

        stones = new_stones;    
        step++;

        //for (auto s : stones) cout << s.first << ":" << s.second << " ";
        long long res {0};
        for (auto s : stones) {
            res += s.second;
        }        
        cout << res << endl;
    }

    long long res {0};
    for (auto s : stones) {
        res += s.second;
    }
    cout << "Solution 1: " << res << endl;
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