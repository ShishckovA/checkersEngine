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
#include "LidraughtsActivity.h"

class LidraughtsGame : public LidraughtsActivity {
public:
    explicit LidraughtsGame(std::string gameUrl);

    std::string getFen();

};


#endif //CHECKERS_LIDRAUGHTSGAME_H
