#include "BattleSystem.h"
#include "Renderer.h"
#include <iostream>

void startBattle(PlayerCharacter& player, Enemy& enemy) {
    clearScreen();
    std::cout << "\n=== BATTLE vs " << enemy.getName() << " ===\n\n";

    while (player.isAlive() && enemy.isAlive()) {
        // Player turn
        printHealthBar(player.getHealth(), player.getMaxHealth());
        std::cout << "   vs   ";
        printHealthBar(enemy.getHealth(), enemy.getMaxHealth());
        std::cout << "\n\n1. Attack\n2. Use Item\n3. Flee\nChoice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            player.attack(enemy);
        }
        else if (choice == 2) {
            player.printInventory();
            std::cout << "Select item number: ";
            size_t idx;
            std::cin >> idx;
            player.useItem(idx);
        }
        else if (choice == 3) {
            if (rand() % 100 < 60) {
                std::cout << "You successfully fled!\n";
                return;
            }
            std::cout << "Failed to flee!\n";
        }

        // Enemy attacks back if still alive
        if (enemy.isAlive()) {
            enemy.attack(player);
        }
    }

    if (!enemy.isAlive()) {
        std::cout << "\nYou defeated " << enemy.getName() << "!\n";
    }
}