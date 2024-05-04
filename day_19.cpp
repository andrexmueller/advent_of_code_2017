#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <unordered_map>

typedef unsigned long long ull;
class Cell;

class Cell {
public:
    int row, col;  
    char dir;      // direction 'u', 'd', 'l', 'r' 
    int steps;
    std::vector<char> letters;

    
    Cell(int r, int c, char d = 'd') {
        row = r;
        col = c;
        dir = d;
        steps = 0;
    }

    bool move(std::vector<std::string>& grid) {
        if (grid[row][col] == ' ') {
            return false;
        }
        steps++;
        int next_r = row; int next_c = col;
        char next_d = dir;
        if (dir == 'd') next_r = row + 1;
        if (dir == 'u') next_r = row - 1;
        if (dir == 'l') next_c = col - 1;
        if (dir == 'r') next_c = col + 1;
        
        if (grid[next_r][next_c] == '+') {
            if (grid[next_r + 1][next_c] != ' ' && dir != 'u') 
                next_d = 'd';
            if (grid[next_r - 1][next_c] != ' ' && dir != 'd') 
                next_d = 'u';
            if (grid[next_r][next_c + 1] != ' ' && dir != 'l') 
                next_d = 'r';
            if (grid[next_r][next_c - 1] != ' ' && dir != 'r') 
                next_d = 'l';
        }

        if (grid[row][col] >= 65 && grid[row][col] <= 90) 
            letters.push_back (grid[row][col]);

        row = next_r;
        col = next_c;
        dir = next_d;
        return true;
    }

};


void foo(std::vector<std::string>& grid) {
    std::unordered_map<char, int> dict;
    for (ull i = 0; i < grid.size(); i++) {
        for (ull j = 0; j < grid[i].size(); j++) {
            if (dict.find(grid[i][j]) == dict.end()) {
                dict[grid[i][j]] = 1;
            } else {
                dict[grid[i][j]]++;
            }
        }
    }

    for (auto [k, v] : dict) {
        printf("%c: %d\n", k, v);
    }
    std::cout << grid.size() * grid[0].size();
}


int main() {


    std::ifstream f;
    f.open("../in19.txt");
    
    //f.open("in19.txt");
    std::string line;
    std::vector<std::string> grid;
    while (std::getline(f, line)) {
        grid.push_back(line);
    }
    
    Cell cell(0, grid[0].find('|'));
    bool m = cell.move(grid);
    while (m) {
        m = cell.move(grid);
    }

    std::cout << "Solution for part 1: ";
    for (char c : cell.letters) 
        std::cout << c;
    std::cout << "\nSolution for part 2: " << cell.steps << std::endl;

    return 0;
}