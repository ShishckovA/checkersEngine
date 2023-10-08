//
// Created by Alexey Shishkov on 08.10.2023.
//

#ifndef CHECKERS_LIDRAUGHTSACTIVITY_H
#define CHECKERS_LIDRAUGHTSACTIVITY_H

#include <string>
#include <iostream>
#include <utility>
#include "Requests.h"
#include "Position.h"

class LidraughtsActivity {
    const std::string pageUrl;
    std::string curString;
public:
    explicit LidraughtsActivity(std::string gameUrl);

    static std::string convertFenToPosition(std::string fen);

    virtual std::string getFen() = 0;

    std::string getPageCode() const;

    std::tuple<bool, Position> getCurrent();

};


#endif //CHECKERS_LIDRAUGHTSACTIVITY_H
