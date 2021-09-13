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

        /*! Encontra o caminho da posição atual de cobra para a comida
			@param pair com a posição inicial da cobra.
			@param pair com a posição que a cobra deve ir.
			@return um vetor de pares com caminho que deve ser seguido.
		*/
        std::vector<std::pair<int, int>> findWay(std::pair<int, int> posBegin, std::pair<int, int> posEnd);
    private:
        /*! Verifica se a posição é válida
			@param pair com a posição a ser verificada.
			@return verdadeiro se for válida ou falso se não for.
		*/
        bool posIsValid(std::pair<int, int> pos);

        /*! Verifica se a posição ja foi visitada
			@param pair com a posição a ser verificada.
            @param vector de pares com as posições visitadas.
			@return verdadeiro se ja foi visitada ou falso se não foi.
		*/
        bool posWasVisited(std::pair<int, int> pos, std::vector<std::pair<int, int>> &visited);

        /*! Verifica se as posições são vizinhas
			@param pair com umas das posições.
            @param pair com a outra posição.
			@return verdadeiro se são vizinhas ou falso se não.
		*/
        bool itsNeighbors(std::pair<int, int> posOne, std::pair<int, int> posTwo, std::vector<std::pair<int, int>> &visited);

        /*! Verifica se as posições são vizinhas
			@param pair com a posição inicial.
            @param pair com a posição destino.
            @param vector de pares com as posições visitadas.
            @param vector de pares com as posições que devem ser seguidas.
			@return verdadeiro se tiver caminho para o destino ou falso se não.
		*/
        bool solveGraph(std::pair<int, int> posBegin, std::pair<int, int> posEnd, std::vector<std::pair<int, int>> &visited, std::vector<std::pair<int, int>> &path);
};

#endif