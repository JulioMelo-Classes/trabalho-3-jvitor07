#include <iostream>
#include "SnakeGame.h"
#include "Models/Snake.hpp"

using namespace std;

int main(int argc, char *argv[]){

    Snake *snake = new Snake(0, 5);
    std::cout << "INICIO: " << "ROW: " << snake->getCurrentPosition().first << " COL: " << snake->getCurrentPosition().second << std::endl;
    snake->moveRight();
    std::cout << "moveu direita: " << "ROW: " << snake->getCurrentPosition().first << " COL: " << snake->getCurrentPosition().second << std::endl;
    snake->moveDown();
    std::cout << "moveu baixo: " << "ROW: " << snake->getCurrentPosition().first << " COL: " << snake->getCurrentPosition().second << std::endl;

    std::cout << "tamanho 01: " << snake->getLength() << std::endl;
    snake->increaseLength();
    std::cout << "tamanho 02: " << snake->getLength() << std::endl;
    snake->increaseLength(5);
    std::cout << "tamanho 03: " << snake->getLength() << std::endl; 

    //SnakeGame game;
    //game.loop(); //bloqueia aqui e só saí quando o jogo termina

    return 0;
}