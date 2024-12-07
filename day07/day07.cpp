#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

enum class Parts{
    All,
    Part1,
    Part2
};

void parse_input(ifstream& input, vector<vector<long long>>& equations){
    string line {};    
    while(getline(input, line)){
        vector<long long> equation {};       
        istringstream ss{ line };
        long long result {0};
        ss >> result;
        equation.push_back(result);
        auto number {0};
        ss.ignore(1);
        while (ss >> number) {
            equation.push_back(number);
        }
        equations.push_back(equation);
    }
}

long long dfs(const vector<long long>& equation, const vector<char>& ops, size_t index, long long temp_res) {
    if (index >= equation.size()) return temp_res;
    for (auto op : ops){
        auto operand {equation[index]};
        long long op_result {0};
        switch (op)
        {
        case '*':
            op_result = temp_res * operand;
            break;
        case '+':
            op_result = temp_res + operand;
            break;
        case '|':
            op_result = stoll(to_string(temp_res) + to_string(operand));
            break;
        }
        auto res = dfs(equation, ops, index + 1, op_result);
        if (res == equation[0]){
            return res;
        }

    }
    return true;
}

void solve_part1(ifstream& input) {
    vector<vector<long long>> equations {};
    parse_input(input, equations);

    vector<char> ops {'+','*'};
    long long answer{0};

    for (const auto& eq : equations) {        
        auto need_result {eq[0]};
        auto eq_result = dfs(eq, ops, 2, eq[1]);
        if (eq_result == need_result) answer += eq_result;
    }

    cout << "Solution 1: " << answer << endl;
}

void solve_part2(ifstream& input){
    vector<vector<long long>> equations {};
    parse_input(input, equations);

    vector<char> ops {'+','*', '|'};
    long long answer{0};

    for (const auto& eq : equations) {        
        auto need_result {eq[0]};
        auto eq_result = dfs(eq, ops, 2, eq[1]);
        if (eq_result == need_result) answer += eq_result;
    }

    cout << "Solution 2: " << answer << endl;
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