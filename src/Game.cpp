//
// Created by Alexey Shishkov on 27.08.2023.
//

#include "Game.h"

bool Game::move(std::string move) {
    for (Position nextPos : pos.moves()) {
        if (nextPos.lastMove == move) {
            pos = nextPos;
            return true;
        }
    }
    return false;
}

void Game::print() {
    system("clear");
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

