cmake_minimum_required(VERSION 3.25)
project(chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(chess main.cpp legalMoves.cpp)
target_include_directories(chess PRIVATE C:/SDL2/include)
target_link_directories(chess PRIVATE C:/SDL2/lib)
target_link_libraries(chess PRIVATE -static-libgcc -static-libstdc++ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer)
