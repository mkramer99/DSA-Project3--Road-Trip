//
// Created by Melanie Kramer on 7/7/22.
//

#ifndef DSA_PROJECT3_GRAPH_H
#define DSA_PROJECT3_GRAPH_H

#endif //DSA_PROJECT3_GRAPH_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

class Graph {
public:
    int edgeid;
    int startnodeid;
    int endnodeid;
    float distance;
    map<int, vector<pair<int, float>>> graph;
    string edgesFile = "Edges-NA(edgeid, startnodeid, endnodeid, distance).txt";
    Graph();
};

Graph::Graph() {
    ifstream file;
    file.open(edgesFile);
    if (file.is_open()) {
        while (file >> edgeid) {
            file >> startnodeid;
            file >> endnodeid;
            file >> distance;
            graph[startnodeid].push_back(make_pair(endnodeid,distance));
        }
    }
    file.close();
}