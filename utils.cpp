#include <vector>
#include <regex>
#include <cmath>
#include <algorithm>
#include "utils.h"


namespace utils {

    std::vector<std::string> search_all(std::string str, std::string str_pattern) {
        
        std::regex pattern(str_pattern);
        auto pattern_begin = std::sregex_iterator(str.begin(), str.end(), pattern);
        auto pattern_end  = std::sregex_iterator();
        std::smatch m;
        
        //size_t matches_size = std::distance(pattern_begin, pattern_end);

        std::vector<std::string> all_matches{};
        for (std::sregex_iterator p = pattern_begin; p != pattern_end; p++) {
            std::smatch match = *p;
            all_matches.push_back(match.str());
        }
        return all_matches;
    }

 
    std::vector<std::string> split_string(std::string str, std::string delimiter) {

        std::vector<std::string> splitted{};
        std::string token{};
        size_t pos = 0;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            splitted.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        token = str.substr(0, pos);
        splitted.push_back(token);
        return splitted;
    }

    std::string int_to_bin(int n, int pad) {
        int len = std::max(pad, (int) std::log2(n)+1);
        std::string bin(len, '0');
        while (n > 1) {
            bin[(int) std::log2(n)] = '1';
            n -= (int) std::pow(2, (int) std::log2(n));
        }
        bin[0] = n == 1 ? '1' : '0';
        std::reverse(bin.begin(), bin.end());
        return bin;
    }    


}