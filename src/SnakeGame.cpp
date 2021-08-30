#include "SnakeGame.h"

#include <iostream>
#include <fstream>

#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep

#define MIN 1
#define MAX 1000

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
            if(lineCount == 0) {
                std::vector<int>values = SplitService::split(line, ' ');
                this->dimensions.first = values[0];
                this->dimensions.second = values[1];
                this->foods = values[2];
            }
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

void SnakeGame::insertItem(std::pair<int, int> pos, char item) {
    this->maze[pos.first][pos.second] = item;
}

void SnakeGame::removeItem(std::pair<int, int> pos) {
    this->maze[pos.first][pos.second] = ' ';
}

bool SnakeGame::collide(std::string cmd, Snake *player) 
{
    bool status = false;
    std::pair<int, int> pos = player->getPos();

    if(cmd == "up") {
        if(this->maze[pos.first - 1][pos.second] == '#' || this->maze[pos.first - 1][pos.second] == '.') status = true;
    }
    if(cmd == "down") {
        if(this->maze[pos.first + 1][pos.second] == '#' || this->maze[pos.first + 1][pos.second] == '.') status = true;
    }
    if(cmd == "left") {
        if(this->maze[pos.first][pos.second - 1] == '#' || this->maze[pos.first][pos.second - 1] == '.') status = true;
    }
    if(cmd == "right") {
        if(this->maze[pos.first][pos.second + 1] == '#' || this->maze[pos.first][pos.second + 1] == '.') status = true;
    }
    
    if(status) player->removeLife();
    
    return status;
}

void SnakeGame::movePlayer(Snake *player, std::string cmd) {

    bool status = this->collide(cmd, player);
    
    if(!status && cmd == "up") {
        this->removeItem(player->getPos());
        player->moveUp();
        this->insertItem({player->getPos().first, player->getPos().second}, player->getValue());
    } 
    if(!status && cmd == "down") {
        this->removeItem(player->getPos());
        player->moveDown();
        this->insertItem({player->getPos().first, player->getPos().second}, player->getValue());
    }
    if(!status && cmd == "left") {
        this->removeItem(player->getPos());
        player->moveLeft();
        this->insertItem({player->getPos().first, player->getPos().second}, player->getValue());
    }
    if(!status && cmd == "right") {
        this->removeItem(player->getPos());
        player->moveRight();
        this->insertItem({player->getPos().first, player->getPos().second}, player->getValue());
    }
}

void SnakeGame::understandMovement(Snake *player, std::pair<int, int> to) {
    std::string command;
    if(player->getPos().first - 1 == to.first){
        command = "up";
    }
    if(player->getPos().first + 1 == to.first){
        command = "down";
    }
    if(player->getPos().second - 1 == to.second){
        command = "left";
    }
    if(player->getPos().second + 1 == to.second){
        command = "right";
    }
    if(player->getPos() == to) {
        this->insertItem(player->getPos(), player->getValue());
    }else {
        this->movePlayer(player, command);
    }
}

std::pair<int, int> SnakeGame::getinitialPos()
{
    std::pair<int, int> pos;

    for(int row = 0; row < this->dimensions.first; row++) {
        for(int col = 0; col < this->dimensions.second; col++) {
            if(this->maze[row][col] == '*') pos = {row, col};
        }
    }

    return pos;
}

void SnakeGame::loop(){
    Snake *player = new Snake(this->getinitialPos());
    ClodaService *cs = new ClodaService(this->dimensions, TranslateService::translate(this->dimensions, this->maze));
    for(int i = 0; i < this->foods; i++)
    {
        if(player->gameIsOver()) {
            this->state = GAME_OVER;
            break;
        }

        std::pair<int, int> end = RandPosService::getValidPos(this->dimensions, TranslateService::translate(this->dimensions, this->maze));
        std::vector<std::pair<int, int>> solution = cs->findWay(player->getPos(), end);

        if(solution.size() != 0) {
            auto it = solution.rbegin();
            this->insertItem(end, 'F');
            while(state != GAME_OVER){
                process_actions();
                update();
                this->understandMovement(player, *it);
                render();
                wait(1000);// espera 1 segundo entre cada frame
                it++;
                if(player->getPos() == end) break;
                if(player->gameIsOver()) {
                    this->state = GAME_OVER;
                }
            }
        }else {
            int initialLifes = player->getLifes();
            while(player->getLifes() > initialLifes - 1) {
                update();
                this->removeItem(player->getPos());
                this->movePlayer(player, "right");
                this->insertItem(player->getPos(), player->getValue());
                render();
                wait(1000);
            }
            if(player->gameIsOver()) {
                this->state = GAME_OVER;
            }
        }
    }
    



}
