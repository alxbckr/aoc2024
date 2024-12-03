#include <algorithm>
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;

enum class Parts{
    All,
    Part1,
    Part2
};

enum State {
    None,
    OpFound,
    OpenBracket,
    Operand1,
    Separator,
    Operand2,
    ClosingBracket,
};

void solve_part1(ifstream& input){
    char c {};
    auto state { State::None };
    string buffer {};

    auto op1 = 0;
    auto op2 = 0;
    long long sum = 0;

    while(input >> c) {
        switch(c){
            case 'm': case 'u': case 'l':
                if (state != State::None) { buffer = ""; break; }
                buffer = buffer + c;
                if (buffer == "mul") state = State::OpFound;
                break;
            case '(':
                if (state != State::OpFound) { buffer = ""; break; }
                buffer = "";
                state = State::OpenBracket;
                break;            
            case ',':
                if (state != State::Operand1) { buffer = ""; break; }
                op1 = stoi(buffer);
                state = State::Separator;
                buffer = "";
                break;
            case ')':
                if (state != State::Operand2) { buffer = ""; break; }
                op2 = stoi(buffer);                
                sum += (op1 * op2);
                state = State::None;
                buffer = "";
                break;
            default: 
                if (isdigit(c)){
                    if (state == State::OpenBracket) state = State::Operand1;
                    if (state == State::Separator) state = State::Operand2;
                    if (state != State::Operand1 && state != State::Operand2) { buffer = ""; break; }                    
                    buffer += c;
                    break;
                }
                state = State::None;
                buffer = "";
                break;
        }
    }
    cout << "Solution 1: " << sum << endl;    
}

void solve_part2(ifstream& input) {
    char c {};
    auto state { State::None };
    string buffer {};
    
    auto enabled { true };
    string op {};
    auto op1 = 0;
    auto op2 = 0;
    long long sum = 0;

    while(input >> c) {
        switch(c){
            case 'd': case 'o': case 'n': case '\'': case 't':
                if (state != State::None && !( state == State::OpFound && buffer == "do") ) { 
                    buffer = ""; 
                    break; 
                }
                
                if (!buffer.empty() && buffer[0] != 'd'){
                    buffer = "";
                }

                if (state == State::OpFound && buffer == "do"){
                    // continue with don't
                    op = "";
                    state = State::None;
                }

                buffer = buffer + c;

                cout << buffer << endl;

                if (buffer == "do" || buffer == "don't") {
                    op = buffer; 
                    state = State::OpFound;                    
                }
                break;            
            case 'm': case 'u': case 'l':
                if (state != State::None) { buffer = ""; break; }
                if (!buffer.empty() && buffer[0] != 'm'){
                    buffer = "";
                }
                buffer = buffer + c;
                if (buffer == "mul") {
                    op = buffer; 
                    state = State::OpFound;
                }
                break;
            case '(':
                if (state != State::OpFound) { buffer = ""; break; }
                buffer = "";
                state = State::OpenBracket;
                break;            
            case ',':
                if (state != State::Operand1) { buffer = ""; break; }
                op1 = stoi(buffer);
                state = State::Separator;
                buffer = "";
                break;
            case ')':
                if (state == State::OpenBracket && ( op == "do" || op == "don't" ) ){
                    if (op == "do" ) enabled = true;
                    else enabled = false;
                    state = State::None;
                    buffer = ""; 
                    break;
                } else if (state != State::Operand2) { buffer = ""; break; }
                op2 = stoi(buffer);                
                if (enabled) sum += (op1 * op2);
                state = State::None;
                buffer = "";
                break;
            default: 
                if (isdigit(c)){
                    if (state == State::OpenBracket) state = State::Operand1;
                    if (state == State::Separator) state = State::Operand2;
                    if (state != State::Operand1 && state != State::Operand2) { buffer = ""; break; }                    
                    buffer += c;
                    break;
                }
                state = State::None;
                buffer = "";
                break;
        }
    }
    cout << "Solution 2: " << sum << endl;
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