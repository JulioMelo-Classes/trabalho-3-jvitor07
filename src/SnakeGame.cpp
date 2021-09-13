#include "SnakeGame.h"

#include <iostream>
#include <fstream>

#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep



using namespace std;

SnakeGame::SnakeGame(){
    choice = "";
    frameCount = 0;
    this->score = 0;
    initialize_game();
}

void SnakeGame::initialize_game(){
    this->printInitialMessage();
    this->askRandPos();
    //carrega o nivel ou os níveis
    ifstream levelFile("data/maze1.txt"); //só dá certo se o jogo for executado dentro da raíz do diretório (vc vai resolver esse problema pegando o arquivo da linha de comando)
    int lineCount = 0;
    string line;
    if(levelFile.is_open()){
        while(getline(levelFile, line)){ //pega cada linha do arquivo
            if(lineCount == 0) {
                std::map<std::string, int> dados = SplitLineService::split(line, ' ');
                this->dimensions.first = dados["rows"];
                this->dimensions.second = dados["cols"];
                this->foods = dados["foods"];
            }
            if(lineCount > 0){ //ignora a primeira linha já que ela contem informações que não são uteis para esse exemplo
                maze.push_back(line);
            }
            lineCount++;
        }
    }
    std::pair<int, int> pos = this->itsRand ? RandPosService::getValidPos(this->dimensions, TranslateService::translate(this->dimensions, this->maze)) : this->getinitialPos();
    this->snake = new Snake(pos);
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
            //if(frameCount>0 && frameCount%10 == 0) //depois de 10 frames o jogo pergunta se o usuário quer continuar
                //state = WAITING_USER;
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
            this->printPlayerStatus();
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

void SnakeGame::game_over(){
}

void SnakeGame::printInitialMessage() {
    std::cout << "    ---> Welcome to the classic snake game <---" << std::endl;
    std::cout << "  Versão criada por: Emanuel Targino e João Vitor" << std::endl;
    std::cout << "--------------------------------------------------- "<< std::endl;
}

void SnakeGame::printPlayerStatus() {
    std::cout << "Lives: " << this->snake->getLifes()<< " | Score: " << this->score << "| Food eaten:" << this->snake->getEaten() << " of " << this->foods << std::endl;
}

void SnakeGame::askRandPos() {
    char option;
    std::cout << "Você deseja iniciar o jogador em uma posição aleatória? (s/n)" << std::endl << "(caso não deseje certifique que inseriu um '*' no arquivo do mapa)." << std::endl;
    std::cin >> option;
    this->itsRand = option == 's';
    std::cout << this->itsRand << std::endl;
}

bool SnakeGame::restart(int quantity)
{
    char option;
    cout << "Deseja gerar mais " << quantity << " comidas?(s/n)" << std::endl;
    std::cin >> option;
    return option == 's';
}

void SnakeGame::insertItem(std::pair<int, int> position, char item)
{
    this->maze[position.first][position.second] = item;
}

void SnakeGame::removeItem(std::pair<int, int> position) 
{
    this->maze[position.first][position.second] = ' ';
}

bool SnakeGame::collide(std::string cmd)
{
    bool status = false;
    std::pair<int, int> pos = this->snake->getPosition();

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
    
    if(status) this->snake->removeLife();
    
    return status;
}

void SnakeGame::itsFood(std::pair<int, int> nextPosition)
{
    if(this->maze[nextPosition.first][nextPosition.second] == 'F')
        this->snake->eat();
}

void SnakeGame::movePlayer(std::string cmd)
{
    std::pair<int, int> currentPosition = this->snake->getPosition();
    std::pair<int, int> nextPosition;

    if(cmd == "up") {
        nextPosition = {currentPosition.first - 1, currentPosition.second};
    } else if(cmd == "down") {
        nextPosition = {currentPosition.first + 1, currentPosition.second};
    } else if(cmd == "left") {
        nextPosition = {currentPosition.first, currentPosition.second - 1};
    } else if(cmd == "right"){
        nextPosition = {currentPosition.first, currentPosition.second + 1};
    }

    bool status = this->collide(cmd);

    if(!status) this->itsFood(nextPosition);
    
    if(!status && cmd == "up") {
        this->removeItem(currentPosition);
        this->snake->moveUp();
        this->insertItem(nextPosition, this->snake->getValue());
    } 
    if(!status && cmd == "down") {
        this->removeItem(currentPosition);
        this->snake->moveDown();
        this->insertItem(nextPosition, this->snake->getValue());
    } 
    if(!status && cmd == "left") {
        this->removeItem(currentPosition);
        this->snake->moveLeft();
        this->insertItem(nextPosition, this->snake->getValue());
    }  
    if(!status && cmd == "right") {
        this->removeItem(currentPosition);
        this->snake->moveRight();
        this->insertItem(nextPosition, this->snake->getValue());
    }
    if(!status && cmd == "stop") {
        this->insertItem(currentPosition, this->snake->getValue());
    }
    
}

void SnakeGame::understandMovement(std::pair<int, int> to)
{
    std::string cmd;
    if(this->snake->getPosition().first - 1 == to.first) {
        cmd = "up";
    }
    if(this->snake->getPosition().first + 1 == to.first) {
        cmd = "down";
    }
    if(this->snake->getPosition().second - 1 == to.second) {
        cmd = "left";
    }
    if(this->snake->getPosition().second + 1 == to.second) {
        cmd = "right";
    }
    if(this->snake->getPosition() == to) {
        cmd = "stop";
    }

    this->movePlayer(cmd);
}


void SnakeGame::loop(){
    ClodaService *cs = new ClodaService(this->dimensions, TranslateService::translate(this->dimensions, this->maze));
    int initialFoods = this->foods;
    for(int i = 0; i < this->foods; i++) {
        std::pair<int, int> end = RandPosService::getValidPos(this->dimensions, TranslateService::translate(this->dimensions, this->maze));
        std::vector<std::pair<int, int>> solution = cs->findWay(this->snake->getPosition(), end);

        if(solution.size() != 0) {
            auto it = solution.rbegin();
            this->insertItem(end, 'F');

            while(state != GAME_OVER){
                process_actions();
                update();
                this->understandMovement(*it);
                render();
                if(this->snake->getLifes() <= 0) this->state = GAME_OVER;
                this->score += 1;
                if(this->snake->getPosition() == end) break;
                it++;
                wait(1000);
            }
        } else {
            int lifes = this->snake->getLifes();
            while(this->snake->getLifes() == lifes) {
                update();
                this->movePlayer("right");
                render();
                wait(1000);
            }
        }
        if(this->state == GAME_OVER) {
            std::cout << "O Jogo acabou :(" << std::endl;
        }
        if(i == this->foods - 1 && this->restart(initialFoods)) {
           this->foods += initialFoods;
        }
    }

    
}
