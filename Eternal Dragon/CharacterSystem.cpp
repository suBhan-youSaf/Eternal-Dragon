#include "CharacterSystem.h"
#include "MapSystem.h"
#include "BattleSystem.h"
#include "Renderer.h"
#include <iostream>
#include <algorithm>

Character::Character(const std::string& n, int lvl, float hp, float dmg, float arm, float mp, float spd, float crit, float exp, float gold)
    : name(n), level(lvl), health(hp), maxHealth(hp), damage(dmg), armor(arm), mana(mp), maxMana(mp) {
}

void Character::addItem(std::unique_ptr<Item> item) {
    if (inventory.size() < 20) inventory.push_back(std::move(item));
}

void Character::useItem(size_t index) {
    if (index >= inventory.size()) return;
    auto& item = inventory[index];
    item->use();
    item->applyEffect(*this);
    if (dynamic_cast<Potion*>(item.get())) inventory.erase(inventory.begin() + index);
}

void Character::equipWeapon(size_t index) {
    if (index >= inventory.size()) return;
    if (auto* w = dynamic_cast<Weapon*>(inventory[index].get())) {
        if (equippedWeapon) damage -= equippedWeapon->getDamageBoost();
        equippedWeapon = w;
        damage += w->getDamageBoost();
    }
}

void Character::equipArmor(size_t index) {
    if (index >= inventory.size()) return;
    if (auto* a = dynamic_cast<Armor*>(inventory[index].get())) {
        if (equippedArmor) armor -= equippedArmor->getArmorBoost();
        equippedArmor = a;
        armor += a->getArmorBoost();
    }
}

void Character::takeDamage(float amount) {
    float dmgTaken = std::max(0.0f, amount - armor * 0.15f);
    health -= dmgTaken;
    if (health < 0) health = 0;
}

void Character::heal(float amount) { health = std::min(maxHealth, health + amount); }
void Character::restoreMana(float amount) { mana = std::min(maxMana, mana + amount); }

void Character::gainExperience(float amount) {
    experience += amount;
    while (experience >= 100) {
        level++;
        experience -= 100;
        maxHealth += 15;
        health = maxHealth;
        damage += 4;
        std::cout << "LEVEL UP! Now level " << level << "!\n";
    }
}

void Character::addCurrency(float amount) { currency += amount; }

void Character::printStats() const {
    std::cout << "\n=== " << name << " (Lv." << level << ") ===\n";
    printHealthBar(health, maxHealth);
    std::cout << "\nDamage: " << damage << "  Armor: " << armor << "\n";
}

void Character::printInventory() const {
    std::cout << "\n=== INVENTORY ===\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i << ". " << inventory[i]->getName() << "\n";
    }
}

// Enemy classes
Enemy::Enemy(const std::string& n, int lvl, float hp, float dmg, float arm, float mp, float spd, float crit, float exp, float gold, float expR, float goldR)
    : Character(n, lvl, hp, dmg, arm, mp, spd, crit, exp, gold), expReward(expR), currencyReward(goldR) {
}

void Enemy::attack(Character& target) {
    float dmg = damage * (0.8f + static_cast<float>(rand() % 40) / 100.0f);
    target.takeDamage(dmg);
    std::cout << name << " hits for " << static_cast<int>(dmg) << " damage!\n";
}

Goblin::Goblin() : Enemy("Goblin", 1, 40, 10, 3, 0, 1.2f, 5, 0, 0, 15, 8) {}
Orc::Orc() : Enemy("Orc", 3, 75, 16, 8, 0, 0.9f, 10, 0, 0, 30, 20) {}
InfernalTyrant::InfernalTyrant() : Enemy("Infernal Tyrant", 10, 450, 50, 30, 100, 1.6f, 25, 0, 0, 200, 150) {}

void InfernalTyrant::attack(Character& target) {
    if (rand() % 100 < 35) std::cout << "Infernal Breath! ";
    Enemy::attack(target);
}

PlayerCharacter::PlayerCharacter(const std::string& n) : Character(n, 1, 130, 16, 8, 60, 1.0f, 15, 0, 0) {}

void PlayerCharacter::move(int dx, int dy, Map& m) { m.movePlayer(*this, dx, dy); }

void PlayerCharacter::attack(Enemy& target) {
    float dmg = damage * (0.8f + static_cast<float>(rand() % 40) / 100.0f);
    target.takeDamage(dmg);
    std::cout << "You hit for " << static_cast<int>(dmg) << " damage!\n";
}