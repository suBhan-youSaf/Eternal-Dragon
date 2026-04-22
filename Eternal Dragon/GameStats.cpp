#include "GameStats.h"
#include <iostream>
#include <ctime>

GameStats* GameStats::instance = nullptr;

GameStats::GameStats() {
    startTime = time(nullptr);
}

GameStats* GameStats::getInstance() {
    if (!instance) instance = new GameStats();
    return instance;
}

void GameStats::enemyDefeated() { enemiesDefeated++; }
void GameStats::itemCollected() { itemsCollected++; }
void GameStats::bossDefeated() { bossesDefeated++; }

void GameStats::displayStats() const {
    time_t now = time(nullptr);
    int minutes = static_cast<int>(difftime(now, startTime) / 60);
    std::cout << "\n=== GAME STATISTICS ===\n";
    std::cout << "Enemies Defeated : " << enemiesDefeated << "\n";
    std::cout << "Items Collected  : " << itemsCollected << "\n";
    std::cout << "Bosses Defeated  : " << bossesDefeated << "\n";
    std::cout << "Time Played      : " << minutes << " minutes\n";
}