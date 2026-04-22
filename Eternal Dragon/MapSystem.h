#pragma once
#include "CharacterSystem.h"
#include <vector>
#include <memory>

class Plate {
protected:
    int x, y;
    char symbol;
public:
    Plate(int x, int y, char s);
    virtual ~Plate() = default;
    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return symbol; }
    virtual bool onEnter(PlayerCharacter& player) = 0;
    virtual void printInfo() const = 0;
};

class EmptyPlate : public Plate { public: EmptyPlate(int x, int y); bool onEnter(PlayerCharacter& player) override; void printInfo() const override; };
class EnemyPlate : public Plate { std::unique_ptr<Enemy> enemy; public: EnemyPlate(int x, int y, std::unique_ptr<Enemy> e); bool onEnter(PlayerCharacter& player) override; void printInfo() const override; };
class ItemPlate : public Plate { std::unique_ptr<Item> item;  public: ItemPlate(int x, int y, std::unique_ptr<Item> i);  bool onEnter(PlayerCharacter& player) override; void printInfo() const override; };
class BossPlate : public Plate { std::unique_ptr<Enemy> boss;  public: BossPlate(int x, int y, std::unique_ptr<Enemy> b);  bool onEnter(PlayerCharacter& player) override; void printInfo() const override; };
class StairsPlate : public Plate { public: StairsPlate(int x, int y); bool onEnter(PlayerCharacter& player) override; void printInfo() const override; };

class Map {
private:
    int width, height, floorLevel = 1;
    bool bossDefeatedThisFloor = false;
    std::vector<std::vector<std::unique_ptr<Plate>>> grid;
    std::vector<std::unique_ptr<PlayerCharacter>> players;

public:
    Map(int w, int h, int floor = 1);
    void generateContent();
    void addPlayer(std::unique_ptr<PlayerCharacter> p);
    bool movePlayer(PlayerCharacter& player, int dx, int dy);
    char getSymbolAt(int x, int y) const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getFloorLevel() const { return floorLevel; }
    bool isBossDefeated() const { return bossDefeatedThisFloor; }
    void setBossDefeated(bool defeated) { bossDefeatedThisFloor = defeated; }

    void nextFloor();                    // Added
    void saveGame(const std::string& filename) const;  // Added
    std::vector<PlayerCharacter*>& getPlayers();
};