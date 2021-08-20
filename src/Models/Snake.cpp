#include "Models/Snake.hpp"

Snake::Snake(int row, int col) {
    this->posRow = row;
    this->posCol = col;
    this->length = 1;
    this->lifes = 5;
    this->value = '^';
}

std::pair<int, int> Snake::getCurrentPosition() {
    
    return {
        this->posRow,
        this->posCol
    };
}

void Snake::moveUp() {
    this->posRow -= 1;
    this->setValue('v');
}

void Snake::moveDown() {
    this->posRow += 1;
    this->setValue('^');
}

void Snake::moveLeft() {
    this->posCol -= 1;
    this->setValue('>');
}

void Snake::moveRight() {
    this->posCol += 1;
    this->setValue('<');
}

int Snake::getLength() {
    return this->length;
}

void Snake::increaseLength(int value) {
    this->length += value;
}

void Snake::setValue(char value) {
    this->value = value;
}

char Snake::getValue() {
    return this->value;
}