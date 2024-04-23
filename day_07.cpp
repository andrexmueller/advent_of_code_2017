/*
    Advent of Code - 2017
    Day 7: Recursive Circus
*/


#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include "utils.h"


class Node {
public:

    std::string name;
    int weight{};
    int total_weight{};
    std::string parent{};
    std::vector<Node*> children{};
    int dif{};

    Node(std::string name) {
        this->name = name;
    }

    void set_weight(int weight) {
        this->weight = weight;
    }
    
    void set_parent(std::string parent) {
        this->parent = parent;
    }

    void add_child(Node *child) {
        this->children.push_back(child);
    }

    int eval_total_weight() {
        this->total_weight = this->weight;
        if (this->children.size() == 0) {
            //this->total_weight = this->weight;
            return this->total_weight;
        }

        for (auto c : this->children) {
            this->total_weight += c->eval_total_weight();
        }

        return this->total_weight;
    }

    bool is_balanced() {
        if (this->children.size() <= 1) return true;
        for (int i = 1; i < this->children.size(); i++) {
            if (this->children[0]->total_weight != this->children[i]->total_weight) {
                this->dif = this->children[0]->weight - this->children[i]->weight;
                return false;
            }

        }
        return true;
    }

    void print_chidren_weights() {
        std::cout << " ( ";
        for (auto n : this->children)
            std::cout << n->total_weight << " ";
        std::cout << ")\n";
        
    }

    void print_node() {
        std::cout << "Node <" << this->name << "> with wight = " << this->weight << " " << this->total_weight;
        std::cout << "  - Children: [ ";
        for (auto n : this->children) std::cout << n->name << ", ";
        std::cout << "]\n";
    }


};


void find_unbalanced_node(Node *node, std::string &unbal_name) {
    // find the unbalanced node that is the farest from the root

    if (node->children.size() == 0) return;
    for (auto n : node->children) {
        find_unbalanced_node(n, unbal_name);
    }
    if (!node->is_balanced() && unbal_name == "") {
        //std::cout << "unbalanced node : " << node->name << std::endl; 
        unbal_name = node->name;
    }


}


int main() {

    std::unordered_map<std::string, Node*> all_nodes{};

    std::string line{};
    
    while (std::getline(std::cin, line)) {
        
        std::vector<std::string> node_info = utils::search_all(line, "[a-z0-9]+");    
            
        if (all_nodes.find(node_info[0]) == all_nodes.end()) { // checks if node doesn't exist
            Node *n = new Node(node_info[0]);
            all_nodes[node_info[0]] = n;            
        }
        
        all_nodes[node_info[0]]->set_weight(std::stoi(node_info[1]));

        if (node_info.size() > 2) { // if has children
            for (int i = 2; i < (int)node_info.size(); i++) {
                if (all_nodes.find(node_info[i]) == all_nodes.end()) {
                    Node *child = new Node(node_info[i]);
                    all_nodes[node_info[i]] = child;
                    all_nodes[node_info[0]]->add_child(child);    
                } else {
                    all_nodes[node_info[0]]->add_child(all_nodes[node_info[i]]);
                }
                all_nodes[node_info[i]]->set_parent(node_info[0]);         
            }
        }
    }

    // get root
    Node *root = NULL;
    for (auto n : all_nodes) {
        if (n.second->parent == "")
            root = n.second;
    }

    std::cout << "Solution for part 1: " << root->name << std::endl ;
    //root->print_node();

    root->eval_total_weight();

    // find unbalanced node
    std::string unbal = "";
    find_unbalanced_node(root, unbal);
    
    //all_nodes[unbal]->print_node();
    
    Node *unbalanced_node = all_nodes[unbal];
    
    // search for the child with different weight
    int diff = 0;
    for (int i = 1; i < unbalanced_node->children.size(); i++) {

        if (unbalanced_node->children[i]->total_weight - unbalanced_node->children[i-1]->total_weight != 0) {
            diff = unbalanced_node->children[i]->total_weight - unbalanced_node->children[i-1]->total_weight;
        }
    }

    // once the absolute difference is found, verify new balance
    for (auto n : unbalanced_node->children) {
        unbal = "";
        n->set_weight(n->weight+diff);
        root->eval_total_weight();
        find_unbalanced_node(root, unbal);
        if (unbal == "") { // got the tree ballanced, ie, found the real unbalanced node
            std::cout << "Solution for part 2: " << n->weight << "\n";
            break;
        } else {
            // reset n
            n->set_weight(n->weight-diff);
        }
    }

    return 0;
}



