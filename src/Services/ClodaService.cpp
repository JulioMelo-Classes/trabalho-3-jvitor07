#include "Services/ClodaService.hpp"

ClodaService::ClodaService(std::pair<int, int> dimensions, std::vector<std::vector<int>> graph) {
    this->dimensions = dimensions;
    this->graph = graph;
}

bool ClodaService::posIsValid(std::pair<int, int> pos) {
    return pos.first <= 0 && pos.first < this->dimensions.first && pos.second <= 0 && pos.second < this->dimensions.second;
}

bool ClodaService::posWasVisited(std::pair<int, int> pos, std::vector<std::pair<int, int>> &visited) {
    for(auto it = visited.begin(); it != visited.end(); it++) {
        if(it->first == pos.first && it->second == pos.second) return true;
    }

    return false;
}

bool ClodaService::itsNeighbors(std::pair<int, int> posOne, std::pair<int, int> posTwo) {
    return (posOne.first == posTwo.first + 1 && posOne.second == posTwo.second) || (posOne.first == posTwo.first - 1 && posOne.second == posTwo.second) || (posOne.first == posTwo.first && posOne.second == posTwo.second + 1) || (posOne.first == posTwo.first && posOne.second == posTwo.second - 1);
}

bool ClodaService::solveGraph(std::pair<int, int> posBegin, std::pair<int, int> posEnd, std::vector<std::pair<int, int>> &visited, std::vector<std::pair<int, int>> &path) {
    if(posBegin.first == posEnd.first && posBegin.second == posEnd.second) {
        path.push_back(posBegin);
        return true;
    }

    visited.push_back(posBegin);
    for(int row = 0; row < this->dimensions.first; row++) {
        for(int col = 0; col < this->dimensions.second; col++) {
            if(!this->posWasVisited({row, col}, visited) && this->graph[row][col] != 1000 && this->itsNeighbors(posBegin, {row, col})) {
                if(this->solveGraph({row, col}, posEnd, visited, path)) {
                    path.push_back(posBegin);
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<std::pair<int, int>> ClodaService::findWay(std::pair<int, int> posBegin, std::pair<int, int> posEnd) {
    std::vector<std::pair<int, int>> visited;
    std::vector<std::pair<int, int>> path;
    this->solveGraph(posBegin, posEnd, visited, path);

    return path;
}