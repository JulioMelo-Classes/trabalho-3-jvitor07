# Snaze

## Como executar?
> - Clone este projeto.
> - Abra a pasta no seu terminal.
> - Execute o comando "mkdir build".
> - Execute o comando "cd build".
> - Execute o comando "cmake --build ."
> - Execute o comando "cd ../".
> - Execute o comando "./build/snaze ./data/maze1.txt"

## Criadores:
> - Emanuel Targino Barbosa.
> - João Vitor de Oliveira Santos.

## Avaliação CP1

### Snake/Pacman
O jogo deveria conter o modo snake/pacman. Em ambos os modos não é possível andar pra trás. No modo snake deve ser desenhado o corpo.

**Avaliação**

50% apenas o modo pacman foi feito

### Render.ui
O jogo deveria desenhar a UI corretamente, mostrando ao menos as vidas, o nível e o score.

**Avaliação**

não implementado

### Render.mapa
O jogo deveria desenhar o mapa corretamente, com base no arquivo passado como argumento. Ok

**Avaliação**

70% o programa lê um arquivo porém não usa os argumentos passados.

### Render.snake
O jogo deveria desenhar a snake corretamente.

**Avaliação**
Neste caso vou considerar Ok, pois estou mais preocupado com o posicionamento e movimentação da snake no mapa.

### Logic.colisão e Logic.comida
O jogo deve se comportar corretamente quando ocorre uma colisão com comida e com paredes.

**Avaliação**

Embora não haja qualquer notificação o jogo para quando há uma colisão então vou considerar ok

### Transição de mapas
O jogo deve ter transição de mapa uma vez que um mapa é terminado.

**Avaliação**

Não implementado.

### Interação com o usuário
O jogo deve perguntar ao usuário se quer continuar/reiniciar o nível/reiniciar o jogo a cada transição de mapa

**Avaliação**

Não implementado

### Classe Level ou similar
O software deve encapsular as funcionalidades do nível em uma classe.

**Avaliação**

Não implementado

### Classe Player ou similar
O software deve encapsular as decisões do jogo em uma classe.

**Avaliação**

Ok vou considerar que a classe "ClondaService" faz o papel do player, embora não seja nem perto da ideia de modelagem sugerida.

### Classe Snake ou similar
O software deve encapsular as funcionalidades relacionadas à snake em uma classe. 

**Avaliação**

ok

## Comentários gerais CP1
- Vocês praticamente não usaram orientação à objetos no trabalho, toda informação é processada em SnakeGame ou na classe ClondaService. Sugiro que vocês tentem dividir mais as tarefas em outros objetos. 
- Embora não tenha sido usado o gameloop pattern, a ideia de orientar à "serviços" simplesmente não faz sentido qua o problema não necessita de serviços, nesse caso a orientação à serviços transforma a solução em uma solução estruturada e não orientada à objetos. Por exemplo, a classe Snake não faz qualquer manipulação dos seus próprios dados, terceirizando essas operações pro SnakeGame, fazendo com que a classe Snake seja apenas um "modelo" como você mesmo colocou, o que não é o objetivo deste trabalho.
- Como deve ser dificil pra você pensar em outra modelagem, tente ao menos retirar a parte do processamento que está dentro de snakegame e colocar dentro de Snake, talvez valha a pena uma classe para modelar os mapas ao invés de deixar tudo como vetores da classe snakegame.
