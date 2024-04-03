/*
    Advent of Code - 2017
    Day 4: High-Entropy Passphrases

*/


#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>


std::vector<std::string> split_line(std::string line) {

    std::vector<std::string> s_vector{};
    size_t i = 0;
    std::string word{};

    while ((i = line.find(" ")) != std::string::npos) {
        word = line.substr(0, i);
        s_vector.push_back(word);
        line.erase(0, i+1);
    }
    s_vector.push_back(line);

    return s_vector;

}


bool counter_part_1(std::vector<std::string> vs) {

    std::unordered_set<std::string> words{};
    int words_count = 0;
    for (auto s : vs) {
        words.insert(s);
        words_count++;
    }

    return words.size() == words_count;
}


bool counter_part_2(std::vector<std::string> vs) {
    std::unordered_set<std::string> words{};
    int words_count = 0;
    for (auto s : vs) {
        sort(s.begin(), s.end());
        words.insert(s);
        words_count++;
    }

    return words.size() == words_count;

}



int main() {

    std::string line{};
    int i{};
    int valid_pass_count{};
    char *letters;

    std::vector<std::string> s_vector{};
    int acc_part_1 = 0;
    int acc_part_2 = 0;


    while(std::getline(std::cin, line)) {
        
        s_vector = split_line(line);
        acc_part_1 += counter_part_1(s_vector);
        acc_part_2 += counter_part_2(s_vector);
    }
    
    std::cout << "Solution for part 1: " << acc_part_1 << std::endl;
    std::cout << "Solution for part 2: " << acc_part_2 << std::endl;
    

}