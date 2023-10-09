//
// Created by Alexey Shishkov on 27.08.2023.
//
#pragma once

#ifndef CHECKERS_POSITION_H
#define CHECKERS_POSITION_H
#include "constants.h"
#include <cassert>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

extern std::unordered_map<int, char> NOTATIONS;

bool legalPos(int i, int j);

class Position {
public:
    std::vector<std::vector<Cell>> board;
    Mover mover;
    std::string lastMoveString;

public:
    Position(): board(std::vector<std::vector<Cell>>(W, std::vector<Cell>(W, EMPTY))), mover(WHITE_MOVE) {}
    static Position start();

    explicit Position(const std::vector<std::vector<Cell>> &board, Mover mover) : board(board), mover(mover) {}

    void print() const;

    [[nodiscard]] std::vector<Position> moves() const;


    void generateMoves(std::vector<Position> &moves, bool &hasAbilityToCapture, int i, int j) const;
    void generateCapturingMoves(
            std::vector<Position> &moves,
            bool &hasAbilityToCapture,
            int i,
            int j,
            std::vector<std::pair<int, int>> capturedOnMove,
            int depth = 0,
            std::string moveBuffer = ""
    ) const;

    void movePiece(int i1, int j1, int i2, int j2);

    [[nodiscard]] Position copy() const;

    void changeMover();

    [[nodiscard]] bool capturingAvailable(int i, int j) const;

    [[nodiscard]] Winner winner() const {
        if (!moves().empty()) {
            return NO_WINNER;
        }
        return mover == WHITE_MOVE ? BLACK_WINNER : WHITE_WINNER;
    }

    [[nodiscard]] std::string toString() const;
    static Position fromString(std::string inp) {
        assert(inp.length() == 33);
        Position p;
        int read = 0;
        for (int i = 0; i < W; ++i) {
            for (int j = (i + 1) % 2; j < W; j += 2) {
                switch (inp[read++]) {
                    case 'w': {
                        p.board[i][j] = WHITE_PIECE;
                        break;
                    }
                    case 'W': {
                        p.board[i][j] = WHITE_QUEEN;
                        break;
                    }
                    case 'b': {
                        p.board[i][j] = BLACK_PIECE;
                        break;
                    }
                    case 'B': {
                        p.board[i][j] = BLACK_QUEEN;
                        break;
                    }
                    default: {
                        p.board[i][j] = EMPTY;
                    }
                }
            }
        }
        p.mover = inp[read] == '1' ? WHITE_MOVE : BLACK_MOVE;
        return p;
    }

    bool capturingAvailable() const;
};


#endif //CHECKERS_POSITION_H
