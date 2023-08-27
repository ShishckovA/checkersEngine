//
// Created by Alexey Shishkov on 27.08.2023.
//

#ifndef CHECKERS_ENGINEBASE_H
#define CHECKERS_ENGINEBASE_H


#include "Position.h"

class EngineBase {
public:
    virtual std::string move(Position pos) = 0;
};


#endif //CHECKERS_ENGINEBASE_H
