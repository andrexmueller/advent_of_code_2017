/*
    Advent of Code - 2017 
    Day 14: Disk Defragmentation

*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <iomanip>
#include <sstream>
#include <unordered_set>
#include "utils.h"
#include <queue>


#define SIZE 256
#define ROUNDS 64
#define ASCII_OFFSET_TO_NUMS 48
#define GRID_SIZE 128


void make_knot(std::vector<int>& v, int pos, int len);
void knot_hash_round(std::vector<int>& len_seq, std::vector<int>& str, int &pos, int &skip_size);
std::string knot_hash(const char* str_to_hash);
int lil_bfs(bool **grid, int row, int col);

int main() {

    char input[] = "vbqugkhl";
    int ones = 0;
    
    bool **grid = new bool*[GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++) {
        grid[i] = new bool[GRID_SIZE];
    }

    
    for (int i = 0; i < GRID_SIZE; i++) {
        std::stringstream ss;
        std::string str_to_hash = std::string(input) + "-" + std::to_string(i);
        std::string hashed = knot_hash(str_to_hash.c_str()); 
        for (char c : hashed) {
            int n = int(c)-ASCII_OFFSET_TO_NUMS;
            if (n <= 9) ss << std::hex << utils::int_to_bin(n,4);
            else ss << std::hex << utils::int_to_bin(n - ASCII_OFFSET_TO_NUMS - 1 + 10,4);
        }
        for (int j = 0; j < GRID_SIZE; j++) {
            if (ss.str()[j] == '1') {
                grid[i][j] = true;
                ones++;
            } else {
                grid[i][j] = false;
            }
        }

    }

    int cliques_count = 0;
    for (int i = 0; i < 128; i++){
        for (int j = 0; j < 128; j++) {
            if (grid[i][j]) {
                cliques_count += lil_bfs(grid, i, j);
            }
        } 
    }
    
    std::cout << "Solution for part 1: " << ones << "\n";
    std::cout << "Solution for part 2: " << cliques_count << "\n";
    

    // freeing memory
    for (int i = 0; i < GRID_SIZE; i++) {
        free(grid[i]);
    }
    delete[] grid;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
int lil_bfs(bool **grid, int row, int col) {
    if (!grid[row][col]) return 0;
    std::queue<std::pair<int, int>> q;
    q.push(std::pair(row, col));
    std::unordered_set<int> visited;
    int r, c;
    while (!q.empty()) {
        r = q.front().first;
        c = q.front().second;
        q.pop();
        //std::cout << "( " << r << ", " << c << ") ";
        grid[r][c] = false;
        // using rows*width+cols once pair<int,int> is not hashable
        if (visited.find(r * GRID_SIZE + c) != visited.end())
            continue;
        visited.insert(r * GRID_SIZE + c);  
        if (r - 1 >= 0 && grid[r-1][c] == true) 
            q.push(std::pair(r-1, c));
        if (r + 1 < GRID_SIZE && grid[r+1][c] == true) 
            q.push(std::pair(r+1, c));
        if (c - 1 >= 0 && grid[r][c-1] == true) 
            q.push(std::pair(r, c-1));
        if (c + 1 < GRID_SIZE && grid[r][c+1] == true) 
            q.push(std::pair(r, c+1));
    }
    return 1;
}

void make_knot(std::vector<int>& v, int pos, int len) {
    std::vector<int> tmp{};
    for (int i = pos; i < pos + len; i++) {
        tmp.push_back(v.at(i % SIZE));
    }
    std::reverse(tmp.begin(), tmp.end());
    for (int i = 0; i < len; i++) {
        v.at((pos + i) % SIZE) = tmp.at(i);
    }
}

void knot_hash_round(std::vector<int>& len_seq, std::vector<int>& str, int &pos, int &skip_size) {
    for (int len : len_seq) {
        make_knot(str, pos, len);
        pos += (len + skip_size++) % SIZE;
    }
}

std::string knot_hash(const char* str_to_hash) {
    std::vector<int> len_seq;
    int end_seq[] = { 17, 31, 73, 47, 23 };
    for (size_t i = 0; i < strlen(str_to_hash); i++) len_seq.push_back( (int) str_to_hash[i] );
    for (int es : end_seq) len_seq.push_back(es);
    
    std::vector<int> str_ints;
    for (int i = 0; i < SIZE; i++) str_ints.push_back(i);

    int pos = 0;
    int skip_size = 0;
    for (int i = 0; i < ROUNDS; i++) {
        knot_hash_round(len_seq, str_ints, pos, skip_size);
    }

    std::vector<int> dense_hash;
    
    for (int i = 0; i < 16; i++) {
        int base = str_ints[i * 16];
        for (int j = 1; j < 16; j++) {
            base ^= str_ints[i*16+j];
        }
        dense_hash.push_back(base);
    }
    
    std::stringstream ss;
    
    for (int n : dense_hash) ss << std::hex << std::setw(2) << std::setfill('0') << n;
    
    return ss.str();
}
