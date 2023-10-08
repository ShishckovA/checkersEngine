//
// Created by Alexey Shishkov on 08.10.2023.
//

#ifndef CHECKERS_LIDRAUGHTSGAME_H
#define CHECKERS_LIDRAUGHTSGAME_H

#include <string>
#include <iostream>
#include <utility>
#include "Requests.h"
#include "Position.h"

class LidraughtsGame {
    const std::string gameUrl;
    std::string curString;
public:
    explicit LidraughtsGame(std::string gameUrl);

    static std::string convertFenToPosition(std::string fen) {
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

    std::string getFen() {
        std::string result = Requests::get(gameUrl);

        size_t fen = result.find("\"fen\":");
        size_t start = result.find('\"', fen + 5) + 1;
        size_t end = result.find('\"', start) + 1;
        return result.substr(start, end - start - 1);
    }

    std::tuple<bool, Position> getCurrent() {
        std::string fen = getFen();
        std::string positionString = convertFenToPosition(fen);
        bool hasUpdates = positionString != curString;
        curString = positionString;
        return {hasUpdates, Position::fromString(positionString)};
    }

};


#endif //CHECKERS_LIDRAUGHTSGAME_H
