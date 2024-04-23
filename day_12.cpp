/*
    Advent of Code - 2017 
    Day 12: Digital Plumber

*/


#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_set>
#include <queue>


class Program {
public:
    int id;
    std::unordered_set<int> conns;

    Program(int id) {
        this->id = id;
    }

    void connect(int p) {
        this->conns.insert(p);
    }
};



std::vector<int> read_line(std::string line) {
    std::regex pattern("[0-9]+");
    std::sregex_iterator pattern_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
    std::sregex_iterator pattern_end = std::sregex_iterator();
    std::smatch m;
    std::vector<int> matches;
    for (std::sregex_iterator p = pattern_begin; p != pattern_end; p++) {
        std::smatch match = *p;
        matches.push_back(std::stoi(match.str()));
    }
    return matches;
}


std::unordered_set<int> bfs(std::vector<Program> &g, int start) {
    std::unordered_set<int> visited;
    std::queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        visited.insert(current);
        for (auto n : g[current].conns) {
            if (visited.find(n) == visited.end()) {
                q.push(n);
            }
        }
    }
    return visited; 

}


int solve_part_1(std::vector<Program> &g) {
    return bfs(g, 0).size(); 
}


int solve_part_2(std::vector<Program> &g) {
    int total_cliques = 0;
    std::unordered_set<int> all_visited;
    std::unordered_set<int> part_visited;

    for (int p = 0; p < g.size(); p++) {
        if (all_visited.find(p) == all_visited.end()) {
            total_cliques++;
            part_visited = bfs(g, p);
            for (auto n : part_visited) { all_visited.insert(n); }
        }
    }
    return total_cliques;
}



int main() {
    

    std::string line;
    std::vector<int> inputs;
    std::vector<Program> g;
    
    while (std::getline(std::cin, line)) {
        //std::cout << line << "\n";
        inputs = read_line(line);
        Program p(inputs[0]);
        for (int i = 1; i < inputs.size(); i++) {
            p.connect(inputs[i]);
        }
        g.push_back(p);
        
    }

    // part 1
    std::cout << "Solve part 1: " << solve_part_1(g);
    std::cout << "\nSolve part 2: " << solve_part_2(g);
    
    return 0;
}