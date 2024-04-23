#ifndef UTILS_H
#define UTILS_h

#include <string>
#include <vector>


namespace utils {

    
    std::vector<std::string> search_all(std::string str, std::string str_pattern); 
    std::vector<std::string> split_string(std::string str, std::string delimiter);
    std::string int_to_bin(int n, int pad); 

}



#endif
