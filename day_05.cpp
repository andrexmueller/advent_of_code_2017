/*
    Advent of Code - 2017
    Day 5: A Maze of Twisty Trampolines, All Alike

*/


#include <iostream>
#include <vector>



int solve_problem(std::vector<int> maze, int part) {

    int steps = 0;
    int actual = 0;
    size_t next = actual + maze[actual];
    
    while (next < maze.size() && next >= 0) {
        if (part == 1) 
            maze[actual]++;
        if (part == 2)
            maze[actual] = maze[actual] >= 3 ? maze[actual] - 1 : maze[actual] + 1;
        actual = next;
        next = actual + maze[actual];
        steps++;
    }
    if (part == 1) 
            maze[actual]++;
    if (part == 2)
            maze[actual] = maze[actual] >= 3 ? maze[actual] - 1 : maze[actual] + 1;
    steps++;
    return steps;
}


int main() {

    std::vector<int> maze{};
    int jmp{0};

    while (std::cin >> jmp) {
        maze.push_back(jmp);
    }

    std::cout << "Solution for part 1: "<< solve_problem(maze, 1) << "\n";
    std::cout << "Solution for part 2: "<< solve_problem(maze, 2) << "\n";

    return 0;
}