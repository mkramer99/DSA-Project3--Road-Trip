#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "FileManager.h"
#include "TextureManager.h"
#include "Number.h"
#include "vector"
#include <map>
#include <string>
//FIX ME: Introduce more classes, code is a bit hardcoded, make buttons their own entity
using namespace std;
int main() {
    sf::Event event;
    FileManager cfg;
    map<string, int> windowData;
    vector<string> userLocations;
    Number numbers;
    //cfg.Config(windowData);
    // have city name stay on gui
    // add x/y positions of cities on map


    //Sprites + Resizing////////////////////////////////////////////////////////
    map<string, sf::Sprite> textureData;
    //Map
    textureData.emplace("america", TextureManager::GetTexture("america"));
    textureData["america"].setScale(1.2, 1.2);
    textureData["america"].setPosition(500, 15);
    //Start Button
    textureData.emplace("start", TextureManager::GetTexture("start"));
    textureData["start"].setScale(0.45, 0.45);
    //Next1 Button
    textureData.emplace("next1", TextureManager::GetTexture("next"));
    textureData["next1"].setScale(0.45, 0.45);
    textureData["next1"].setPosition(-55, 100);
    //Next2 Button
    textureData.emplace("next2", TextureManager::GetTexture("next"));
    textureData["next2"].setScale(0.45, 0.45);
    textureData["next2"].setPosition(-55, 200);
    //Next3 Button
    textureData.emplace("next3", TextureManager::GetTexture("next"));
    textureData["next3"].setScale(0.45, 0.45);
    textureData["next3"].setPosition(-55, 300);
    //Next4 Button
    textureData.emplace("next4", TextureManager::GetTexture("next"));
    textureData["next4"].setScale(0.45, 0.45);
    textureData["next4"].setPosition(-55, 400);
    //Ok Button
    textureData.emplace("ok", TextureManager::GetTexture("ok"));
    textureData["ok"].setScale(0.45, 0.45);
    textureData["ok"].setPosition(-55, 100);
    //End Button
    textureData.emplace("end", TextureManager::GetTexture("end"));
    textureData["end"].setScale(0.45, 0.45);
    textureData["end"].setPosition(-55, 300);
    //Numbers
    textureData.emplace("numbers", TextureManager::GetTexture("numbers"));
    textureData["numbers"].setScale(0.45, 0.45);
    //Text
    sf::Font font;
    if (font.loadFromFile("Project3/SSP.ttf")) {

    }
    string userInput;
    sf::String sfUserInput;
    sf::Text sfUserText;
    sfUserText.setFont(font);
    sfUserText.setStyle(sf::Text::Regular);
    sfUserText.setString(userInput);
    sfUserText.setCharacterSize(24);
    sfUserText.setFillColor(sf::Color::Black);
    sfUserText.setString(userInput);
    //sfUserInput = userInput;
    //Text Box // https://en.sfml-dev.org/forums/index.php?topic=19965.0, Used Laurent's Code
    //Cursor
    sf::Clock clock;

    //Sprite Positioning (if needed)
    //textureData.at("debug").setPosition(448, ((windowData["height"] - 100) / 32) * 32);

    //Window
    sf::RenderWindow window(sf::VideoMode(1080, 870), "Road Trip");


    //Variables/Modes:
    int textBoxMode = 0; // 0 = start, 1 = next, 2 = next...
    int optionsMode = 0; // 0 = no options, 1 = display options
    int destinationMode = 0;
    int endMode = 0;
    int next = 0; // amount of next's
        //Positioning:
    int textY = 50;
    int okY = 0;
    int endY = 150;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            //Enter Text
            //FIX ME: Make this mode activated when the text box opens, and then close and save
            //the string to the vector
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // Clicking the box to queue the text box
                cout << "Left Click" << endl;
                sf::Vector2i localPos = sf::Mouse::getPosition(window);
                cout << localPos.x << " " << localPos.y << endl;

                sf::FloatRect startPos = textureData["start"].getGlobalBounds();
                if (startPos.contains(localPos.x, localPos.y)) {
                    sf::Uint8 light = 100;
                    textureData["start"].setColor(sf::Color(light, light, light));
                    textY += 100;
                    okY += 100;
                    textBoxMode = 1;
                }
                sf::FloatRect next1Pos = textureData["next1"].getGlobalBounds();
                if (next1Pos.contains(localPos.x, localPos.y) && textBoxMode != 1) {
                    okY += 100;
                    endY += 150;
                    optionsMode = 1;
                }
                sf::FloatRect next2Pos = textureData["next2"].getGlobalBounds();
                if (next2Pos.contains(localPos.x, localPos.y) && textBoxMode != 1) {
                    okY += 100;
                    endY += 100;
                    optionsMode = 1;
                }
                sf::FloatRect next3Pos = textureData["next3"].getGlobalBounds();
                if (next3Pos.contains(localPos.x, localPos.y) && textBoxMode != 1) {
                    okY += 100;
                    endY += 100;
                    optionsMode = 1;
                }
                sf::FloatRect next4Pos = textureData["next4"].getGlobalBounds();
                if (next4Pos.contains(localPos.x, localPos.y) && textBoxMode != 1) {
                    okY += 100;
                    endY += 100;
                    optionsMode = 1;
                }
                sf::FloatRect okPos = textureData["ok"].getGlobalBounds();
                if (okPos.contains(localPos.x, localPos.y)) {
                    if (clock.getElapsedTime() >= sf::milliseconds(500)) {
                        clock.restart();
                        sfUserInput.insert(sfUserInput.getSize(), '|');
                        sfUserText.setString(sfUserInput);
                    }
                    else {
                        sfUserInput.erase(sfUserInput.getSize(), 1);
                        sfUserText.setString(sfUserInput);
                    }
                    textBoxMode = 1;
                }
                sf::FloatRect endPos = textureData["end"].getGlobalBounds();
                if (endPos.contains(localPos.x, localPos.y)) {
                    endMode = 1;
                }
            }
            //Text Box Activation
            if (event.type == sf::Event::TextEntered && textBoxMode > 0) {
                if (event.text.unicode == '\b') { //backspace key is displayed figure out how to remove
                    sfUserInput.erase(sfUserInput.getSize()-1, 1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    textY += 100;
                    userInput = sfUserInput;
                    cout << userInput;
                    userLocations.push_back(userInput);
                    if (textBoxMode == 1) {
                        sfUserInput.clear();
                        destinationMode = 1;
                        next++;
                        textBoxMode = 0;
                        optionsMode = 0;
                    }
                }
                else {
                    sfUserInput += event.text.unicode;
                }
            }
            sfUserText.setString(sfUserInput);
            window.draw(sfUserText);
            window.display();
        }
        window.clear(sf::Color(255, 255, 255, 255));

        if (textBoxMode == 1) { // Allow User Text
            sfUserText.setPosition(50, textY);
            textureData["ok"].setPosition(-55, okY);
            window.draw(textureData["ok"]);
        }

        if (destinationMode == 1) { // Displays next option
            textureData["start"].setColor(sf::Color(255, 255, 255));
            window.draw(textureData["next1"]);
            if (next > 1) {
                textureData["next1"].setColor(sf::Color(255, 255, 255));
                window.draw(textureData["next2"]);
            }
            if (next > 2) {
                textureData["next2"].setColor(sf::Color(255, 255, 255));
                window.draw(textureData["next3"]);
            }
            if (next > 3) {
                textureData["next3"].setColor(sf::Color(255, 255, 255));
                window.draw(textureData["next4"]);
            }
        }

        if (optionsMode == 1) { // Type or end
            textureData["ok"].setPosition(-55, okY);
            textureData["end"].setPosition(-55, endY);
            if (next == 1) {
                textureData["next1"].setColor(sf::Color(100, 100, 100));
            }
            if (next == 2) {
                textureData["next2"].setColor(sf::Color(100, 100, 100));
            }
            if (next == 3) {
                textureData["next3"].setColor(sf::Color(100, 100, 100));
            }
            if (next == 4) {
                textureData["next4"].setColor(sf::Color(100, 100, 100));
            }
            window.draw(textureData["ok"]);
            window.draw(textureData["end"]);
            window.draw(textureData["next1"]);
        }
        if (endMode == 1) { // End trip
            break;
            //display some type of edge map
        }
        window.draw(textureData["start"]);
        window.draw(textureData["america"]);
        window.draw(sfUserText);
        window.display();
    }
    cout << "Dijkstra's Algorithm: " << "miles" << endl;
    cout << "(" << " ms, " << "nodes checked)" << endl;
    cout << "Bellman-Ford's Algorithm: " << "miles" << endl;
    cout << "(" << " ms, " << "nodes checked)" << endl;
    return 0;
}
/* Saved for future reference: if (event.type == sf::Event::MouseButtonPressed) {
                cout << "Mouse Pressed" << endl;
                if (event.key.code == sf::Mouse::Left) {
                    cout << "Left key pressed" << endl;
                }
            }*///tileData.otherHiddenTiles.at(i).tile.setTexture(
//TextureManager::GetTexture("tile_revealed"))