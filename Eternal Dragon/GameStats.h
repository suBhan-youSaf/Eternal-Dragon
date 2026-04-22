#pragma once
#include <string>

class GameStats {
private:
    static GameStats* instance;
    int enemiesDefeated = 0;
    int itemsCollected = 0;
    int bossesDefeated = 0;
    time_t startTime;

    GameStats();

public:
    static GameStats* getInstance();
    void enemyDefeated();
    void itemCollected();
    void bossDefeated();
    void displayStats() const;
};