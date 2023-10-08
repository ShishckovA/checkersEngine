//
// Created by Alexey Shishkov on 27.08.2023.
//

#include "MinimaxEngine.h"

double MinimaxEngine::minimax(Position pos, double alpha, double beta, int depth) {
    std::string posString = pos.toString();
    const auto res = database.find(posString);
    if (res != database.end() && res->second.first >= depth) {
        return res->second.second;
    }
    std::vector<Position> curMoves = pos.moves();
    if (curMoves.empty()) {
        return pos.mover == WHITE_MOVE ? -inf : inf;
    }
    if (curMoves.size() == 1) {
        depth += 1;
    }
    if (depth == 0) {
        return positionScore(pos);
    }
    double value;
    if (pos.mover == WHITE_MOVE) {
        value = -inf;
        for (const auto& [move, _] : sortedMovesWithScores(pos, true)) {
            value = std::max(value, minimax(move, alpha, beta, depth - 1));

            if (value > beta) {
                break;
            }
            alpha = std::max(alpha, value);
        }
    } else {
        value = inf;
        for (const auto& [move, _] : sortedMovesWithScores(pos, false)) {
            value = std::min(value, minimax(move, alpha, beta, depth - 1));
            if (value < alpha) {
                break;
            }
            beta = std::min(beta, value);
        }
    }
    database[posString] = {depth, value};
    return value;
}

std::string MinimaxEngine::move(Position pos) {
    std::string bestMove = pos.moves()[0].lastMove;
    double bestValue = -inf;
    int minSign = pos.mover == WHITE_MOVE ? 1 : -1;
    for (const auto &move : pos.moves()) {
        double moveScore = minimax(move, -inf, inf, maxDepth);
        if (moveScore * minSign > bestValue) {
            bestMove = move.lastMove;
            bestValue = moveScore * minSign;
        }
    }
    std::cout << "Found best move with value " << bestValue << std::endl;
    return bestMove;
}

void MinimaxEngine::infinite(const Position &pos) {
    bool descending = pos.mover == WHITE_MOVE;
    while (true) {
        std::vector<std::pair<Position, double>> moves;
        for (const auto& [move, score] : sortedMovesWithScores(pos, descending)) {
            std::string posString = move.toString();
            double minimaxx = minimax(move, -inf, inf, maxDepth);
            moves.emplace_back(move, minimaxx);
        }

        std::sort(moves.begin(), moves.end(), [descending] (
                const std::pair<Position, double>& lhs, const std::pair<Position, double>& rhs)
                -> bool {
            if (descending) {
                return (lhs.second > rhs.second);
            }
            return (lhs.second < rhs.second);
        });
        pos.print();
        std::cout << "Depth:" <<  maxDepth << std::endl;

        for (const auto &[move, score] : moves) {
            std::cout << move.lastMove << ": " << score << std::endl;
        }
        ++maxDepth;
    }
}


std::vector<std::pair<Position, double>> MinimaxEngine::sortedMovesWithScores(Position pos, bool descending) const {
    std::vector<std::pair<Position, double>> moves;
    for (const Position& move : pos.moves()) {
        const auto it = database.find(move.toString());
        double posScore;
        if (it != database.end()) {
            posScore = it->second.second;
        } else {
            posScore = positionScore(move);
        }
        std::string posString = move.toString();
        moves.emplace_back(move, posScore);
    }
    std::sort(moves.begin(), moves.end(), [descending] (
            const std::pair<Position, double>& lhs, const std::pair<Position, double>& rhs)
            -> bool {
        if (descending) {
            return (lhs.second > rhs.second);
        }
        return (lhs.second < rhs.second);
    });
    return moves;
}
