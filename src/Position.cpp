//
// Created by Alexey Shishkov on 27.08.2023.
//

#include "Position.h"

std::unordered_map<int, char> NOTATIONS = {
        {0, 'a'},
        {1, 'b'},
        {2, 'c'},
        {3, 'd'},
        {4, 'e'},
        {5, 'f'},
        {6, 'g'},
        {7, 'h'},
};

void Position::print() const {
    std::cout << std::endl;
    std::cout << "  ";
    for (char i = 'a'; i <= 'h'; ++i) {
        std::cout << i;
    }
    std::cout << std::endl;
    std::cout << "  ========" << std::endl;

    for (int i = 0; i < W; ++i) {
        std::cout << W - i << "|";
        for (int j = 0; j < W; ++j) {
            switch (board[i][j]) {
                case EMPTY: {
                    std::cout << " ";
                    break;
                }
                case WHITE_PIECE: {
                    std::cout << "O";
                    break;
                }
                case WHITE_QUEEN: {
                    std::cout << "Q";
                    break;
                }
                case BLACK_PIECE: {
                    std::cout << "#";
                    break;
                }
                case BLACK_QUEEN: {
                    std::cout << "*";
                    break;
                }
                default: {
                    std::cout << "?";
                    break;
                }
            }
        }
        std::cout << "|";
        std::cout << W - i << std::endl;

    }
    std::cout << "  ========" << std::endl;
    std::cout << "  ";
    for (char i = 'a'; i <= 'h'; ++i) {
        std::cout << i;
    }
    std::cout << std::endl;

}

bool legalPos(int i, int j) {
    return !(i < 0 || i >= W || j < 0 || j >= W);
}


std::string moveString(int i1, int j1, int i2, int j2) {

    return NOTATIONS[j1] + std::to_string(W - i1) + ":" + NOTATIONS[j2] + std::to_string(W - i2) + " ";
}

std::string cellString(int i, int j) {
    return NOTATIONS[j] + std::to_string(W - i);
}



void Position::generateCapturingMoves(
        std::vector<Position> &moves,
        bool &hasAbilityToCapture,
        int i,
        int j,
        std::vector<std::pair<int, int>> capturedOnMove,
        int depth,
        std::string moveBuffer
    ) const {
    bool wasCapturing = false;
    if (depth == 0) {
        moveBuffer = cellString(i, j);
    }
    for (int dirI : {-1, 1}) {
        for (int dirJ: {-1, 1}) {
            int overI = -1;
            int overJ = -1;
            std::vector<std::tuple<Position, int, int>> capturingFinishesPositions;
            bool nextCapturingAvailable = false;
            for (int step = 1; ; ++step) {
                if (!isQueen(board[i][j]) && step > 2) {
                    break;
                }
                int finishI = i + dirI * step;
                int finishJ = j + dirJ * step;
                if (!legalPos(finishI, finishJ)) {
                    break;
                }
                if (isMoversPiece(board[finishI][finishJ], mover) || board[finishI][finishJ] == NOW_CAPTURING) {
                    break;
                }
                if (isOpponentPiece(board[finishI][finishJ], mover)) {
                    if (overI != -1) {
                        break;
                    }
                    overI = finishI;
                    overJ = finishJ;
                    continue;
                }
                if (overI != -1) {
                    Position newPos = copy();
                    newPos.movePiece(i, j, finishI, finishJ);
                    newPos.board[overI][overJ] = NOW_CAPTURING;
                    bool nextCapturingAvailableOnFinish = newPos.capturingAvailable(finishI, finishJ);
                    if (nextCapturingAvailableOnFinish && !nextCapturingAvailable) {
                        nextCapturingAvailable = true;
                        capturingFinishesPositions.clear();
                    }
                    if (nextCapturingAvailable && !nextCapturingAvailableOnFinish) {
                        continue;
                    }
                    capturingFinishesPositions.emplace_back(newPos, finishI, finishJ);
                    wasCapturing = true;
                }
            }
            capturedOnMove.emplace_back(overI, overJ);
            for (const auto &[nextPos, nextPosI, nextPosJ] : capturingFinishesPositions) {
                nextPos.generateCapturingMoves(
                        moves,
                        hasAbilityToCapture,
                        nextPosI,
                        nextPosJ,
                        capturedOnMove,
                        depth + 1,
                        moveBuffer + ":" + cellString(nextPosI, nextPosJ)
                );
            }
            capturedOnMove.pop_back();
        }
    }
    if (!wasCapturing && depth >= 1) {
        if (!hasAbilityToCapture) {
            hasAbilityToCapture = true;
            moves.clear();
        }
        Position newPos = copy();
        for (const auto& [capturedI, capturedJ] : capturedOnMove) {
            newPos.board[capturedI][capturedJ] = EMPTY;
        }
        newPos.changeMover();
        newPos.lastMove = moveBuffer;
        moves.push_back(newPos);
    }
}


