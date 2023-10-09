//
// Created by Alexey Shishkov on 09.10.2023.
//

#ifndef CHECKERS_LIDRAUGHTSPUZZLE_H
#define CHECKERS_LIDRAUGHTSPUZZLE_H


#include "LidraughtsActivity.h"

class LidraughtsPuzzle : public LidraughtsActivity {
public:
    explicit LidraughtsPuzzle(const std::string& puzzleUrl);
    std::string getFen() override {
        std::string result = getPageCode();
        size_t fen = result.rfind("\"fen\":");
        size_t start = result.find('\"', fen + 5) + 1;
        size_t end = result.find('\"', start) + 1;
        return result.substr(start, end - start - 1);
    }
};


#endif //CHECKERS_LIDRAUGHTSPUZZLE_H
