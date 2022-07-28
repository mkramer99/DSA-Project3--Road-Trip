//
// Created by otish on 4/6/2022.
//
#include "string"
#include "iostream"
#include <map>
#include "vector"
#ifndef MINESWEEPER_FILEMANAGER_H
#define MINESWEEPER_FILEMANAGER_H

#endif //MINESWEEPER_FILEMANAGER_H
using std::string;
using std::map;

class FileManager {
public:
    void Config( map<string, int> &input);
    void TestFile(const string& testBoard);
    std::vector<int> Test;
};