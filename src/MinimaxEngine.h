//
// Created by Alexey Shishkov on 27.08.2023.
//

#ifndef CHECKERS_MINIMAXENGINE_H
#define CHECKERS_MINIMAXENGINE_H


#include "EngineBase.h"

class MinimaxEngine : EngineBase {
    MinimaxEngine() {

    };

    int positionScore(const Position pos) {
        return 0;
    }

    std::string move(Position pos) override {
        std::vector<Position> moves = pos.moves();
        return moves[0].lastMove;
    }

};


#endif //CHECKERS_MINIMAXENGINE_H
