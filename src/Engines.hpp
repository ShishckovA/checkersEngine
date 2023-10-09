#include "MinimaxEngine.h"
#include "MinimaxEngineNoMemory.h"

class DiffEngine : public MinimaxEngine {
public:
    [[maybe_unused]] explicit DiffEngine(int depth): MinimaxEngine(depth){};
    [[nodiscard]] double positionScore(const Position& pos) const override {
        float score = 0;
        for (int i = 0; i < W; ++i) {
            for (int j = (i + 1) % 2; j < W; j += 2) {
                if (pos.board[i][j] == WHITE_PIECE) {
                    score += 1;
                }
                if (pos.board[i][j] == WHITE_QUEEN) {
                    score += 5;
                }
                if (pos.board[i][j] == BLACK_PIECE) {
                    score -= 1;
                }
                if (pos.board[i][j] == BLACK_QUEEN) {
                    score -= 5;
                }
            }
        }
        return score;
    }
};

class FracEngine : public MinimaxEngine {
public:
    [[maybe_unused]] explicit FracEngine(int depth): MinimaxEngine(depth) {};

    [[nodiscard]] double positionScore(const Position& pos) const override {
        double whites = 0;
        double black = 0;
        for (int i = 0; i < W; ++i) {
            for (int j = (i + 1) % 2; j < W; j += 2) {
                if (pos.board[i][j] == WHITE_PIECE) {
                    whites += 1;
                }
                if (pos.board[i][j] == WHITE_QUEEN) {
                    whites += 5;
                }
                if (pos.board[i][j] == BLACK_PIECE) {
                    black += 1;
                }
                if (pos.board[i][j] == BLACK_QUEEN) {
                    black += 5;
                }
            }
        }
        double zo = whites / (whites + black);
        return zo * 2 - 1;
    }
};



class ScoredFracEngine : public MinimaxEngine {
public:
    explicit ScoredFracEngine(int depth): MinimaxEngine(depth) {};

    [[nodiscard]] double positionScore(const Position& pos) const override {
        std::vector<double> horizontal_scores = {1.02, 1.08, 1.18, 1.32, 1.51, 1.73, 2};
        double whites = 0;
        double black = 0;
        for (int i = 0; i < W; ++i) {
            for (int j = (i + 1) % 2; j < W; j += 2) {
                if (pos.board[i][j] == WHITE_PIECE) {
                    whites += 1. * horizontal_scores[W - i - 1];
                }
                if (pos.board[i][j] == WHITE_QUEEN) {
                    whites += 5.;
                }
                if (pos.board[i][j] == BLACK_PIECE) {
                    black += 1. * horizontal_scores[i];
                }
                if (pos.board[i][j] == BLACK_QUEEN) {
                    black += 5.;
                }
            }
        }
        double zo = whites / (whites + black);
        return zo * 2 - 1;
    }
};

class ScoredFracEngineNoMemory : public MinimaxEngineNoMemory {
public:
    explicit ScoredFracEngineNoMemory(int depth): MinimaxEngineNoMemory(depth) {};

    [[nodiscard]] double positionScore(const Position& pos) const override {
        std::vector<double> horizontal_scores = {1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
        double whites = 0;
        double black = 0;
        for (int i = 0; i < W; ++i) {
            for (int j = (i + 1) % 2; j < W; j += 2) {
                if (pos.board[i][j] == WHITE_PIECE) {
                    whites += 1 * horizontal_scores[W - i - 1];
                }
                if (pos.board[i][j] == WHITE_QUEEN) {
                    whites += 5;
                }
                if (pos.board[i][j] == BLACK_PIECE) {
                    black += 1 * horizontal_scores[i];
                }
                if (pos.board[i][j] == BLACK_QUEEN) {
                    black += 5;
                }
            }
        }
        double zo = whites / (whites + black);
        return zo * 2 - 1;
    }
};

class ScoredFracEngineNoMemory2 : public MinimaxEngineNoMemory2 {
public:
    explicit ScoredFracEngineNoMemory2(int depth): MinimaxEngineNoMemory2(depth) {};

    [[nodiscard]] double positionScore(const Position& pos) const override {
        std::vector<double> horizontal_scores = {1.02, 1.08, 1.18, 1.32, 1.51, 1.73, 2};
        double whites = 0;
        double black = 0;
        for (int i = 0; i < W; ++i) {
            for (int j = (i + 1) % 2; j < W; j += 2) {
                if (pos.board[i][j] == WHITE_PIECE) {
                    whites += 1 * horizontal_scores[W - i - 1];
                }
                if (pos.board[i][j] == WHITE_QUEEN) {
                    whites += 5;
                }
                if (pos.board[i][j] == BLACK_PIECE) {
                    black += 1 * horizontal_scores[i];
                }
                if (pos.board[i][j] == BLACK_QUEEN) {
                    black += 5;
                }
            }
        }
        double zo = whites / (whites + black);
        return zo * 2 - 1;
    }
};