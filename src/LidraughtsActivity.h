//
// Created by Alexey Shishkov on 08.10.2023.
//

#ifndef CHECKERS_LIDRAUGHTSACTIVITY_H
#define CHECKERS_LIDRAUGHTSACTIVITY_H

#include <string>
#include <iostream>
#include <utility>
#include <csignal>
#include <unistd.h>
#include <sys/wait.h>
#include "Requests.h"
#include "Position.h"
#include "MinimaxEngine.h"

class LidraughtsActivity {
    const std::string pageUrl;
    std::string curString;
public:
    explicit LidraughtsActivity(std::string gameUrl);

    virtual ~LidraughtsActivity() = default;

    static std::string convertFenToPosition(std::string fen);

    virtual std::string getFen() = 0;

    [[nodiscard]] std::string getPageCode() const;

    std::tuple<bool, Position> getCurrent();

    void follow(MinimaxEngine *e, int startingDepth = 4, int engineMaxOutput = 3) {
        auto [hasUpdates, pos] = getCurrent();
        while (true) {
            pid_t pid = fork();

            if (pid == 0) {
                e->maxDepth = startingDepth;
                e->infinite(pos, engineMaxOutput);
            } else if (pid > 0) {
                do {
                    auto pp = getCurrent();
                    hasUpdates = std::get<0>(pp);
                    pos = std::get<1>(pp);
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                } while (!hasUpdates);

                kill(pid, SIGKILL);
                wait(nullptr);
            } else {
                std::cerr << "Fork failed" << std::endl;
                exit(1);
            }
        }
    }

};


#endif //CHECKERS_LIDRAUGHTSACTIVITY_H
