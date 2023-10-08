//
// Created by Alexey Shishkov on 27.08.2023.
//

#ifndef CHECKERS_MINIMAXENGINE_H
#define CHECKERS_MINIMAXENGINE_H


#include "EngineBase.h"
#include <math.h>


class MinimaxEngine : public EngineBase {
private:
    constexpr const static double inf = 1000;
    std::unordered_map<std::string, std::pair<int, double>> database;
    const double discount = 1;
public:
    int maxDepth;

    MinimaxEngine(int maxDepth): maxDepth(maxDepth) {};

    virtual double positionScore(const Position& pos) const = 0;

    double minimax(Position pos, double alpha, double beta, int depth = 0);

    std::string move(Position pos) override;

    std::vector<std::pair<Position, double>> sortedMovesWithScores(Position pos, bool descending) const;

    void infinite(const Position &pos);
};


#endif //CHECKERS_MINIMAXENGINE_H
