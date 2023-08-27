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

    float positionScore(const Position& pos) {
        float score = 0;
        for (int i = 0; i < W; ++i) {
            for (int j = (i + 1) % 2; j < W; j += 2) {
                if (pos.board[i][j] == WHITE) {
                    score += 1;
                }
                if (pos.board[i][j] == WHITE_QUEEN) {
                    score += 5;
                }
                if (pos.board[i][j] == BLACK) {
                    score -= 1;
                }
                if (pos.board[i][j] == BLACK_QUEEN) {
                    score -= 5;
                }
            }
        }
        return score;
    }

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
//        std::cout << "Returning" << value << std::endl;
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
