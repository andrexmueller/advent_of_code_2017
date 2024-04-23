/*
    Advent of Code - 2017 
    Day 8: I Heard You Like Registers

*/


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "utils.h"



bool compare(std::string cmp, int v1, int v2){
    if (cmp == "==") return v1 == v2;
    else if (cmp == "<") return v1 < v2;
    else if (cmp == ">") return v1 > v2;
    else if (cmp == ">=") return v1 >= v2;
    else if (cmp == "<=") return v1 <= v2;
    else return v1 != v2;
}



int main() {

    
    std::unordered_map<std::string, int> registers{};

    std::string line{};
    std::vector<std::string> splited_line{};

    std::string reg1, reg2, inst, cmp; 
    int jmp, cnd;

    int max_reg_all = 0;

    while (std::getline(std::cin, line)){
        splited_line = utils::split_string(line, " ");
        
        // for (auto s : splited_line) std::cout << s << " ";
        // std::cout << std::endl;
        reg1 = splited_line[0];
        reg2 = splited_line[4];

        if (registers.find(reg1) == registers.end()) {
            registers[reg1] = 0;
        }
        if (registers.find(reg2) == registers.end()) {
            registers[reg2] = 0;
        }

        inst = splited_line[1];
        cmp = splited_line[5];

        jmp = std::stoi(splited_line[2]);
        cnd = std::stoi(splited_line[6]);

        if (compare(cmp, registers[reg2], cnd)) {
            registers[reg1] += inst == "inc" ? jmp : -jmp;
        }

        if (registers[reg1] > max_reg_all) {
            max_reg_all = registers[reg1];
        }

    }

    int max_reg = 0;
    for (auto [k, v] : registers) {
        if (v > max_reg) max_reg = v;
    }
    std::cout << "Solution for part 1: " << max_reg << std::endl;
    std::cout << "Solution for part 2: " << max_reg_all << std::endl;


    return 0;
}