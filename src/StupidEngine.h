//
// Created by Alexey Shishkov on 27.08.2023.
//

#ifndef CHECKERS_STUPIDENGINE_H
#define CHECKERS_STUPIDENGINE_H


#include "EngineBase.h"

class StupidEngine: public EngineBase {

public:
    std::string move(Position pos) override;
    StupidEngine() = default;
};


#endif //CHECKERS_STUPIDENGINE_H
