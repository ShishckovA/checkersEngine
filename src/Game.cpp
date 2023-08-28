//
// Created by Alexey Shishkov on 27.08.2023.
//

#include "Game.h"

bool Game::move(std::string move) {
    for (Position nextPos : pos.moves()) {
        if (nextPos.lastMove == move) {
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

Mover Game::mover() {
    return pos.mover;
}

std::vector<Position> Game::moves() {
    return pos.moves();
}

Position const Game::position() {
    return pos;
}

Game::Game() {
    pos = Position::start();
}

Game::Game(Position p): pos(p) {}

Winner Game::winner() {
    return pos.winner();
}

