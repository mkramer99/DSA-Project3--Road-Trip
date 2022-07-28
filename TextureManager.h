//
// Created by otish on 4/6/2022.
//
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#pragma once
#ifndef MINESWEEPER_TEXTUREMANAGER_H
#define MINESWEEPER_TEXTUREMANAGER_H

#endif //MINESWEEPER_TEXTUREMANAGER_H
using std::unordered_map;
using std::string;

class TextureManager {
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName);

public:
    static sf::Texture& GetTexture(string textureName);
    static void Clear();
};