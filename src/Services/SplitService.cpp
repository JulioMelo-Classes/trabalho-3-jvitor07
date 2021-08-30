#include "Services/SplitService.hpp"

std::vector<int> SplitService::split(std::string line, char separator) {
    std::vector<int> result;
    std::string str;
    std::stringstream ss(line);

    while(std::getline(ss, str, separator)){
        result.push_back(std::stoi(str));
    }
    return result;
}