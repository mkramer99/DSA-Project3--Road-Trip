//
// Created by otish on 7/28/2022.
//
#include "iostream"
#include "TextureManager.h"
#include "map"
#ifndef MINESWEEPER_NUMBER_H
#define MINESWEEPER_NUMBER_H

#endif //MINESWEEPER_NUMBER_H
using namespace std;
class Number {
public:
    Number();
    void event(sf::RenderWindow &window);
private:
    std::map<string, sf::Sprite> texture;
    std::vector<sf::Sprite> digits;

};
