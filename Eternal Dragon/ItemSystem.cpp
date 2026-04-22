#include "ItemSystem.h"
#include "CharacterSystem.h"
#include <iostream>

Item::Item(const std::string& n, const std::string& d, float v)
    : name(n), description(d), value(v) {
}

void Item::display() const {
    std::cout << name << " — " << description << " (Value: " << value << ")\n";
}

// Potion
Potion::Potion(const std::string& n, const std::string& d, float v)
    : Item(n, d, v) {
}

// HealthPotion
HealthPotion::HealthPotion() : Potion("Health Potion", "Restores 50 HP", 50) {}
void HealthPotion::use() { std::cout << "You drank a Health Potion!\n"; }
void HealthPotion::applyEffect(Character& c) { c.heal(50); }

// ManaPotion
ManaPotion::ManaPotion() : Potion("Mana Potion", "Restores 40 MP", 40) {}
void ManaPotion::use() { std::cout << "You drank a Mana Potion!\n"; }
void ManaPotion::applyEffect(Character& c) { c.restoreMana(40); }

// Weapon base class (this was missing)
Weapon::Weapon(const std::string& n, const std::string& d, float v, float db)
    : Item(n, d, v), damageBoost(db) {
}

// Sword
Sword::Sword() : Weapon("Iron Sword", "Sharp blade", 80, 18) {}
void Sword::use() { std::cout << "You equipped the Sword!\n"; }
void Sword::applyEffect(Character&) {}

// Bow
Bow::Bow() : Weapon("Hunter Bow", "Ranged weapon", 70, 15) {}
void Bow::use() { std::cout << "You equipped the Bow!\n"; }
void Bow::applyEffect(Character&) {}

// Armor base class (this was missing)
Armor::Armor(const std::string& n, const std::string& d, float v, float ab)
    : Item(n, d, v), armorBoost(ab) {
}

// LightArmor
LightArmor::LightArmor() : Armor("Leather Armor", "Light protection", 60, 12) {}
void LightArmor::use() { std::cout << "You equipped Leather Armor!\n"; }
void LightArmor::applyEffect(Character&) {}

// HeavyArmor
HeavyArmor::HeavyArmor() : Armor("Plate Armor", "Strong protection", 140, 28) {}
void HeavyArmor::use() { std::cout << "You equipped Plate Armor!\n"; }
void HeavyArmor::applyEffect(Character&) {}