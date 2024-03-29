#include <iostream>

#include "src/Position.h"
#include "src/StupidEngine.h"
#include "src/Game.h"
#include "src/MinimaxEngine.h"
#include "src/Engines.hpp"
#include "src/LidraughtsGame.h"
#include "src/LidraughtsPuzzle.h"
#include <chrono>
#include <mutex>


[[noreturn]] void vsPC() {
//    Game g;
    Position p = Position::fromString("0bb0b0b0bb0wbb000w00www00w0000ww1");
    Game g(p);

    std::vector<std::string> positionHistory;
    MinimaxEngine* engine = new ScoredFracEngine(8);
    std::string lastMove;
    while (true) {
        g.print();
        std::cout << "Last move: " <<  lastMove << std::endl;
        if (g.mover() == BLACK_MOVE) {
            int i = 1;
            std::vector<Position> moves = g.moves();
            for (const auto& x : moves) {
                std::cout << i << " " << x.lastMoveString << std::endl;
                ++i;
            }
            std::string inp;
            std::cin >> inp;
            if (inp == "+") {
                engine->maxDepth += 1;
                std::cout << "Engine depth is " << engine->maxDepth << std::endl;
                continue;
            }
            if (inp == "-") {
                engine->maxDepth -= 1;
                std::cout << "Engine depth is " << engine->maxDepth << std::endl;
                continue;
            }
            if (inp == "z") {
                std::cout << positionHistory.back() << std::endl;
                std::cout << g.position().toString() << std::endl;
                g = Game(Position::fromString(positionHistory.back()));
                positionHistory.pop_back();
                continue;
            }
            i = (int) std::strtol(inp.c_str(), nullptr, 10);
            i--;
            std::string to_move = moves[i].lastMoveString;
            positionHistory.push_back(g.position().toString());
            g.move(to_move);
        } else {
            auto start = clock();
            std::string to_move = engine->move(g.position());
            auto end = clock();
            std::cout << end - start << std::endl;
            g.move(to_move);
            lastMove = to_move;
        }
    }
}

int pairEngines(EngineBase *engineWhite, EngineBase *engineBlack, const std::string& startPos = "") {
    Game g;
    if (!startPos.empty()) {
        g = Game(Position::fromString(startPos));
    }
    while (true) {
        g.print();
        std::cout << g.position().toString() << std::endl;
        Winner winner = g.winner();
        if (winner != NO_WINNER) {
            std::cout << ((winner == WHITE_WINNER) ? "White wins!" : "Black wins!") << std::endl;
            return (winner == WHITE_WINNER) ? 1 : -1;
        }
        EngineBase *engineMoves = g.mover() == WHITE_MOVE ? engineWhite : engineBlack;
        std::string to_move = engineMoves->move(g.position());
        if (!g.move(to_move)) {
            std::cout << "Draw (position repetition)!" << std::endl;
            return 0;
        }
    }
}


