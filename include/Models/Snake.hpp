#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <utility>

class Snake 
{
    private: 
        int posRow;
        int posCol;
        int length;

    public: 
        Snake(int row, int col);
        
        /**
         * Função para pegar a posição atual da cabeça da cobra
         * @return std::pair<int, int> { linha, coluna } 
         */ 
        std::pair<int, int> getCurrentPosition();

        /**
         * Função que movimenta para cima.
         */ 
        void moveUp();
        
        /**
         * Função que movimenta para baixo.
         */ 
        void moveDown();

        /**
         * Função que movimenta para esquerda.
         */ 
        void moveLeft();

        /**
         * Função que movimenta para direita.
         */ 
        void moveRight();

        /**
         * Função que pega o tamanho atual.
         * @return int valor do tamanho
         */ 
        int getLength();
        
        /**
         * Função aumenta o tamanho.
         * @param int value = 1(valor default de 1), valor que devera ser aumentado no tamanho
         */ 
        void increaseLength(int value = 1);
};

#endif