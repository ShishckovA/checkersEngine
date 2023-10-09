//
// Created by Alexey Shishkov on 27.08.2023.
//

#include "MinimaxEngineNoMemory.h"

double MinimaxEngineNoMemory::minimax(const Position& pos, double alpha, double beta, int depth) const {
    std::vector<Position> curMoves = pos.moves();
    if (curMoves.empty()) {
        return pos.mover == WHITE_MOVE ? -inf : inf;
    }
    if (curMoves.size() == 1) {
        depth -= 1;
    }
    if (depth >= maxDepth) {
        return positionScore(pos);
    }
    double value;
    if (pos.mover == WHITE_MOVE) {
        value = -inf;
        for (const Position& move : pos.moves()) {
            value = std::max(value, minimax(move, alpha, beta, depth + 1));
            if (value > beta) {
                break;
            }
            alpha = std::max(alpha, value);
        }
    } else {
        value = inf;
        for (const Position& move : pos.moves()) {
            value = std::min(value, minimax(move, alpha, beta, depth + 1));
            if (value < alpha) {
                break;
            }
            beta = std::min(beta, value);
        }
    }
    return value;
}

std::string MinimaxEngineNoMemory::move(Position pos) {
    std::string bestMove = pos.moves()[0].lastMoveString;
    double bestValue = -inf;
    int minSign = pos.mover == WHITE_MOVE ? 1 : -1;
    for (const auto &move : pos.moves()) {
        if (minimax(move) * minSign > bestValue) {
            bestMove = move.lastMoveString;
            bestValue = minimax(move) * minSign;
        }
    }
    std::cout << "Found best move with value " << bestValue << std::endl;
    return bestMove;
}
