#include "src/Position.h"
#include "src/StupidEngine.h"
#include "src/Game.h"
#include <iostream>
#include <unistd.h>

int main() {
    Game g;
    EngineBase* engine = new StupidEngine();

    while (1) {
        g.print();
        if (g.mover() == WHITE_MOVE) {
            int i = 1;
            std::vector<Position> moves = g.moves();
            for (auto x : moves) {
                std::cout << i << " " << x.lastMove << std::endl;
                ++i;
            }
            std::cin >> i;
            i--;
            std::string tomove = moves[i].lastMove;
            g.move(tomove);
        } else {
            std::string tomove = engine->move(g.position());
            g.move(tomove);
        }
    }

}
