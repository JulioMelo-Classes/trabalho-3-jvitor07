#include "Services/RandPosService.hpp"

std::pair<int, int> RandPosService::getValidPos(std::pair<int, int> dimensions, std::vector<std::vector<int>> graph) {
    std::vector<std::pair<int, int>> positions;

    for(int row = 0; row < dimensions.first; row++) {
        for(int col = 0; col < dimensions.second; col++) {
            if(graph[row][col] != 1000) positions.push_back({row, col});
        }
    }

    srand(time(0));
    int randNumber = rand()%positions.size();

    return positions[randNumber];
}