/*

Advent of Code - 2017
Day 2: Corruption Checksum

*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

vector<int>* read_line(string s) {
    vector<int> *v = new vector<int>;
    int i = 0;
    int x;

    while (i < s.length()) {
        if (isdigit(s[i])) {
            x = atoi(&s[i]);
            v->push_back(x);
            i += log10(x) + 1;
        }
        i++;
    }
    return v;
}


int main() {

    
    ifstream f;

    f.open("in02.txt");
    string line;


    int solution_part_1 = 0;
    int solution_part_2 = 0;

    while (getline(f, line)) {
        vector<int> *v = read_line(line);
        int max = numeric_limits<int>::min();
        int min = numeric_limits<int>::max();
        for (int i = 0; i < v->size(); i++) {
            if (v->at(i) > max) max = v->at(i);
            if (v->at(i) < min) min = v->at(i);
        }
        solution_part_1 += max - min;

        for (int i = 0; i < v->size(); i++)            
            for (int j = 0; j < v->size(); j++)
                if (v->at(i) % v->at(j) == 0 && i != j)
                    solution_part_2 += v->at(i) / v->at(j);

        delete v;      
                        
    }

    cout << "Solution for part 1: " << solution_part_1 << endl;
    cout << "Solution for part 2: " << solution_part_2 << endl;

    f.close();
    return 0;
}