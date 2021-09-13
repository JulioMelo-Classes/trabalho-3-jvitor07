#ifndef SnakeGame_h
#define SnakeGame_h
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "Models/Snake.hpp"
#include "Services/SplitLineService.hpp"
#include "Services/ClodaService.hpp"
#include "Services/RandPosService.hpp"
#include "Services/TranslateService.hpp"

class SnakeGame{
    public:
        /**
        * @brief descreve os possíveis estados do jogo, fique à vontade para adicionar outros se necessário
        **/
        enum GameStates{
            RUNNING, //<! quando o jogo está executando o estado é RUNNING
            GAME_OVER, //<! quando o jogo deve terminar o estado é GAME_OVER
            WAITING_USER //<! quando o jogo deve esperar por uma entrada do usuário o estado é WAITING_USER
        };

    private:
        //<! atributos adicione outros se quiser
        std::vector<std::string> maze; //<! vector contendo o labirinto atual, pode ser interpretado como uma matriz
        int frameCount; //<! contador de frames, usado apenas como exemplo
        std::string choice; //<! usado na função process_actions para guardar a escolha do usuário
        GameStates state; //<! guarda o estado do jogo
        std::pair<int, int> dimensions;
        int foods;
        int score;
        Snake *snake;
        bool itsRand;

    public:
        /**
        * @brief construtor padrão, fique à vontade para adicionar parâmetros se desejar
        **/
        SnakeGame();

        /**
        * @brief chamado no main, este loop executa o jogo indefinidamente até que o usuário escolha terminar!
        */
        void loop();

    private:
        /**
        * @brief realiza a inicialização geral do jogo, fique à vontade para adicionar parâmetros se achar que deve
        **/
        void initialize_game();

        /**
        * @brief atualiza o estado do jogo, basicamente movendo os objetos, sorteando novas posições de comida
        **/
        void update();

        /**
        * @brief processa as entradas do jogador
        **/
        void process_actions();

        /**
        * @brief testa o estado do jogo e desenha a tela correspondente
        **/
        void render();

        /**
        * @brief é chamada quando o jogo termina a fim de destruir/resetar elementos do estado do jogo
        **/
        void game_over();

        /**
        * @brief é chamada quando o jogo inicia para mostrar as mensagens iniciais 
        **/
        void printInitialMessage();

        /**
        * @brief mostra o status do jogador
        **/
        void printPlayerStatus();

        /*! Método para inserir item no mapa.
            * @param std::pair<int, int> position: posição onde deve ser inserido.
            * @param char item que deve ser inserido
 		*/ 
        void insertItem(std::pair<int, int> position, char item);

        /*! Método para remover item no mapa.
            * @param std::pair<int, int> position: posição onde deve ser removido.
 		*/
        void removeItem(std::pair<int, int> position);

        /*! Método que identifica se a cobra colidiu na parede.
            * @param std::string cmd: comando pra onde a cobra vai.
            * @return bool: retorna verdadeiro caso haja a colisão e falso se não.
 		*/
        bool collide(std::string cmd);

        /*! Método para mover a cobra.
            * @param std::string cmd: comando pra onde a cobra vai.
 		*/
        void movePlayer(std::string cmd);

        /*! Método para entender o movimento da cobra.
            * @param std::pair<int, int> to: posição para o destino.
 		*/
        void understandMovement(std::pair<int, int> to);

        /*! Método para identificar se a posição que a cobra vai é uma comida.
            * @param std::pair<int, int> nextPosition: posição para o destino.
 		*/
        void itsFood(std::pair<int, int> nextPosition);
        
        /*! Método que pega a posição inicial da cobra.
            * @return std::pair<int, int>: posição inicial da cobra.
 		*/
        std::pair<int, int> getinitialPos();
        
        /**
        * @brief mostra mensagem que decide se a posição inicial vai ser aleatória ou não
        **/
        void askRandPos();

        /*! Método que verifica se o player quer continuar no jogo.
            * @param quantity quantidade de novas comidas que vão ser geradas.
            * @return bool: verdadeiro caso queira continuar e falso se não.
 		*/
        bool restart(int quantity);
};

#endif //SnakeGame_h