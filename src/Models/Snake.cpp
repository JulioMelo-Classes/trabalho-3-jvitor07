#include "Models/Snake.hpp"

Snake::Snake(std::pair<int, int> position) {
    this->value = '<';
    this->lifes = 5;
    this->eaten = 0;
    this->position = position;
}

void Snake::moveUp()
{
    this->position.first -= 1;
    this->value = 'v';
}

void Snake::moveDown()
{
    this->position.first += 1;
    this->value = '^';
}

void Snake::moveLeft()
{
    this->position.second -= 1;
    this->value = '>';
}

void Snake::moveRight()
{
    this->position.second += 1;
    this->value = '<';
}

void Snake::removeLife()
{
    this->lifes -= 1;
}

void Snake::eat()
{
    this->eaten += 1;
}

char Snake::getValue()
{
    return this->value;
}

std::pair<int, int> Snake::getPosition()
{
    return this->position;
}

int Snake::getLifes()
{
    return this->lifes;
}   

int Snake::getEaten()
{
    return this->eaten;
}
