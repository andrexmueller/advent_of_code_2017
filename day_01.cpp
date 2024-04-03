/*

Advent of Code - 2017
Day 1: Inverse Captcha

*/


#include <iostream>
#include <fstream>

using namespace std;

int main() {

    
    ifstream f;

    f.open("in01.txt");
    string line;
    getline(f, line);

    int total = 0;
    for (int i = 0; i < line.length(); i++) 
        if (line[i] == line[(line.length()-1+i) % line.length()])
            total += (int)line[i] - '0';

    cout << "Solution for part 1: " << total << endl;

    
    total = 0;
    for (int i = 0, j = line.length() / 2; i < line.length(); i++, j++) 
        if (line[i] == line[j%line.length()])
            total += (int)line[i] - '0';



    cout << "Solution for part 2: " << total << endl;
    f.close();
    return 0;
}