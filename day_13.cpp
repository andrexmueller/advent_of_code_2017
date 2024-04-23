/*
    Advent of Code - 2017 
    Day 13: Packet Scanners

*/


#include <iostream>
#include <string>
#include <vector>

class Layer {
public:
    int id;
    int depth;

    Layer(int id, int depth) {
        this->id = id;
        this->depth = depth;
    }
    
    int get_position(int time) {
        int direction = (time / (this->depth-1)) % 2; // if even -->, if odd <--
        int steps = time % (this->depth-1);
        return direction == 0 ? steps : this->depth - 1 - steps; 
    }

};


Layer read_input_line(std::string line) {
    int id = std::stoi(line);
    int depth = std::stoi(line.substr(line.find(":")+2));
    Layer layer(id, depth);    
    return layer;
}


void solve_part_1(const std::vector<Layer>& layers) {
    int severity = 0;
    for (auto layer : layers) {
        if (layer.get_position(layer.id) == 0) {
            severity += layer.id * layer.depth;
        }
    }
    std::cout << "Solution for part 1: " << severity << std::endl;
}


bool send_packet(const std::vector<Layer>& layers, int delay) {
    for (auto layer : layers) {
        if (layer.get_position(layer.id + delay) == 0) return false;
    }
    return true;
}


void solve_part_2(const std::vector<Layer>& layers) {

    int delay = 0;
    while (!send_packet(layers, delay)) {
        delay++;
    }
    std::cout << "Solution for part 2: " << delay << std::endl;
}



int main() {

    std::vector<Layer> layers; 

    std::string line;
    while (std::getline(std::cin, line)) {
        Layer layer = read_input_line(line);
        layers.push_back(layer);
    }

    solve_part_1(layers);
    solve_part_2(layers);

    return 0;
}