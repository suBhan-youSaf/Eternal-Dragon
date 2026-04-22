#pragma once
#include "ItemSystem.h"
#include <vector>
#include <string>
#include <memory>

class Map;

class Character {
protected:
    std::string name;
    int level = 1;
    float health, maxHealth;
    float damage, armor;
    float mana, maxMana;
    float experience = 0;
    float currency = 0;
    std::vector<std::unique_ptr<Item>> inventory;
    Weapon* equippedWeapon = nullptr;
    Armor* equippedArmor = nullptr;

public:
    Character(const std::string& name, int lvl, float hp, float dmg, float arm,
        float mp, float spd, float crit, float exp, float gold);

    virtual ~Character() = default;

    void addItem(std::unique_ptr<Item> item);
    void useItem(size_t index);
    void equipWeapon(size_t index);
    void equipArmor(size_t index);
    void takeDamage(float amount);
    void heal(float amount);
    void restoreMana(float amount);
    void gainExperience(float amount);
    void addCurrency(float amount);

    bool isAlive() const { return health > 0; }
    const std::string& getName() const { return name; }
    int getLevel() const { return level; }
    float getHealth() const { return health; }
    float getMaxHealth() const { return maxHealth; }
    float getDamage() const { return damage; }
    float getArmor() const { return armor; }
    float getCurrency() const { return currency; }   // ← Added

    void printStats() const;
    void printInventory() const;
};

class Enemy : public Character {
protected:
    float expReward, currencyReward;
public:
    Enemy(const std::string& name, int lvl, float hp, float dmg, float arm,
        float mp, float spd, float crit, float exp, float gold,
        float expR, float goldR);

    float getExpReward() const { return expReward; }
    float getCurrencyReward() const { return currencyReward; }
    virtual void attack(Character& target);
};

class Goblin : public Enemy { public: Goblin(); };
class Orc : public Enemy { public: Orc(); };
class InfernalTyrant : public Enemy {
public:
    InfernalTyrant();
    void attack(Character& target) override;
};

class PlayerCharacter : public Character {
private:
    int posX = 0, posY = 0;
public:
    explicit PlayerCharacter(const std::string& name);
    void setPosition(int x, int y) { posX = x; posY = y; }
    int getX() const { return posX; }
    int getY() const { return posY; }
    void move(int dx, int dy, Map& map);
    void attack(Enemy& target);
};