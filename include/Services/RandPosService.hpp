#ifndef RAND_POS_SERVICE
#define RAND_POS_SERVICE
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>

class RandPosService
{
    public:
        static std::pair<int, int> getValidPos(std::pair<int, int> dimensions, std::vector<std::vector<int>> graph);
};

#endif