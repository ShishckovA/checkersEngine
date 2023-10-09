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



class MinimaxEngineNoMemory2 : public EngineBase {
private:
    constexpr const static double inf = 1000;
    std::unordered_map<std::string, std::pair<int, double>> database;
    [[maybe_unused]] const double discount = 1;
public:
    int maxDepth;

    explicit MinimaxEngineNoMemory2(int maxDepth): maxDepth(maxDepth) {};
    virtual ~MinimaxEngineNoMemory2() = default;

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

#endif //CHECKERS_MINIMAXENGINENOMEMORY_H
