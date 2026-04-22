#include "Renderer.h"
#include "MapSystem.h"
#include <iostream>

void clearScreen() { system("cls"); }

void printColored(const std::string& text, const std::string& color) {
    std::cout << color << text << "\033[0m";
}

void printHealthBar(float current, float max) {
    float percent = current / max;
    int filled = static_cast<int>(percent * 20);
    std::cout << "[";
    for (int i = 0; i < 20; ++i) {
        std::cout << (i < filled ? "#" : "-");
    }
    std::cout << "] " << static_cast<int>(current) << "/" << static_cast<int>(max);
}

void printMap(const Map& map, int playerX, int playerY) {
    for (int y = 0; y < map.getHeight(); ++y) {
        for (int x = 0; x < map.getWidth(); ++x) {
            if (x == playerX && y == playerY) {
                printColored(" P ", "\033[1;33m");
                continue;
            }
            char sym = map.getSymbolAt(x, y);
            if (sym == 'E') printColored(" E ", "\033[31m");
            else if (sym == 'I') printColored(" I ", "\033[32m");
            else if (sym == 'B') printColored(" B ", "\033[35m");
            else if (sym == '>') printColored(" > ", "\033[36m");
            else std::cout << " . ";
        }
        std::cout << "\n";
    }
}