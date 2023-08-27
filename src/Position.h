//
// Created by Alexey Shishkov on 27.08.2023.
//
#pragma once

#ifndef CHECKERS_POSITION_H
#define CHECKERS_POSITION_H
#include "constants.h"
#include <vector>
#include <iostream>
#include <string>

class Position {
public:
    std::vector<std::vector<Cell>> board;
    Mover mover;
    std::string lastMove;

public:
    Position(): board(std::vector<std::vector<Cell>>(W, std::vector<Cell>(W, EMPTY))), mover(WHITE_MOVE) {}
    static Position start();

    explicit Position(const std::vector<std::vector<Cell>> &board, Mover mover) : board(board), mover(mover) {}

    void print() const;

    std::vector<Position> moves();


    void generateMoves(std::vector<Position> &moves, bool &hasAbilityToCapture, int i, int j) const;
    void generateCapturingMoves(
            std::vector<Position> &moves,
            bool &hasAbilityToCapture,
            int i,
            int j, int depth, std::string moveBuffer) const;

    bool isBeatingMove(Cell start, Cell over, Cell finish) const {
        return isOpponentPiece(over, mover) && finish == EMPTY;
    }

    void movePiece(int i1, int j1, int i2, int j2);

    Position copy() const;

    void changeMover();
};


#endif //CHECKERS_POSITION_H
