#pragma once

extern int W;
extern int MAX_POSITION_REPEAT;
#define WHITE_BIT 0x1
#define BLACK_BIT 0x10
#define QUEEN_BIT 0x100


enum Cell {
    WHITE_PIECE = WHITE_BIT,
    WHITE_QUEEN = WHITE_BIT | QUEEN_BIT,
    BLACK_PIECE = BLACK_BIT,
    BLACK_QUEEN = BLACK_BIT | QUEEN_BIT,
    NOW_CAPTURING = 0x1000,
    EMPTY = 0x0
};

enum Mover {
    WHITE_MOVE = WHITE_BIT,
    BLACK_MOVE = BLACK_BIT
};

enum Winner {
    NO_WINNER = 0,
    WHITE_WINNER = 1,
    BLACK_WINNER = 2
};

inline bool isMoversPiece(Cell field, Mover mover) {
    return ((unsigned int) field) & ((unsigned int) mover);
}

inline bool isOpponentPiece(Cell field, Mover mover) {
    return !isMoversPiece(field, mover) && field;
}

inline bool isQueen(Cell field) {
    return ((unsigned int) field) & QUEEN_BIT;
}

inline Mover changeMover(Mover mover) {
    return Mover(((unsigned int) mover) ^ BLACK_BIT ^ WHITE_BIT);
}
