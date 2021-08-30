#include "Models/Snake.hpp"

Snake::Snake(std::pair<int, int> pos) {
    this->pos = pos;
    this->length = 1;
    this->lifes = 3;
    this->value = '^';
}

void Snake::increaseLength() {
    this->length += 1;
}

void Snake::removeLife() {
    this->lifes -= 1;
}

void Snake::moveUp() {
    this->pos.first -= 1;
    this->value = 'v';
}

void Snake::moveDown() {
    this->pos.first += 1;
    this->value = '^';
}

void Snake::moveRight() {
    this->pos.second += 1;
    this->value = '<';
}

void Snake::moveLeft() {
    this->pos.second -= 1;
    this->value = '>';
}

bool Snake::gameIsOver() {
    return this->lifes == 0;
}

void Snake::resetBaseStatus() {
    this->length = 1;
    this->lifes = 5;
}

std::pair<int, int> Snake::getPos() {
    return this->pos;
}   

int Snake::getLength() {
    return this->length;
}

int Snake::getLifes() {
    return this->lifes;
}

char Snake::getValue() {
    return this->value;
}