/*
    Advent of Code - 2017 
    Day 11: Hex Ed

*/


#include <iostream>
#include <string>
#include <unordered_set>

#define abs(x) ((x) >= 0 ? (x) : -(x))
#define min(x,y) ((x) <= (y) ? (x) : (y))

typedef struct point_t {
    int x;
    int y;
} point_t;


void move_point(point_t &p, std::string direction) {

    if (direction == "n") p.y += 2;
    if (direction == "s") p.y -= 2;
    if (direction == "ne") { p.x++; p.y++; }
    if (direction == "nw") { p.x--; p.y++; }
    if (direction == "se") { p.x++; p.y--; }
    if (direction == "sw") { p.x--; p.y--; }
    
}

void print_point(point_t& p) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
}

int norm(point_t p) {
    int diagonal = min(abs(p.x), abs(p.y));
    int horizontal = abs(p.x) != diagonal ? (abs(p.x) - diagonal) / 2 : 0;
    int vertical = abs(p.y) != diagonal ? (abs(p.y) - diagonal) / 2 : 0;
    return diagonal + horizontal + vertical;
}


int main() {
    
    std::string line;
    std::getline(std::cin, line);
    
    point_t p = { 0, 0 };
    int farest = 0;
    int actual_dist;

    std::string move;
    int pos = 0;
    
    while ((pos=line.find(',')) != std::string::npos) {
        move = line.substr(0, pos);
        move_point(p, move);
        actual_dist = norm(p);
        if (actual_dist > farest) { farest = actual_dist; }
        line.erase(0, pos + 1);
    }
    move = line.substr(0, pos);
    move_point(p, move);
    actual_dist = norm(p);
    if (actual_dist > farest) { farest = actual_dist; }
    print_point(p);
    std::cout << "Solution for part 1: " << norm(p) << std::endl;
    std::cout << "Solution for part 2: " << farest;
   

}


