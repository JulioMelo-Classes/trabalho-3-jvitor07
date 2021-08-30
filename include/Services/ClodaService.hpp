#ifndef CLODA_SERVICE_HPP
#define CLODA_SERVICE_HPP

#include <utility>
#include <vector>

class ClodaService
{
    private:
        std::pair<int, int> dimensions;
        std::vector<std::vector<int>> graph;

    public:
        ClodaService(std::pair<int, int> dimensions, std::vector<std::vector<int>> graph);
        std::vector<std::pair<int, int>> findWay(std::pair<int, int> posBegin, std::pair<int, int> posEnd);
    private:
        bool posIsValid(std::pair<int, int> pos);
        bool posWasVisited(std::pair<int, int> pos, std::vector<std::pair<int, int>> &visited);
        bool itsNeighbors(std::pair<int, int> posOne, std::pair<int, int> posTwo);
        bool solveGraph(std::pair<int, int> posBegin, std::pair<int, int> posEnd, std::vector<std::pair<int, int>> &visited, std::vector<std::pair<int, int>> &path);
};

#endif