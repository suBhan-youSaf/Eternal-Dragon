#pragma once
#include <string>

void clearScreen();
void printColored(const std::string& text, const std::string& color);
void printHealthBar(float current, float max);
void printMap(const class Map& map, int playerX, int playerY);