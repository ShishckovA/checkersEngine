//
// Created by Alexey Shishkov on 08.10.2023.
//

#include "LidraughtsActivity.h"


LidraughtsActivity::LidraughtsActivity(std::string gameUrl) : pageUrl(std::move(gameUrl)) {}

std::string LidraughtsActivity::convertFenToPosition(std::string fen) {
    std::string result(33, '0');
    result[32] = fen[0] == 'W' ? '1' : '2';
    size_t i = 1;
    char mover = '?';
    bool isQueen = false;
    int num = 0;
    while (i < fen.size()) {
        if (isdigit(fen[i])) {
            num = num * 10 + (fen[i] - '0');
        } else {
            if (num > 0) {
                if (isQueen) {
                    mover = toupper(mover);
                } else {
                    mover = tolower(mover);
                }
                result[num - 1] = mover;
            }
            if (fen[i] == ':') {
                ++i;
                if (fen[i] == 'W') {
                    mover = 'W';
                } else if (fen[i] == 'B') {
                    mover = 'B';
                } else {
                    break;
                }
            }
            num = 0;
            isQueen = false;
            if (fen[i] == 'K') {
                isQueen = true;
            }
        }
        ++i;
    }
    return result;
}

std::tuple<bool, Position> LidraughtsActivity::getCurrent() {
    std::string fen = getFen();
    std::string positionString = convertFenToPosition(fen);
    bool hasUpdates = positionString != curString;
    curString = positionString;
    return {hasUpdates, Position::fromString(positionString)};
}

std::string LidraughtsActivity::getPageCode() const {
    return Requests::get(pageUrl);
}

