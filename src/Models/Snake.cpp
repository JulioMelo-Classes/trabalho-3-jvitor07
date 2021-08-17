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