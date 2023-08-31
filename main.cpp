#include <iostream>

#include "src/Position.h"
#include "src/StupidEngine.h"
#include "src/Game.h"
#include "src/MinimaxEngine.h"
#include "src/Engines.cpp"


void vsPC() {
    Game g;
//    Position p = Position::fromString("OOOOBOOOOOOOOOOOOOOOOBOWOOOOOBOO1");
//    Game g(p);

    std::vector<std::string> positionHistory;
    MinimaxEngine* engine = new ScoredFracEngine(8);
    std::string lastMove;
    while (1) {
        g.print();
        std::cout << "Last move: " <<  lastMove << std::endl;
        if (g.mover() == WHITE_MOVE) {
            int i = 1;
            std::vector<Position> moves = g.moves();
            for (const auto& x : moves) {
                std::cout << i << " " << x.lastMove << std::endl;
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
            i = atoi(inp.c_str());
            i--;
            std::string tomove = moves[i].lastMove;
            positionHistory.push_back(g.position().toString());
            g.move(tomove);
        } else {
            auto start = clock();
            std::string tomove = engine->move(g.position());
            auto end = clock();
            std::cout << end - start << std::endl;
            g.move(tomove);
            lastMove = tomove;
        }
    }
}

int pairEngines(EngineBase *engineWhite, EngineBase *engineBlack, const std::string& startPos = "") {
    Game g;
    if (!startPos.empty()) {
        g = Game(Position::fromString(startPos));
    }
    while (1) {
        g.print();
        std::cout << g.position().toString() << std::endl;
        Winner winner = g.winner();
        if (winner != NO_WINNER) {
            std::cout << ((winner == WHITE_WINNER) ? "White wins!" : "Black wins!") << std::endl;
            return (winner == WHITE_WINNER) ? 1 : -1;
        }
        EngineBase *engineMoves = g.mover() == WHITE_MOVE ? engineWhite : engineBlack;
        std::string tomove = engineMoves->move(g.position());
        if (!g.move(tomove)) {
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
            std::string tomove = engine.move(game.position());
            game.move(tomove);

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

void test() {
    Game g = Game(Position::fromString("B00000000W00000000000W000000W0002"));
    g.print();
    for (const auto& move : g.moves()) {
        move.print();
    }
}

int main() {
    vsPC();
//    test();
//    e2e();
//    generatePositions(100, 5);
}
