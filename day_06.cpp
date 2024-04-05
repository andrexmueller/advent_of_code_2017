/*
    Advent of Code - 2017
    Day 6: Memory Reallocation

*/


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "utils.h"



void reallocation(std::vector<int> &banks);
std::string vector_to_string(std::vector<int> banks);
void solution(std::vector<std::string> input_banks);


int main()
{
    
    std::string str_in{};
    std::getline(std::cin, str_in);
    std::vector<std::string> banks = utils::search_all(str_in, "\\d+");
    solution(banks);
    
    return 0;
}


void reallocation(std::vector<int> &banks) {

    // find the highest bank
    int highest = banks[0];
    int hi_index = 0;
    int len = (int) banks.size();  // cast size as int to avoid annoying warnings from compiler
    
    for (int i = 0; i < len; i++) {
        if (banks[i] > highest){
            highest = banks[i];
            hi_index = i;
        }
    }

    // setting highest to 0
    banks[hi_index] = 0;

    // equaly distribuited mem
    int mem_plus = highest / banks.size();
    // leftover mem
    int mem_rest = highest % banks.size();

    for (int i = 0; i < len; i++) {
        banks[(i+hi_index+1)%banks.size()] += mem_plus;
        if (mem_rest > 0) {
            banks[(i+hi_index+1)%banks.size()]++;
            mem_rest--;
        }
    }
}


std::string vector_to_string(std::vector<int> banks) {
    std::stringstream ss{};
    for (auto b : banks) ss << b << "_";
    std::string str{};
    ss >> str;
    return str;
}


void solution(std::vector<std::string> input_banks) {

    // cast the vector to ints in order to do the calculations
    std::vector<int> banks{};
    for (auto b : input_banks) banks.push_back(std::stoi(b));

    // set to track all the configurations
    std::unordered_map<std::string, int> dict{};

    // rounds counter
    int counter{};
    
    std::string config = vector_to_string(banks);
    
    while (dict.find(config) == dict.end()) {
        dict[config] = counter++;
        reallocation(banks);
        config = vector_to_string(banks);
    }

    std::cout << "Solution for part 1: " << counter << std::endl;
    std::cout << "Solution for part 1: " << counter - dict[config] << std::endl;


}
