//
// Created by Alexey Shishkov on 27.08.2023.
//

#ifndef CHECKERS_GAME_H
#define CHECKERS_GAME_H


#include "Position.h"

class Game {
    Position pos;

public:
    Game();
    void print();
    Mover mover();
    std::vector<Position> moves();
    bool move(std::string move);
    Position const position();
};


#endif //CHECKERS_GAME_H
