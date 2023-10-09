//
// Created by Alexey Shishkov on 27.08.2023.
//

#ifndef CHECKERS_MINIMAXENGINE_H
#define CHECKERS_MINIMAXENGINE_H


#include "EngineBase.h"
#include <cmath>
#include <cstdio>


class MinimaxEngine : public EngineBase {
private:
    constexpr const static double inf = 1000;
    std::unordered_map<std::string, std::pair<int, double>> database;
    [[maybe_unused]] const double discount = 1;
public:
    int maxDepth;

    explicit MinimaxEngine(int maxDepth): maxDepth(maxDepth) {};
    virtual ~MinimaxEngine() = default;

    [[nodiscard]] virtual double positionScore(const Position& pos) const = 0;

    double minimax(const Position& pos, double alpha, double beta, int depth = 0);

    std::string move(Position pos) override;

    [[nodiscard]] std::vector<std::pair<Position, double>> sortedMovesWithScores(const Position &pos) const;

private:
    std::vector<Position> _bestSequence(const Position &start, int depth);
public:
    [[noreturn]] void infinite(const Position &pos, int maxOutput = 3);
    std::vector<Position> bestSequence(const Position &start, int depth=7);
};


#endif //CHECKERS_MINIMAXENGINE_H
