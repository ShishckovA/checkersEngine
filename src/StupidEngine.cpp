//
// Created by Alexey Shishkov on 27.08.2023.
//

#include "StupidEngine.h"

std::string StupidEngine::move(Position pos) {
    std::vector<Position> moves = pos.moves();
    return moves[rand() % moves.size()].lastMoveString;
}
