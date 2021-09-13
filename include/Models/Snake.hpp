#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <string>
#include <utility>

class Snake
{
    private:
        char value;
        std::pair<int, int> position;
        int lifes;
        int eaten;

    public:
        Snake(std::pair<int, int> position);
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight(); 
        void removeLife();
        void eat();
        char getValue();
        std::pair<int, int> getPosition();
        int getLifes();   
        int getEaten();
};

#endif