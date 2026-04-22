#include "GameSystem.h"
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Game game;
    game.start();
    return 0;
}