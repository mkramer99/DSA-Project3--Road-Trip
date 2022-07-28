//
// Created by otish on 7/28/2022.
//

#include "Number.h"
Number::Number() {
    sf::Sprite temp;
    texture.emplace("numbers", TextureManager::GetTexture("numbers"));
    texture.emplace("mi", TextureManager::GetTexture("miles"));
    texture["mi"].setScale(0.45, 0.45);
    texture["numbers"].setScale(0.45, 0.45);
    for (int x = 0; x < 1243;) {
        texture["numbers"].setTextureRect(sf::IntRect(x,0, 155, 479));
        x += 138;
        digits.push_back(texture["numbers"]);
    }
    digits.push_back(texture["mi"]);
}

void Number::event(sf::RenderWindow &window) {
    window.draw(digits.at(10));
}