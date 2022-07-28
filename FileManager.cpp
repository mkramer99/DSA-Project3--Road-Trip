//
// Created by otish on 4/6/2022.
//
#include "fstream"
#include "FileManager.h"
using std::ifstream;
using std::invalid_argument;

void FileManager::Config(map<string, int> &input) {
    string placeHolder;
    int width;
    int height;
    int mines;
    int tiles;
    ifstream file("boards/config.cfg");
    while (!file.eof()) {
        getline(file, placeHolder);
        try {
            width = stoi(placeHolder) * 32;
        }
        catch (invalid_argument const&) {
            width = 0;
        }
        input.emplace("width", width);
        getline(file, placeHolder);
        try {
            height = (stoi(placeHolder) * 32) + 100;
        }
        catch (invalid_argument const&) {
            height = 0;
        }
        input.emplace("height", height);
        getline(file, placeHolder);
        try {
            mines = stoi(placeHolder);
        }
        catch (invalid_argument const&) {
            mines = 0;
        }
        input.emplace("mines", mines);
        tiles = (width/32) * (height - 100)/32;
        input.emplace("tiles", tiles);
    }
}

void FileManager::TestFile(const string &testBoard) {
    Test.clear();
    string whatever;
    int value;
    ifstream file(testBoard);
    while (!file.eof()) {
        getline(file, whatever, '\n');
        for (int i = 0; i < whatever.size(); i++) {
            value = (int)whatever.at(i) - 48;
            Test.push_back(value);
        }

    }
}