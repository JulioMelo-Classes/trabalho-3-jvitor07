#include "SnakeGame.h"

#include <iostream>
#include <fstream>
#include "Services/randNumberService.hpp"
#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep

using namespace std;

SnakeGame::SnakeGame(){
    choice = "";
    frameCount = 0;
    initialize_game();
}

void SnakeGame::initialize_game(){
    //carrega o nivel ou os níveis
    ifstream levelFile("data/maze1.txt"); //só dá certo se o jogo for executado dentro da raíz do diretório (vc vai resolver esse problema pegando o arquivo da linha de comando)
    int lineCount = 0;
    string line;
    if(levelFile.is_open()){
        while(getline(levelFile, line)){ //pega cada linha do arquivo
            if(lineCount > 0){ //ignora a primeira linha já que ela contem informações que não são uteis para esse exemplo
                maze.push_back(line);
            }
            lineCount++;
        }
    }
    state = RUNNING;
}



void SnakeGame::process_actions(){
    //processa as entradas do jogador de acordo com o estado do jogo
    //nesse exemplo o jogo tem 3 estados, WAITING_USER, RUNNING e GAME_OVER.
    //no caso deste trabalho temos 2 tipos de entrada, uma que vem da classe Player, como resultado do processamento da IA
    //outra vem do próprio usuário na forma de uma entrada do teclado.
    switch(state){
        case WAITING_USER: //o jogo bloqueia aqui esperando o usuário digitar a escolha dele
            cin>>std::ws>>choice;
            break;
        default:
            //nada pra fazer aqui
            break;
    }
}

void SnakeGame::update(){
    //atualiza o estado do jogo de acordo com o resultado da chamada de "process_input"
    switch(state){
        case RUNNING:
            if(frameCount>0 && frameCount%10 == 0) //depois de 10 frames o jogo pergunta se o usuário quer continuar
                state = WAITING_USER;
            break;
        case WAITING_USER: //se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
            if(choice == "n"){
                state = GAME_OVER;
                game_over();
            }
            else{
                //pode fazer alguma coisa antes de fazer isso aqui
                state = RUNNING;
            }
            break;
        default:
            //nada pra fazer aqui
            break;
    }
}

/**
 * @brief função auxiliar para fazer o programa esperar por alguns milisegundos
 * @param ms a quantidade de segundos que o programa deve esperar
 */
void wait(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}

/**
 * @brief função auxiliar para limpar o terminal
 */
void clearScreen(){
//some C++ voodoo here ;D
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

void SnakeGame::render(){
    clearScreen();
    switch(state){
        case RUNNING:
            //desenha todas as linhas do labirinto
            for(auto line : maze){
                cout<<line<<endl;
            }
            break;
        case WAITING_USER:
            cout<<"Você quer continuar com o jogo? (s/n)"<<endl;
            break;
        case GAME_OVER:
            cout<<"O jogo terminou!"<<endl;
            break;
    }
    frameCount++;
}

void SnakeGame::game_over(){
}

bool SnakeGame::itsPossible(std::pair<int, int> cords) {
    return !(cords.first < 0) && !(cords.second < 0) && !(cords.first > this->maze.size()) && !(cords.second > (this->maze.at(cords.first)).size()) 
    && !(this->maze[cords.first][cords.second] == '#') && !(this->maze[cords.first][cords.second] == '.') && !((this->maze[cords.first][cords.second] == 'o'));
}

void SnakeGame::putElement(char value, std::pair<int, int> pos) {
    bool status = this->itsPossible(pos);

    if(status) {
        this->maze[pos.first][pos.second] = value;
    }
}

void SnakeGame::removeElement(std::pair<int, int> pos) {
    bool status = this->itsPossible(pos);

    if(status) {
        this->maze[pos.first][pos.second] = ' ';
    }
}

void SnakeGame::movePlayerUp(Snake *snake) {
    std::pair<int, int> pos = snake->getCurrentPosition();

    bool currentStatus = this->itsPossible(pos);
    bool nextPositionStatus = this->itsPossible({pos.first - 1, pos.second});

    if(currentStatus && nextPositionStatus) {
        this->removeElement(pos);
        snake->moveUp();
        this->putElement(snake->getValue(), snake->getCurrentPosition());
    }
}

void SnakeGame::movePlayerDown(Snake *snake) {
    std::pair<int, int> pos = snake->getCurrentPosition();

    bool currentStatus = this->itsPossible(pos);
    bool nextPositionStatus = this->itsPossible({pos.first + 1, pos.second});

    if(currentStatus && nextPositionStatus) {
        this->removeElement(pos);
        snake->moveDown();
        this->putElement(snake->getValue(), snake->getCurrentPosition());
    }
}

void SnakeGame::movePlayerLeft(Snake *snake) {
    std::pair<int, int> pos = snake->getCurrentPosition();

    bool currentStatus = this->itsPossible(pos);
    bool nextPositionStatus = this->itsPossible({pos.first, pos.second - 1});

    if(currentStatus && nextPositionStatus) {
        this->removeElement(pos);
        snake->moveLeft();
        this->putElement(snake->getValue(), snake->getCurrentPosition());
    }
}

void SnakeGame::movePlayerRight(Snake *snake) {
    std::pair<int, int> pos = snake->getCurrentPosition();

    bool currentStatus = this->itsPossible(pos);
    bool nextPositionStatus = this->itsPossible({pos.first, pos.second + 1});

    if(currentStatus && nextPositionStatus) {
        this->removeElement(pos);
        snake->moveRight();
        this->putElement(snake->getValue(), snake->getCurrentPosition());
    }
}

void SnakeGame::setFood() {
    std::vector<std::pair<int, int>> points;
    int row = 0;
    for(auto itRow = this->maze.begin(); itRow != this->maze.end(); itRow++) {
        
        int col = 0;
        for(auto itCol = itRow->begin(); itCol != itRow->end(); itCol++) {
            if(this->itsPossible({row, col})) {
                points.push_back({row, col});
            }
            col++;
        }
        row++;
    }

    int value = randNumberService::generateNumber(0, points.size());
    this->putElement('F', {points[value].first, points[value].second});
}

void SnakeGame::loop(){
    Snake *player = new Snake(0, 1);
    this->putElement(player->getValue(), player->getCurrentPosition());
    this->setFood();
    
    while(state != GAME_OVER){
        process_actions();
        update();
        this->movePlayerDown(player);
        this->movePlayerRight(player);
        render();
        wait(1000);// espera 1 segundo entre cada frame
    }
    
}
