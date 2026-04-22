#pragma once
#include "MapSystem.h"

class Game {
private:
    std::unique_ptr<Map> map;
    bool running = false;

public:
    Game();

    void start();
    void newGame();
    void loadGame();
    void gameLoop();
    void moveMenu(PlayerCharacter& player);
    void inventoryMenu(PlayerCharacter& player);
    void shopMenu(PlayerCharacter& player);   // ? Added for shop
};