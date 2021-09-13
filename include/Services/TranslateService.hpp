#ifndef TRANSLATE_SERVICE_HPP
#define TRANSLATE_SERVICE_HPP

#include<string>
#include <vector>
#include<utility>

class TranslateService
{
    public:
        /*! Método converte um vetor de strings em uma matriz de numeros.
            * @param std::pair<int, int> dimensions: dimensões do mapa.
            * @param cstd::vector<std::string> maze: vetor de string.
            * @return std::vector<std::vector<int>>: matriz com os valores convertidos.
 		*/
        static std::vector<std::vector<int>> translate(std::pair<int, int> dimensions, std::vector<std::string> maze);
};

#endif