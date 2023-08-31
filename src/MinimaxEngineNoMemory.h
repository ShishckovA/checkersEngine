//
// Created by Alexey Shishkov on 27.08.2023.
//

#ifndef CHECKERS_MINIMAXENGINENOMEMORY_H
#define CHECKERS_MINIMAXENGINENOMEMORY_H


#include "EngineBase.h"


class MinimaxEngineNoMemory : public EngineBase {
private:
    constexpr const static double inf = 1000;
    const double discount = 1;
public:
    int maxDepth;

    MinimaxEngineNoMemory(int maxDepth): maxDepth(maxDepth) {};

    virtual double positionScore (const Position& pos) = 0;


    double minimax(Position pos, double alpha = -inf, double beta = inf, int depth = 0);

    std::string move(Position pos) override;

};


#endif //CHECKERS_MINIMAXENGINENOMEMORY_H
