#include <regex>
#include <string>


std::string replace(std::string input, std::string pattern_s ,std::string replaced){
    std::regex pattern(pattern_s); // Matches one or more digits
    std::string result = std::regex_replace(input, pattern, replaced);
    return result;
}
