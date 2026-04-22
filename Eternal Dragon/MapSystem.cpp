#include "MapSystem.h"
#include "BattleSystem.h"
#include "Renderer.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

Plate::Plate(int x, int y, char s) : x(x), y(y), symbol(s) {}

EmptyPlate::EmptyPlate(int x, int y) : Plate(x, y, '.') {}
bool EmptyPlate::onEnter(PlayerCharacter&) { return false; }
void EmptyPlate::printInfo() const { std::cout << "Empty\n"; }

EnemyPlate::EnemyPlate(int x, int y, std::unique_ptr<Enemy> e)
    : Plate(x, y, 'E'), enemy(std::move(e)) {
}
bool EnemyPlate::onEnter(PlayerCharacter& p) {
    std::cout << "\nEnemy encountered!\n";
    startBattle(p, *enemy);
    return !enemy->isAlive();
}
void EnemyPlate::printInfo() const { std::cout << "Enemy: " << enemy->getName() << "\n"; }

ItemPlate::ItemPlate(int x, int y, std::unique_ptr<Item> i)
    : Plate(x, y, 'I'), item(std::move(i)) {
}
bool ItemPlate::onEnter(PlayerCharacter& p) {
    std::cout << "You found " << item->getName() << "!\n";
    item->display();
    char c; std::cout << "Take it? (y/n): "; std::cin >> c;
    if (c == 'y' || c == 'Y') {
        p.addItem(std::move(item));
        std::cout << "Item taken!\n";
        return true;
    }
    return false;
}
void ItemPlate::printInfo() const { std::cout << "Item: " << item->getName() << "\n"; }

BossPlate::BossPlate(int x, int y, std::unique_ptr<Enemy> b)
    : Plate(x, y, 'B'), boss(std::move(b)) {
}
bool BossPlate::onEnter(PlayerCharacter& p) {
    std::cout << "\n*** BOSS FIGHT ***\n";
    startBattle(p, *boss);
    return !boss->isAlive();
}
void BossPlate::printInfo() const { std::cout << "BOSS: " << boss->getName() << "\n"; }

StairsPlate::StairsPlate(int x, int y) : Plate(x, y, '>') {}
bool StairsPlate::onEnter(PlayerCharacter& p) {
    std::cout << "\nYou found stairs to the next floor!\n";
    return false;
}
void StairsPlate::printInfo() const { std::cout << "Stairs down\n"; }

Map::Map(int w, int h, int floor) : width(w), height(h), floorLevel(floor) {
    grid.resize(height);
    for (auto& row : grid) row.resize(width);
    generateContent();
}

void Map::generateContent() {
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            grid[y][x] = std::make_unique<EmptyPlate>(x, y);

    // Add enemies
    for (int i = 0; i < 10; ++i) {
        int x = rand() % width;
        int y = rand() % height;
        if (grid[y][x]->getSymbol() == '.') {
            if (rand() % 2 == 0) {
                grid[y][x] = std::make_unique<EnemyPlate>(x, y, std::make_unique<Goblin>());
            }
            else {
                grid[y][x] = std::make_unique<EnemyPlate>(x, y, std::make_unique<Orc>());
            }
        }
    }

    // Add items
    for (int i = 0; i < 6; ++i) {
        int x = rand() % width;
        int y = rand() % height;
        if (grid[y][x]->getSymbol() == '.') {
            grid[y][x] = std::make_unique<ItemPlate>(x, y, std::make_unique<HealthPotion>());
        }
    }

    // Add boss
    int bx = width / 2;
    int by = height / 2;
    grid[by][bx] = std::make_unique<BossPlate>(bx, by, std::make_unique<InfernalTyrant>());

    // Add stairs
    int sx = width - 3;
    int sy = height - 3;
    grid[sy][sx] = std::make_unique<StairsPlate>(sx, sy);
}

void Map::addPlayer(std::unique_ptr<PlayerCharacter> p) {
    players.push_back(std::move(p));
    players.back()->setPosition(1, 1);
}

bool Map::movePlayer(PlayerCharacter& player, int dx, int dy) {
    int newX = (player.getX() + dx + width) % width;
    int newY = (player.getY() + dy + height) % height;

    bool shouldRemove = grid[newY][newX]->onEnter(player);

    if (shouldRemove) {
        grid[newY][newX] = std::make_unique<EmptyPlate>(newX, newY);
    }

    player.setPosition(newX, newY);
    return true;
}

char Map::getSymbolAt(int x, int y) const {
    if (y < 0 || y >= height || x < 0 || x >= width) return '.';
    return grid[y][x]->getSymbol();
}

std::vector<PlayerCharacter*>& Map::getPlayers() {
    static std::vector<PlayerCharacter*> refs;
    refs.clear();
    for (auto& p : players) refs.push_back(p.get());
    return refs;
}

// New functions
void Map::nextFloor() {
    floorLevel++;
    bossDefeatedThisFloor = false;
    generateContent();
    std::cout << "\n=== You descended to Floor " << floorLevel << " ===\n";
}

void Map::saveGame(const std::string& filename) const {
    std::ofstream file(filename);
    if (file) {
        file << "Floor:" << floorLevel << "\n";
        std::cout << "Game saved to " << filename << "!\n";
    }
}