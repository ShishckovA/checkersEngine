//
// Created by Alexey Shishkov on 27.08.2023.
//

#ifndef CHECKERS_MINIMAXENGINE_H
#define CHECKERS_MINIMAXENGINE_H


#include "EngineBase.h"


class MinimaxEngine : public EngineBase {
private:
    constexpr const static double inf = 1000;
public:
    int maxDepth;

    MinimaxEngine(int maxDepth): maxDepth(maxDepth) {};

    virtual double positionScore (const Position& pos) = 0;


    double minimax(Position pos, double alpha = -inf, double beta = inf, int depth = 0) {
        if (depth >= maxDepth) {
            return positionScore(pos);
        }
        double value;
        if (pos.mover == WHITE_MOVE) {
            value = -inf;
            for (Position move : pos.moves()) {
                value = fmax(value, minimax(move, alpha, beta, depth + 1));
                if (value > beta) {
                    break;
                }
                alpha = fmax(alpha, value);
            }
        } else {
            value = inf;
            for (Position move : pos.moves()) {
                value = fmin(value, minimax(move, alpha, beta, depth + 1));
                if (value < alpha) {
                    break;
                }
                beta = fmin(beta, value);
            }
        }
        return value;
    }

    std::string move(Position pos) override {
        std::string bestMove = pos.moves()[0].lastMove;
        double bestValue = -inf;
        int minSign = pos.mover == WHITE_MOVE ? 1 : -1;
        for (const auto &move : pos.moves()) {
            if (minimax(move) * minSign > bestValue) {
                bestMove = move.lastMove;
                bestValue = minimax(move) * minSign;
            }
        }
        std::cout << "Found best move with value " << bestValue << std::endl;
        return bestMove;
    }

};


#endif //CHECKERS_MINIMAXENGINE_H
