//
// Created by Alexey Shishkov on 27.08.2023.
//

#include "Game.h"

#include <utility>

bool Game::move(const std::string& move) {
    for (const Position& nextPos : pos.moves()) {
        if (nextPos.lastMoveString == move) {
            pos = nextPos;
            if (++used_positions[pos.toString()] >= MAX_POSITION_REPEAT) {
                return false;
            }
            return true;
        }
    }
    assert(false);
}

void Game::print() {
    system("clear");
    std::cout << position().toString() << std::endl;
    pos.print();
}

Mover Game::mover() const {
    return pos.mover;
}

std::vector<Position> Game::moves() {
    return pos.moves();
}

Position Game::position() {
    return pos;
}

Game::Game() {
    pos = Position::start();
}

Game::Game(Position p): pos(std::move(std::move(p))) {}

Winner Game::winner() {
    return pos.winner();
}

