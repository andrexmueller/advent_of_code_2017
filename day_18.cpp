#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <queue>

typedef struct comm_t {
    std::string comm;
    std::string x;
    std::string y;
} comm_t;


class Thread;

class Thread {
public:
    std::vector<comm_t> instructions{};
    Thread* other = NULL;
    std::unordered_map<std::string, long long> registers{};
    std::queue<long long> received{};
    int cursor{}, send_count{};

    Thread(std::vector<comm_t> insts, int id) {
        instructions = insts;
        cursor = 0;
        send_count = 0;

        for (auto &i : instructions) {
            auto [_, x, y] = i;
            if (registers.find(x) == registers.end()) {
                if (x != "" && !std::isalpha(x[0])) {
                    registers[x] = std::stol(x);
                } else {
                    registers[x] = 0;
                }
            }

            if (registers.find(y) == registers.end()) {
                if (y != "" && !std::isalpha(y[0])) {
                    registers[y] = std::stol(y);
                } else {
                    registers[y] = 0;
                }
            }
        }
        registers["p"] = id;
    }

    void run() {
        int offset;
        
        while (true) {
            offset = 0;
            auto [c, x, y] = instructions[cursor];
            
            if (c == "snd") {
                other->received.push(registers[x]);
                send_count++;
            } else if (c == "set") {
                registers[x] = registers[y];
            } else if (c == "add") {
                registers[x] += registers[y];
            } else if (c == "mul") {
                registers[x] *= registers[y];
            } else if (c == "mod") {
                registers[x] %= registers[y];
            } else if (c == "jgz") {
                if (registers[x] > 0) {
                    offset += registers[y] - 1;
                }
            } else {
                if (received.size() > 0) {
                    registers[x] = received.front();
                    received.pop();
                } else {
                    //return cursor;
                    return;
                }
            }
            cursor += offset + 1;
            if (cursor < 0 || cursor >= (int) instructions.size()) {
                //return cursor;
                return;
            }
        }
    }
};



void solve_part_1(const std::vector<comm_t> &program);
void solve_part_2(const std::vector<comm_t> &program);


int main() {

    std::ifstream f;
    f.open("../in18.txt");
    std::string line;
    std::vector<comm_t> program;
    
    while (std::getline(f, line)) {
        comm_t comm;
        std::string c = line.substr(0,3);
        line.erase(0, 4);
        comm.comm = c;
        std::string x = line.substr(0, line.find(" "));
        line.erase(0, x.size()+1);    
        comm.x = x;
        if (line.size() > 0) {
            comm.y = line;
        }
        else
            comm.y = "";
        program.push_back(comm);
    }

    solve_part_1(program);
    solve_part_2(program);

    f.close();
    return 0;
}

void solve_part_1(const std::vector<comm_t> &program) {
    
    std::unordered_map<std::string, long long> registers;
    int last_played_sound = 0;
    int cursor = 0;
    int offset = 0;
    
    while (true) {
        auto [c, x, y] = program[cursor];
        offset = 0;
        
        // populate the registers map
        if (registers.find(x) == registers.end()) {
            if (x != "" && !std::isalpha(x[0])) {
                registers[x] = std::stol(x);
            } else {
                registers[x] = 0;
            }
        }
        
        if (registers.find(y) == registers.end()) {
            if (y != "" && !std::isalpha(y[0])) {
                registers[y] = std::stol(y);
            } else {
                registers[y] = 0;
            }
        }
        
        
        if (c == "snd") {
            last_played_sound = registers[x];
        } else if (c == "set") {
            registers[x] = registers[y];
        } else if (c == "add") {
            registers[x] += registers[y];
        } else if (c == "mul") {
            registers[x] *= registers[y];
        } else if (c == "mod") {
            registers[x] %= registers[y];
        } else if (c == "jgz") {
            if (registers[x] > 0) {
                offset += registers[y] - 1;
            }
        } else {
            if (registers[x] != 0) {
                std::cout << "Solution for part 1: " << last_played_sound << std::endl;
                return;
            }
        }
        cursor += offset + 1;
    }
}

void solve_part_2(const std::vector<comm_t> &program) {

    Thread th0(program, 0);
    Thread th1(program, 1);
    th0.other = &th1;
    th1.other = &th0;

    while (true) {
        th0.run();
        th1.run();
        if (th0.received.size() == 0 && th1.received.size() == 0) 
            break;
    }
    std::cout << "Solution for part 2: " << th1.send_count << std::endl;

}