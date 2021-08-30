#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <utility>

class Snake
{
    private:
        char value; 
        std::pair<int, int> pos;
        int length;
        int lifes;

    public:
        Snake(std::pair<int, int> pos);
        void increaseLength();
        void removeLife();
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        bool gameIsOver();
        void resetBaseStatus();
        std::pair<int, int> getPos();
        int getLength();
        int getLifes();
        char getValue();
};

#endif