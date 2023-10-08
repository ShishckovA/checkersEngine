//
// Created by Alexey Shishkov on 09.10.2023.
//

#include "LidraughtsGame.h"


LidraughtsGame::LidraughtsGame(std::string gameUrl) : LidraughtsActivity(gameUrl) {}

std::string LidraughtsGame::getFen() {
    std::string result = getPageCode();

    size_t fen = result.find("\"fen\":");
    size_t start = result.find('\"', fen + 5) + 1;
    size_t end = result.find('\"', start) + 1;
    return result.substr(start, end - start - 1);
}

