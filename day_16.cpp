#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

void spin(char* s, int x) {
    int y = strlen(s) - x;
    char* first = (char*) malloc(y);
    char* second = (char*) malloc(x);
    memcpy(first, s, y);    
    memcpy(second, s+y, x);
    memcpy(s, second, x);
    memcpy(s+x, first, y);
    free(first);
    free(second);
}

void exchange(char* s, int from, int to) {
    char tmp = s[from];
    s[from] = s[to];
    s[to] = tmp;
}

void partner (char* s, char a, char b) {
    char* pos_a = strchr(s, a);
    char* pos_b = strchr(s, b);
    *pos_b = a;
    *pos_a = b;
}

void process_move(char* s, char* move) {
    int i, j;
    char a, b;

    switch (move[0])
    {
    case 's':
        i = atoi(move+1);
        spin(s, i);
        break;
    case 'x':
        i = atoi(move+1);
        j = atoi(strchr(move, '/') + 1);
        exchange(s, i, j);
        break;
    case 'p':
        a = move[1];
        b = move[3];
        partner(s, a, b);
        break; 
    default:
        break;
    }
}

void perform_one_round(char* s, std::vector<std::string> moves) {
    for (auto move : moves) 
        process_move(s, move.data());
}

int main() {

    std::ifstream file("../in16.txt");

    char s[] = "abcdefghijklmnop";
    std::string line;
    std::getline(file, line);
    std::vector<std::string> moves;
    std::unordered_map<std::string, int> results;
    
    char *token = strtok(line.data(), ",");
    while (token != NULL) {
        moves.push_back(token);
        token = strtok(NULL, ",");
    }
    
    for (int i = 0; ; i++) {
        perform_one_round(s, moves);
        std::string result(s);
        if (results.find(result) == results.end()) {
            results[result] = i;
        } else {
            break;
        }
    }


    int part_1 = 0;
    int part_2 = 1'000'000 % results.size() - 1;

    for (auto [k, v] : results) {
        if (v == part_1)
            std::cout << "Solution for part 1: " << k << std::endl;
        if (v == part_2)
            std::cout << "Solution for part 2: " << k << std::endl;
        
    }

    file.close();

    



    return 0;
}