#include <iostream>
#include "SnakeGame.h"
#include "Models/Snake.hpp"

using namespace std;

int main(int argc, char *argv[]){

    Snake *snake = new Snake(0, 5);
    std::cout << "ROW: " << snake->getCurrentPosition().first << " COL: " << snake->getCurrentPosition().second << std::endl;

    //SnakeGame game;
    //game.loop(); //bloqueia aqui e só saí quando o jogo termina

    return 0;
}