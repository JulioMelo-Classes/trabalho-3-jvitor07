#include "Models/Snake.hpp"

Snake::Snake(int row, int col) {
    this->posRow = row;
    this->posCol = col;
    this->length = 1;
}

std::pair<int, int> Snake::getCurrentPosition() {
    
    return {
        this->posRow,
        this->posCol
    };
}

void Snake::moveUp() {
    this->posRow -= 1;
}

void Snake::moveDown() {
    this->posRow += 1;
}

void Snake::moveLeft() {
    this->posCol -= 1;
}

void Snake::moveRight() {
    this->posCol += 1;
}