cmake_minimum_required(VERSION 3.24)
project(checkers)

set(CMAKE_CXX_STANDARD 20)

add_executable(checkers
        main.cpp
        src/Position.cpp
        src/constants.cpp
        src/EngineBase.cpp
        src/StupidEngine.cpp
        src/Game.cpp
        src/MinimaxEngine.cpp
        src/Engines.cpp
        )
