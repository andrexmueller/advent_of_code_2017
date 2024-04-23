/*
    Advent of Code - 2017 
    Day 10: Knot Hash

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

#define SIZE 256
#define ROUNDS 64

int solve_part_1(std::vector<int> inputs); 
void solve_part_2(void); 
void make_knot(std::vector<int>& v, int pos, int len);
void knot_hash_round(std::vector<int>& len_seq, std::vector<int>& str, int &pos, int &skip_size);




int main() {

    std::vector<int> inputs = { 120, 93, 0, 90, 5, 80, 129, 74, 1, 165, 204, 255, 254, 2, 50, 113 };
    std::cout << "Solution for part 1: " << solve_part_1(inputs) << std::endl;
    solve_part_2();
    return 0;
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


int solve_part_1(std::vector<int> inputs) {
    std::vector<int> str;
    for (int i = 0; i < SIZE; i++) str.push_back(i);
    int pos = 0;
    int skip_size = 0;
    knot_hash_round(inputs, str, pos, skip_size);
    return str[0] * str[1];
}

void solve_part_2(void) {
    char len_seq_char[] = "120,93,0,90,5,80,129,74,1,165,204,255,254,2,50,113";
    std::vector<int> len_seq;
    int end_seq[] = { 17, 31, 73, 47, 23 };
    for (int i = 0; i < strlen(len_seq_char); i++) len_seq.push_back((int)len_seq_char[i]);
    for (int es : end_seq) len_seq.push_back(es);
    
    std::vector<int> str;
    for (int i = 0; i < SIZE; i++) str.push_back(i);

    int pos = 0;
    int skip_size = 0;
    for (int i = 0; i < ROUNDS; i++) {
        knot_hash_round(len_seq, str, pos, skip_size);
    }

    std::vector<int> dense_hash;
    for (int i = 0; i < 16; i++) {
        int base = str[i * 16];
        for (int j = 1; j < 16; j++) {
            base ^= str[i*16+j];
        }
        dense_hash.push_back(base);
    }

    std::cout << "\nSolution for part 2: ";
    for (int n : dense_hash) printf("%02x", n);

}


