#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Number.h"
#include "vector"
#include <map>
#include <string>
#include <chrono>
#include "Point.h"
#include "Graph.h"
#include "Algorithms.h"
using namespace std;
using Clock = std::chrono::steady_clock;

int main() {
    //Variables
    int rangeD;
    int rangeB;
    int mileageD;
    int mileageB;
    int tankD;
    int tankB;
    string d;
    string b;
    cout << "Enter your electric vehicle's range per charge: ";
    cin >> rangeD;
    cout << endl << "Enter your gas vehicle's mileage per gallon: ";
    cin >> mileageD;
    cout << "Enter your car's tank size: ";
    cin >> tankD;
    tankB = tankD;
    rangeB = rangeD;
    mileageB = mileageD;
    sf::Event event;
    vector<sf::CircleShape> pins;
    unordered_map<string, pair<int, int>> cityLocations; // city, x, y
    map<string, int> cities;
    vector<string> userLocations;
    bool algo = false;
    float distanceD = 0.0;
    float distanceB = 0.0;

    //City Locations
    cityLocations["whitehorse"] = {815, 345};
    cityLocations["vancouver"] = {824, 505};
    cityLocations["anchorage"] = {824, 505};
    cityLocations["seattle"] = {821, 530};
    cityLocations["portland"] = {813, 551};
    cityLocations["sanfrancisco"] = {792, 650};
    cityLocations["losangeles"] = {816, 702};
    cityLocations["sandiego"] = {831, 726};
    cityLocations["niagarafalls"] = {1213, 583};
    cityLocations["chicago"] = {1131, 618};
    cityLocations["cleveland"] = {1193, 612};
    cityLocations["tampa"] = {1217, 788};
    cityLocations["orlando"] = {1230, 777};
    cityLocations["miami"] = {1245, 800};
    cityLocations["charlotte"] = {1221, 689};
    cityLocations["charleston"] = {1198, 649};
    cityLocations["philadelphia"] = {1252, 616};
    cityLocations["boston"] = {1284, 573};
    cityLocations["newyorkcity"] = {1254, 588};
    cityLocations["dc"] = {1242, 631};
    cityLocations["mexicocity"] = {1024, 895};
    cityLocations["cancun"] = {1173, 882};
    cityLocations["guadalajara"] = {966, 905};

    //Sprites + Resizing////////////////////////////////////////////////////////
    map<string, sf::Sprite> textureData;
    //Background
    textureData.emplace("background", TextureManager::GetTexture("background"));
    //Map
    textureData.emplace("america", TextureManager::GetTexture("america"));
    textureData["america"].setScale(0.6, 0.6);
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
    //Reset
    textureData.emplace("reset", TextureManager::GetTexture("reset"));
    textureData["reset"].setScale(0.26, 0.26);
    textureData["reset"].setPosition(400, 920);
    //Text
    sf::Font font;
    (font.loadFromFile("Project3/SSP.ttf"));
    string userInput;
    sf::String sfUserInput;
    sf::Text sfUserText;
    sf::Text dij;
    sf::Text bF;
    sfUserText.setFont(font);
    dij.setFont(font);
    bF.setFont(font);
    sfUserText.setStyle(sf::Text::Bold);
    sfUserText.setString(userInput);
    sfUserText.setCharacterSize(24);
    dij.setCharacterSize(24);
    bF.setCharacterSize(24);
    sfUserText.setFillColor(sf::Color::Black);
    dij.setFillColor(sf::Color::Black);
    bF.setFillColor(sf::Color::Black);


    //Window
    sf::RenderWindow window(sf::VideoMode(1444, 1080), "Road Trip");



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
            if (event.type == sf::Event::MouseButtonPressed) { // Clicking the box to queue the text box
                sf::Vector2i localPos = sf::Mouse::getPosition(window);

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
                    textBoxMode = 1;
                }
                sf::FloatRect endPos = textureData["end"].getGlobalBounds();
                if (endPos.contains(localPos.x, localPos.y)) {
                    userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end()); // erase whitespace
                    for (int i = 0; i < userInput.size(); i++) { // deals with alpha variants
                        if (isalpha(userInput.at(i))) {
                            userInput.at(i) = tolower(userInput.at(i));
                        }
                    }
                    userLocations.push_back(userInput);
                    endMode = 1;
                }
                sf::FloatRect resetPos = textureData["reset"].getGlobalBounds();
                if (resetPos.contains(localPos.x, localPos.y)) {
                    window.clear();
                    textBoxMode = 0;
                    optionsMode = 0;
                    destinationMode = 0;
                    endMode = 0;
                    pins.clear();
                    next = 0;
                    textY = 50;
                    okY = 0;
                    endY = 150;
                    algo = false;
                    userLocations.clear();
                }
            }
            //Text Box Activation
            if ((event.type == sf::Event::TextEntered && textBoxMode > 0) || (endMode == 1)) {
                if (event.text.unicode == '\b') { //backspace key is displayed figure out how to remove
                    sfUserInput.erase(sfUserInput.getSize()-1, 1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || (endMode == 1)) {
                    textY += 100;
                    userInput = sfUserInput;
                    userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end()); // erase whitespace
                    for (int i = 0; i < userInput.size(); i++) { // deals with alpha variants
                        if (isalpha(userInput.at(i))) {
                            userInput.at(i) = tolower(userInput.at(i));
                        }
                    }
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
        window.draw(textureData["start"]);
        window.draw(textureData["america"]);
        for (int i = 0; i < userLocations.size(); i++) {
            if (cityLocations.find(userLocations.at(i)) == cityLocations.end()) {

            }
            else {
                sf::CircleShape temp;
                temp.setFillColor(sf::Color(250, 70, 22));
                temp.setRadius(4);
                temp.setPosition(cityLocations[userLocations.at(i)].first, cityLocations[userLocations.at(i)].second);
                pins.push_back(temp);
            }
        }
        if (endMode == 1) { // End trip
            sf::VertexArray lines(sf::LineStrip, pins.size());
            for (int i = 0; i < pins.size(); i++) {
                int x1 = pins.at(i).getPosition().x;
                int y1 = pins.at(i).getPosition().y;
                lines[i].position = sf::Vector2f(x1, y1);
                lines[i].color = sf::Color(0, 33, 165);
            }

            if (!algo) {
                Graph g;
                auto tic = Clock::now();
                auto toc = Clock::now();
                cities = g.GetCities();
                tic = Clock::now();
                for (int i = 0; i < userLocations.size() - 1; i++) {
                    distanceD += Dijkstra(g.graph, cities[userLocations.at(i)], cities[userLocations.at(i + 1)]);
                }
                toc = Clock::now();
                d = to_string(duration_cast<std::chrono::milliseconds>(toc - tic).count());
                tic = Clock::now();
                for (int i = 0; i < userLocations.size() - 1; i++) {
                    distanceB += BellmanFord(g.graph, cities[userLocations.at(i)], cities[userLocations.at(i + 1)]);
                }
                toc = Clock::now();
                b = to_string(duration_cast<std::chrono::milliseconds>(toc - tic).count());
                algo = true;
            }
            window.draw(lines);
            string str0 = "Bellman-Ford Algorithm: ";
            string str1 = "Dijkstra's Algorithm: ";
            string str2 = " miles";
            string str3 = "(" ;
            string str4 = " ms, ";
            string str5 = " Number of charges: ";
            string str6 = ", Number of tanks: ";
            string str7 = ")";
            string dijkstra = str1 + to_string(distanceD) + str2 + '\n' + str3 + (d) + str4 + str5 +
                    to_string(distanceD / rangeD) + str6 + to_string((distanceD / mileageD) / tankD) + str7;
            string bellmanFord = str0 + to_string(distanceB) + str2 + '\n' + str3 + (b) + str4 + str5 +
                    to_string(distanceB / rangeB) + str6 + to_string((distanceB / mileageB) / tankB) + str7;
            dij.setString(dijkstra);
            bF.setString(bellmanFord);
            dij.setPosition(0, 800);
            bF.setPosition(0, 900);
            window.draw(dij);
            window.draw(bF);
        }
        for (int i = 0; i < pins.size(); i++) {
            if (destinationMode > 0)
            window.draw(pins.at(i));
        }
        window.draw(sfUserText);
        window.display();
    }
    return 0;
}
