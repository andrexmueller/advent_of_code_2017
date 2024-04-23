/*
    Advent of Code - 2017 
    Day 9: Stream Processing

*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>




int solve_part_1(std::string s) {
    
    int score = 0;
    bool open_angle = false;
    std::vector<char> stack{};

    int i = 0;
    while (i < s.size()) {
        if (s[i] == '!') {
            i += 2;
            continue;
        }
        if (s[i] == '{' && !open_angle) {
            stack.push_back('{');
        }
        if (s[i] == '}' && !open_angle) {
            score += stack.size();
            stack.pop_back();
        }
        if (s[i] == '<') {
            open_angle = true;
        } 
        if (s[i] == '>') {
            open_angle = false;
        }
        i++;
    }
    return score;
}

int solve_part_2(std::string s) {

    int garbage_count = 0;
    bool open_bracket = false;

    int i = 0;
    while (i < s.size()) {
        if (s[i] == '!') {
            i += 2;
            continue;
        }
        if (open_bracket){
            if (s[i] == '>') {
                open_bracket = false;
            } else {
                garbage_count++;
            }
        }
        if (s[i] == '<' && !open_bracket) {
            open_bracket = true;
        }
        i++;
    }
    return garbage_count;
}


int main() {

    std::string s{};

    std::getline(std::cin, s);

    // std::cout << s << std::endl;
    // std::cout << std::endl;
    
    std::cout << "Solution for part 1: " << solve_part_1(s) << std::endl;    
    std::cout << "Solution for part 2: " << solve_part_2(s) << std::endl;    

    return 0;
}
