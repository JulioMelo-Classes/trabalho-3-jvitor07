#include "Services/TranslateService.hpp"

std::vector<std::vector<int>> TranslateService::translate(std::pair<int, int> dimensions, std::vector<std::string> maze) {
    std::vector<std::vector<int>> graph;

    for(auto itRow = maze.begin(); itRow != maze.end(); itRow++) {
        std::vector<int> row;
        for(auto itCol = itRow->begin(); itCol != itRow->end(); itCol++) {
            if(*itCol == ' ') row.push_back(1);
            if(*itCol == '#' || *itCol == '.' || *itCol == 'o') row.push_back(1000);
        }
        graph.push_back(row);
    }

    return graph;
}