#ifndef RAND_POS_SERVICE
#define RAND_POS_SERVICE
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>

class RandPosService
{
    public:
        /*! Método que verifica todas as posições validas do mapa e retorna uma escolhida aleatoriamente.
        * @param std::pair<int, int> dimensions: dimensões do mapa.
        * @param std::vector<std::vector<int>> graph: mapa.
        * @return std::pair<int, int>: posição valida no mapa.
 		*/
        static std::pair<int, int> getValidPos(std::pair<int, int> dimensions, std::vector<std::vector<int>> graph);
};

#endif