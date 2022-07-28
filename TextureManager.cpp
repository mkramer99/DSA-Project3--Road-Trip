//
// Created by otish on 4/6/2022.
//

#include "TextureManager.h"
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName) {
    string text = "Project3/";
    text += fileName + ".png";
    textures[fileName].loadFromFile(text);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
    if (textures.find(textureName) == textures.end()) {
        LoadTexture(textureName);
    }

    return textures[textureName];
}