//
// Created by Alexey Shishkov on 27.08.2023.
//

#ifndef CHECKERS_MINIMAXENGINENOMEMORY_H
#define CHECKERS_MINIMAXENGINENOMEMORY_H


#include "EngineBase.h"


class MinimaxEngineNoMemory : public EngineBase {
private:
    constexpr const static double inf = 1000;
    [[maybe_unused]] const double discount = 1;
public:
    int maxDepth;

    explicit MinimaxEngineNoMemory(int maxDepth): maxDepth(maxDepth) {};
    virtual ~MinimaxEngineNoMemory() = default;


    [[nodiscard]] virtual double positionScore(const Position& pos) const = 0;

    [[nodiscard]] double minimax(const Position& pos, double alpha = -inf, double beta = inf, int depth = 0) const;

    std::string move(Position pos) override;

};


#endif //CHECKERS_MINIMAXENGINENOMEMORY_H
