#include <vector>
#include <regex>

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


}
    


