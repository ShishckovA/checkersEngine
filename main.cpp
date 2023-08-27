#include "src/Position.h"
#include "src/StupidEngine.h"
#include "src/Game.h"
#include "src/MinimaxEngine.h"
#include <iostream>
#include <unistd.h>

int main() {
    Game g;
    MinimaxEngine* engine = new MinimaxEngine(8);

    while (1) {
        g.print();
        if (g.mover() == WHITE_MOVE) {
            int i = 1;
            std::vector<Position> moves = g.moves();
            for (auto x : moves) {
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
            i = atoi(inp.c_str());
            i--;
            std::string tomove = moves[i].lastMove;
            g.move(tomove);
        } else {
            std::string tomove = engine->move(g.position());
            g.move(tomove);
        }
    }

}
