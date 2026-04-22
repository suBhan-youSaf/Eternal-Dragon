#include "GameSystem.h"
#include "Renderer.h"
#include <iostream>

Game::Game() = default;

void Game::start() {
    clearScreen();
    std::cout << "\n=== ETERNAL DUNGEON ===\n\n";
    std::cout << "1. New Game\n2. Load Game\n3. Quit\nChoice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) newGame();
    else if (choice == 2) loadGame();
    else return;

    if (map) {
        running = true;
        gameLoop();
    }
}

void Game::newGame() {
    map = std::make_unique<Map>(12, 12, 1);

    std::string name;
    std::cout << "Enter your hero name: ";
    std::cin >> name;

    auto player = std::make_unique<PlayerCharacter>(name);
    player->addItem(std::make_unique<HealthPotion>());
    player->addItem(std::make_unique<HealthPotion>());
    player->addItem(std::make_unique<Sword>());

    map->addPlayer(std::move(player));
}

void Game::gameLoop() {
    while (running) {
        auto& players = map->getPlayers();
        if (players.empty() || !players[0]->isAlive()) {
            std::cout << "\nGAME OVER\n";
            break;
        }

        PlayerCharacter& player = *players[0];

        clearScreen();
        std::cout << "Floor " << map->getFloorLevel() << " — " << player.getName() << "\n\n";
        printMap(*map, player.getX(), player.getY());

        std::cout << "\n1. Move   2. Inventory   3. Stats   4. Shop   5. Save   6. Quit\nChoice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) moveMenu(player);
        else if (choice == 2) inventoryMenu(player);
        else if (choice == 3) player.printStats();
        else if (choice == 4) shopMenu(player);
        else if (choice == 5) map->saveGame("save.txt");
        else if (choice == 6) running = false;
    }
}

void Game::moveMenu(PlayerCharacter& player) {
    std::cout << "\nW) Up  S) Down  A) Left  D) Right  C) Cancel\nDirection: ";
    char dir;
    std::cin >> dir;
    dir = tolower(dir);

    int dx = 0, dy = 0;
    if (dir == 'w') dy = -1;
    else if (dir == 's') dy = 1;
    else if (dir == 'a') dx = -1;
    else if (dir == 'd') dx = 1;
    else return;

    map->movePlayer(player, dx, dy);
}

void Game::inventoryMenu(PlayerCharacter& player) {
    player.printInventory();
    std::cout << "\n1. Use Item\n2. Equip Weapon\n3. Equip Armor\n4. Back\nChoice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Item number: ";
        size_t idx; std::cin >> idx;
        player.useItem(idx);
    }
    else if (choice == 2 || choice == 3) {
        std::cout << "Item number: ";
        size_t idx; std::cin >> idx;
        if (choice == 2) player.equipWeapon(idx);
        else player.equipArmor(idx);
    }
}

void Game::shopMenu(PlayerCharacter& player) {
    std::cout << "\n=== SHOP ===\n";
    std::cout << "Your Gold: " << player.getCurrency() << "\n";
    std::cout << "1. Health Potion (30 gold)\n2. Sword (80 gold)\n3. Back\nChoice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1 && player.getCurrency() >= 30) {
        player.addCurrency(-30);
        player.addItem(std::make_unique<HealthPotion>());
        std::cout << "Bought Health Potion!\n";
    }
    else if (choice == 2 && player.getCurrency() >= 80) {
        player.addCurrency(-80);
        player.addItem(std::make_unique<Sword>());
        std::cout << "Bought Sword!\n";
    }
    else if (choice == 1 || choice == 2) {
        std::cout << "Not enough gold!\n";
    }
}

void Game::loadGame() {
    map = std::make_unique<Map>(12, 12);
    std::cout << "Load feature coming soon...\n";
}