void e2e() {
    EngineBase *engine1 = new ScoredFracEngineNoMemory(7);
    EngineBase *engine2 = new ScoredFracEngine(7);

    std::vector<std::string> positions = {
        "",
        "bbbbbbbbbbbOOOObOwOOwOwwwwwwwwww1",
        "bbbbbbbbbbbOOOOObOOOwOwwwwOwwwww1",
        "bbbbbbbbbbObOObOOOwOwwwOwwwwwwww1",
        "bbbbbbbbbbObOObOwOOOwOwwwwwwwwww1",
        "bbbbbbbbbbObOObOwOOOwOwwwwwwwwww1",
        "bbbbbbbbbbObOOObwOOOwOwwwwwwwwww1",
        "bbbbbbbbbObbObOOOwOOwOwwwwwwwwww1",
        "bbbbbbbbbObbObOOOwOOwOwwwwwwwwww1",
        "bbbbbbbbbObbObOOOwOOwOwwwwwwwwww1",
        "bbbbbbbbbObbObOOwOOOOwwwwwwwwwww1",
        "bbbbbbbbbObbObOOwOOOwOwwwwwwwwww1",
        "bbbbbbbbbObbObOOwOOOwOwwwwwwwwww1",
        "bbbbbbbbbObbObOOwOOOwOwwwwwwwwww1",
        "bbbbbbbbbObbOObOOOwOwwwOwwwwwwww1",
//        "bbbbbbbbbObOOOObbOOOOwwwwwwwwwww1",
//        "bbbbbbbbbOObOObOOOwwwwOOwwwOwwww1",
//        "bbbbbbbbbOObOOObOObOwwOwwwwwwwww1",
//        "bbbbbbbbbOObOOObOOwwwwOOwOwwwwww1",
//        "bbbbbbbbbOOOwObOOObOwwOwOwwwwwww1",
//        "bbbbbbbbObbbbOOOOwOOwwOwwwwwwwww1",
//        "bbbbbbbbObbbbOOOwOOOwOwwwwwwwwww1",
//        "bbbbbbbbObbbObOOOOwOwwwOwwwwwwww1",
//        "bbbbbbbbObbbObOOOOwOwwwOwwwwwwww1",
//        "bbbbbbbbObbbOOOObOOwwwwwwwwOwwww1",
//        "bbbbbbbbObbObOObOwOwwwOOwwwwwwww1",
//        "bbbbbbbbObbObOOOwwOOwOwwwwOwwwOw1",
//        "bbbbbbbbObObbOObOOwwwwOOwwwwwwww1",
//        "bbbbbbbbObObOObOOOwwwbOOwwwwwwww1",
//        "bbbbbbbbObObOOOOOOObbwOwwwwwwwww1",
//        "bbbbbbbbOObbbOOObOOOOwwwwwwwwwww1",
//        "bbbbbbbbOObbOObOObOOOwwwwwwwwwww1",
//        "bbbbbbbbOObbOObOObOOwOwwwwwwwwww1",
//        "bbbbbbbbOObbOwOOOObOOwOwwwwwwwww1",
//        "bbbbbbbbOObOOwbbOOOOwOOwwwwwwwww1",
//        "bbbbbbbbOOObOObbOObOOOwOwwwwwwww1",
//        "bbbbbbbObbbbOOObOwwOwOwOwwwwwwww1",
//        "bbbbbbbObbObOObOOOOOwwOwwwwwwwww1",
//        "bbbbbbbObbObOOOOwwObwOOwwOwwwwww1",
//        "bbbbbbbObObbOOwbOOOOwOwOwwwwwwww1",
//        "bbbbbbbObOObwObbOwOOOOOwwwwwwwww1",
//        "bbbbbbbOObbbbOObwOOwwwwOOwwwwwww1",
//        "bbbbbbbOObbbOObbOOOwwOOwwwwOwwww1",
//        "bbbbbbbOObbbwbObOOOOwwwwOwwwwwww1",
//        "bbbbbbbOObbbwObOOOwOwOwwwwwwwwwO1",
//        "bbbbbbbOObObObbOOOOOwwwwwwOwwwww1",
//        "bbbbbbbOObObObbOwOOOwOwOwwwwwwww1",
//        "bbbbbbbOOObbbOwOOOOOwOOOwwwwwwww1",
//        "bbbbbbObbbbbOOObwOOOwwwwwOwwwwww1",
//        "bbbbbbObbbbbOOOOOOwwwwOOwwwOwwww1",
//        "bbbbbbObbbObOOObOOOOwwOwwwwwwwww1",
//        "bbbbbbObbObbObOOOOOwwwwbwwwwwwwO1",
//        "bbbbbbObbObbObwOOOOOwOOwwwwwwwww1",
//        "bbbbbbObObbbbOOOwOwbwwwwOwwOwwww1",
//        "bbbbbbObObbwOObOObOOOwwOwwwwwwww1",
//        "bbbbbbObOObbObwOOOOOwOOOwwwwwwww1",
//        "bbbbbbOOObbbObObOwOOwOwwOwwwwwww1",
//        "bbbbbObbbbbwObOOwOOOwOwOwwwwwwww1",
//        "bbbbbObbbbOObObwwOOOOwOOwwwwwwww1",
//        "bbbbbObbbObbOObOOOOOOwwwwwwwwwww1",
//        "bbbbbObbbObbOObOOOOOOwwwwwwwwwww1",
//        "bbbbbObbbObbOObOOOOOwwOwwwwwwwww1",
//        "bbbbbObbbObbOOOOOOOOOwwbwwwwwwww1",
//        "bbbbbObbbOObObbOwbOOwwwOwOwwwwww1",
//        "bbbbbObbbOObOObOwOOOwwOwOOwwwwww1",
//        "bbbbbObbbOOwOOObOOOOwOwOwwwOwwww1",
//        "bbbbbObbObbbbOOOOOOOwOwwwwwwwwww1",
//        "bbbbbObbObbbObOOwbOwwOwwwwwwwwwO1",
//        "bbbbbObbOObwbObOOOOOOwOwwwwwwwww1",
//        "bbbbbOObbOObOObbOOOOwOOwwwwwwwww1",
//        "bbbbObbbbbbbObOOwOwOwOOwwwwwwwww1",
//        "bbbbObbbbbOObOOOwOObOwOOwwwwwwww1",
//        "bbbbObbbbObbbbOOOOOwwwwwwwwwwwwO1",
//        "bbbbObbbObbbObOOOOOOwwOwwwwwwwww1",
//        "bObbbObbbbObObbOOOOwwOwOwwwwwwww1",
//        "ObbbbbbbbbbbOObOOOOOwOwwwwwwwwOw1",
//        "ObbbbbbbObbbbOOOwbOOOwwwwOwwwwww1",
    };
    int wins1 = 0, wins2 = 0, draws = 0;
    for (const std::string &position : positions) {
        int res;
        res = pairEngines(engine1, engine2, position);
        if (res == 1) {
            ++wins1;
        } else if (res == -1) {
            ++wins2;
        } else {
            ++draws;
        }
        res = pairEngines(engine2, engine1, position);
        if (res == 1) {
            ++wins2;
        } else if (res == -1) {
            ++wins1;
        } else {
            ++draws;
        }
    }
    std::cout << "Wins 1: " << wins1 << " (" << 100. * wins1 / (wins1 + wins2 + draws) << "%)" << std::endl;
    std::cout << "Wins 2: " << wins2 << " (" << 100. * wins2 / (wins1 + wins2 + draws) << "%)" << std::endl;
    std::cout << "Draws: " << draws << " (" << 100. * draws / (wins1 + wins2 + draws) << "%)" << std::endl;
}

void generatePositions(int n = 10, int maxMoves = 20) {
    StupidEngine engine;
    int gameNum = 0;
    while (gameNum < n) {
        Game game;
        Winner winner;
        int gameMoves = rand() % maxMoves;
        for (int i = 0; i < gameMoves * 2; ++i) {
            std::string to_move = engine.move(game.position());
            game.move(to_move);

            winner = game.winner();
            if (winner != NO_WINNER) {
                break;
            }
        }
        if (winner != NO_WINNER) {
            continue;
        }
        gameNum++;
        std::cout << "\"" << game.position().toString() << "\"," <<  std::endl;
    }
}


int main() {
    std::string url;
    std::cin >> url;
    LidraughtsActivity* activity;
    if (url.find("training") != std::string::npos) {
        activity = new LidraughtsPuzzle(url);
    } else {
        if (url.size() != 31) {
            url = url.substr(0, 31);
        }
        activity = new LidraughtsGame(url);
    }
    MinimaxEngine* engine = new ScoredFracEngine(5);
    activity->follow(engine);
    delete activity;
    delete engine;
}
