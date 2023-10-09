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
    explicit Game(Position p);
    Winner winner();
    void print();
    [[nodiscard]] Mover mover() const;
    std::vector<Position> moves();
    bool move(const std::string& move);
    Position position();
};


#endif //CHECKERS_GAME_H
