//
// Created by Alexey Shishkov on 27.08.2023.
//

#include "MinimaxEngine.h"

double MinimaxEngine::minimax(const Position& pos, double alpha, double beta, int depth) {
    std::string posString = pos.toString();
    const auto res = database.find(posString);
    if (res != database.end() && res->second.first >= depth) {
        return res->second.second;
    }
    std::vector<Position> curMoves = pos.moves();
    if (curMoves.empty()) {
        return pos.mover == WHITE_MOVE ? -inf : inf;
    }
    if (curMoves.size() == 1 || (depth == 0 && pos.capturingAvailable())) {
        depth += 1;
    }
    if (depth == 0) {
        return positionScore(pos);
    }
    double value;
    if (pos.mover == WHITE_MOVE) {
        value = -inf;
        for (const auto& [move, _] : sortedMovesWithScores(pos)) {
            value = std::max(value, minimax(move, alpha, beta, depth - 1));

            if (value > beta) {
                break;
            }
            alpha = std::max(alpha, value);
        }
    } else {
        value = inf;
        for (const auto& [move, _] : sortedMovesWithScores(pos)) {
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
    std::string bestMove = pos.moves()[0].lastMoveString;
    double bestValue = -inf;
    int minSign = pos.mover == WHITE_MOVE ? 1 : -1;
    for (const auto &move : pos.moves()) {
        double moveScore = minimax(move, -inf, inf, maxDepth);
        if (moveScore * minSign > bestValue) {
            bestMove = move.lastMoveString;
            bestValue = moveScore * minSign;
        }
    }
    std::cout << "Found best move with value " << bestValue << std::endl;
    return bestMove;
}

[[noreturn]] void MinimaxEngine::infinite(const Position &pos, int maxOutput) {
    bool descending = pos.mover == WHITE_MOVE;
    while (true) {
        std::vector<std::pair<Position, double>> moves;
        for (const auto& [move, score] : sortedMovesWithScores(pos)) {
            std::string posString = move.toString();
            double minimax_val = minimax(move, -inf, inf, maxDepth);
            moves.emplace_back(move, minimax_val);
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
        int output = 0;
        for (const auto &[move, score] : moves) {
            std::printf("%s: %.3f\n", move.lastMoveString.c_str(), score * 100);
            const auto& bestSeq = bestSequence(move, maxOutput);
            std::cout << "( ";
            for (const auto &nextMove : bestSeq) {
                std::cout << nextMove.lastMoveString << " ";
            }
            std::cout << ")" << std::endl;
            output++;
            if (output >= maxOutput) {
                break;
            }
        }
        ++maxDepth;
    }
}


std::vector<std::pair<Position, double>> MinimaxEngine::sortedMovesWithScores(const Position &pos) const {
    bool descending = pos.mover == WHITE_MOVE;
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

std::vector<Position> MinimaxEngine::bestSequence(const Position &start, int depth) {
    auto seq = _bestSequence(start, depth);
    std::reverse(seq.begin(), seq.end());
    return seq;
}

std::vector<Position> MinimaxEngine::_bestSequence(const Position &start, int depth) {
    if (depth == 0) {
        return {};
    }
    const auto& movesWithScores = sortedMovesWithScores(start);
    if (!movesWithScores.empty()) {
        Position bestMove = movesWithScores.front().first;
        std::vector<Position> bestSeq = _bestSequence(bestMove, depth - 1);
        bestSeq.push_back(bestMove);
        return bestSeq;
    }
    return {};
}
