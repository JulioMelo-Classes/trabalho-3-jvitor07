cmake_minimum_required(VERSION 3.5)
project(snaze VERSION 0.1 LANGUAGES CXX )


### Executável
# Diretório contendo os .hpp
include_directories( include
                     include/Models
                     include/Services )

# Cria um executável com nome "snaze", adiciona neste executável os arquivos src/snaze.cpp src/sistema.cpp src/executor.cpp
add_executable( snaze
                src/SnakeGame.cpp
                src/Snaze.cpp
                src/Models/Snake.cpp
                src/Services/SplitLineService.cpp
                src/Services/RandPosService.cpp
                src/Services/TranslateService.cpp
                src/Services/ClodaService.cpp)

# The end
