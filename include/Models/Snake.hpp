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
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
};

#endif