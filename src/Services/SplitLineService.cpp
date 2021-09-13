#include "Services/SplitLineService.hpp"

std::map<std::string, int> SplitLineService::split(std::string line, char separator) {
    std::map<std::string, int> result;
    std::vector<int> arr;
    std::string str;
    std::stringstream ss(line);

    while(std::getline(ss, str, separator)){
        arr.push_back(std::stoi(str));
    }

    result.insert({"rows", arr[0]});
    result.insert({"cols", arr[1]});
    result.insert({"foods", arr[2]});

    return result;
}