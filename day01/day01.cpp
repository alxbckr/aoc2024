#include <array>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

enum class Parts{
    All,
    Part1,
    Part2
};

void solve_part1(ifstream& input) {
    int loc1, loc2, cursor {};
    array<int, 1000> locations1{};
    array<int, 1000> locations2{};
    while (input >> loc1 >> loc2) {
        locations1[cursor] = loc1;
        locations2[cursor] = loc2;
        cursor++;
    }
    auto size = cursor;

    sort(locations1.begin(), locations1.begin() + size);
    sort(locations2.begin(), locations2.begin() + size);

    auto total = 0;
    for (int c = 0; c < size; c++) {
        total += abs(locations1[c] - locations2[c]);
    }

    cout << "Solution " << total << endl;
}

void solve_part2(ifstream& input){
    int loc1, loc2, cursor {};
    array<int, 1000> locations1{};
    array<int, 1000> locations2{};
    while (input >> loc1 >> loc2) {
        locations1[cursor] = loc1;
        locations2[cursor] = loc2;
        cursor++;
    }
    auto size = cursor;

    sort(locations1.begin(), locations1.begin() + size);
    map<int,int> sim_score = {};

    auto total = 0;
    for (int c = 0; c < size; c++) {
        sim_score[locations2[c]] += 1;
    }

    for (int c = 0; c < size; c++) {
        total += locations1[c] * (sim_score.find(locations1[c]) == sim_score.end() ? 0 : sim_score[locations1[c]]);
    }

    cout << "Solution " << total << endl;
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