void Position::movePiece(int i1, int j1, int i2, int j2) {
    Cell newCell = board[i1][j1];
    if (i2 == 0 && mover == WHITE_MOVE) {
        newCell = WHITE_QUEEN;
    }
    if (i2 == W - 1 && mover == BLACK_MOVE) {
        newCell = BLACK_QUEEN;
    }
    board[i2][j2] = newCell;
    board[i1][j1] = EMPTY;
}

Position Position::copy() const {
    Position newPos = Position(this->board, this->mover);
    return newPos;
}

void Position::changeMover() {
    mover = ::changeMover(mover);
}

void Position::generateMoves(
        std::vector<Position> &moves,
        bool &hasAbilityToCapture,
        int i,
        int j) const {
    std::vector<std::pair<int, int>> buf;
    generateCapturingMoves(moves, hasAbilityToCapture, i, j, buf);

    if (hasAbilityToCapture) {
        return;
    }
    for (int dirI : {-1, 1}) {
        if ((!isQueen(board[i][j])) && (
            (dirI == -1 && mover == BLACK_MOVE) ||
            (dirI == 1 && mover == WHITE_MOVE)
        )) {
            continue;
        }
        for (int dirJ: {-1, 1}) {
            for (int step = 1; ; ++step) {
                int finishI = i + dirI * step;
                int finishJ = j + dirJ * step;
                if (!legalPos(finishI, finishJ) || board[finishI][finishJ] != EMPTY) {
                    break;
                }
                Position newPos = copy();
                newPos.movePiece(i, j, finishI, finishJ);
                newPos.lastMove = cellString(i, j) + "-" + cellString(finishI, finishJ);
                newPos.changeMover();
                moves.push_back(newPos);
                if (!isQueen(board[i][j])) {
                    break;
                }
            }
        }
    }
}


std::vector<Position> Position::moves() {
    std::vector<Position> res;
    bool hasAbilityToBeat = false;
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < W; ++j) {
            if (!isMoversPiece(board[i][j], mover)) {
                continue;
            }
            generateMoves(res, hasAbilityToBeat, i, j);
        }
    }
    return res;
}

Position Position::start() {
    return Position({
                            {EMPTY,       BLACK_PIECE, EMPTY,       BLACK_PIECE, EMPTY,       BLACK_PIECE, EMPTY,       BLACK_PIECE},
                            {BLACK_PIECE, EMPTY,       BLACK_PIECE, EMPTY,       BLACK_PIECE, EMPTY,       BLACK_PIECE, EMPTY},
                            {EMPTY,       BLACK_PIECE, EMPTY,       BLACK_PIECE, EMPTY,       BLACK_PIECE, EMPTY,       BLACK_PIECE},
                            {EMPTY,       EMPTY,       EMPTY,       EMPTY,       EMPTY,       EMPTY,       EMPTY,       EMPTY},
                            {EMPTY,       EMPTY,       EMPTY,       EMPTY,       EMPTY,       EMPTY,       EMPTY,       EMPTY},
                            {WHITE_PIECE, EMPTY,       WHITE_PIECE, EMPTY,       WHITE_PIECE, EMPTY,       WHITE_PIECE, EMPTY},
                            {EMPTY,       WHITE_PIECE, EMPTY,       WHITE_PIECE, EMPTY,       WHITE_PIECE, EMPTY,       WHITE_PIECE},
                            {WHITE_PIECE, EMPTY,       WHITE_PIECE, EMPTY,       WHITE_PIECE, EMPTY,       WHITE_PIECE, EMPTY}
                    }, WHITE_MOVE);
}

std::string Position::toString() const {
    std::string res;
    for (int i = 0; i < W; ++i) {
        for (int j = (i + 1) % 2; j < W; j += 2) {
            if (board[i][j] == WHITE_PIECE) {
                res += "w";
            } else if (board[i][j] == WHITE_QUEEN) {
                res += "W";
            } else if (board[i][j] == BLACK_PIECE) {
                res += "b";
            } else if (board[i][j] == BLACK_QUEEN) {
                res += "B";
            } else {
                res += "O";
            }
        }
    }
    res += mover == WHITE_MOVE ? "1" : "2";
    return res;
}

bool Position::capturingAvailable(int i, int j) const {
    for (int dirI : {-1, 1}) {
        for (int dirJ: {-1, 1}) {
            bool goOver = false;
            for (int step = 1; ; ++step) {
                if (!isQueen(board[i][j]) && step > 2) {
                    break;
                }
                int finishI = i + dirI * step;
                int finishJ = j + dirJ * step;
                if (!legalPos(finishI, finishJ)) {
                    break;
                }
                if (isMoversPiece(board[finishI][finishJ], mover) || board[finishI][finishJ] == NOW_CAPTURING) {
                    break;
                }
                if (isOpponentPiece(board[finishI][finishJ], mover)) {
                    if (goOver) {
                        break;
                    }
                    goOver = true;
                    continue;
                }
                if (goOver) {
                    return true;
                }
            }
        }
    }
    return false;
}
