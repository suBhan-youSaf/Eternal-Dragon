#pragma once
#include <string>

class Character;

class Item {
protected:
    std::string name;
    std::string description;
    float value;
public:
    Item(const std::string& n, const std::string& d, float v);
    virtual ~Item() = default;
    virtual void use() = 0;
    virtual void applyEffect(Character& c) = 0;
    virtual char getSymbol() const = 0;
    const std::string& getName() const { return name; }
    void display() const;
};

class Potion : public Item {
public:
    Potion(const std::string& n, const std::string& d, float v);
    char getSymbol() const override { return 'P'; }
};

class HealthPotion : public Potion {
public:
    HealthPotion();
    void use() override;
    void applyEffect(Character& c) override;
};

class ManaPotion : public Potion {
public:
    ManaPotion();
    void use() override;
    void applyEffect(Character& c) override;
};

class Weapon : public Item {
protected:
    float damageBoost;
public:
    Weapon(const std::string& n, const std::string& d, float v, float db);
    char getSymbol() const override { return 'W'; }
    float getDamageBoost() const { return damageBoost; }
};

class Sword : public Weapon { public: Sword(); void use() override; void applyEffect(Character& c) override; };
class Bow : public Weapon { public: Bow();   void use() override; void applyEffect(Character& c) override; };

class Armor : public Item {
protected:
    float armorBoost;
public:
    Armor(const std::string& n, const std::string& d, float v, float ab);
    char getSymbol() const override { return 'A'; }
    float getArmorBoost() const { return armorBoost; }
};

class LightArmor : public Armor { public: LightArmor(); void use() override; void applyEffect(Character& c) override; };
class HeavyArmor : public Armor { public: HeavyArmor(); void use() override; void applyEffect(Character& c) override; };