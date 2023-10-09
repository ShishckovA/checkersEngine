cmake_minimum_required(VERSION 3.22)
project(checkers)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

message(STATUS "start running cmake...")


add_executable(
        checkers
        main.cpp
        src/Position.cpp
        src/constants.cpp
        src/EngineBase.cpp
        src/StupidEngine.cpp
        src/Game.cpp
        src/MinimaxEngine.cpp
        src/MinimaxEngineNoMemory.cpp
        src/Engines.hpp
        src/Requests.cpp
        src/LidraughtsActivity.cpp
        src/LidraughtsGame.cpp
        src/LidraughtsPuzzle.cpp src/LidraughtsPuzzle.h)


find_package (CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(checkers ${CURL_LIBRARIES})
else()
    MESSAGE(FATAL_ERROR "LibCurl is not found in your system.")
endif (CURL_FOUND)

target_link_libraries(checkers ${LIBS})

if(Boost_FOUND)
    target_link_libraries(checkers ${Boost_LIBRARIES})
endif()
