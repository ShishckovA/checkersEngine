//
// Created by Alexey Shishkov on 27.08.2023.
//

#ifndef CHECKERS_GAME_H
#define CHECKERS_GAME_H


#include "Position.h"
#include <unordered_map>
#include <cassert>

class Game {
    Position pos;
    std::unordered_map<std::string, int> used_positions;

public:
    Game();
    Game(Position p);
    Winner winner();
    void print();
    Mover mover();
    std::vector<Position> moves();
    bool move(std::string move);
    Position const position();
};


#endif //CHECKERS_GAME_H
