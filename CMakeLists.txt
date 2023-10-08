cmake_minimum_required(VERSION 3.24)
project(checkers)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

message(STATUS "start running cmake...")

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()


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
        src/Engines.cpp
        src/Requests.cpp src/Requests.cpp src/LidraughtsGame.cpp)


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
