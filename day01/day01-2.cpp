#include <array>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cout << "Not enough arguments" << endl;
        return 0;
    };

    filesystem::path path{ argv[1] };
    if (!filesystem::exists(path)) {
        cout << "Input not found" << endl;
        return 0;
    }

    ifstream input { path, ios::in };

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

    return 0;
}