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
    map<int, vector<pair<int, float>>> graph; // THE GRAPH
    map<int, vector<pair<float, float>>> cityNodes;
    map<string, int> cities; // hold indexed city node ids
    string edgesFile = "Edges-NA(edgeid, startnodeid, endnodeid, distance).txt";
    string nodesFile = "Nodes-NA(nodeid, normX, normY).txt";
    string citiesFile = "Cities";
    Graph();
    void LoadCities();
    void FindCities();
};

// create the graph
Graph::Graph() {
    ifstream file;
    file.open(edgesFile);
    if (file.is_open()) {
        cout << "File open." << endl;
        while (file >> edgeid) {
            file >> startnodeid;
            file >> endnodeid;
            file >> distance;
            graph[startnodeid].push_back(make_pair(endnodeid,distance));
            graph[endnodeid].push_back(make_pair(startnodeid,distance));
        }
    }
    file.close();
    cout << "Graph created." << endl;
    LoadCities();
}

// load the nodes to locate city locations
void Graph::LoadCities() {
    int nodeid;
    float latx;
    float lony;
    ifstream file;
    file.open(nodesFile);
    if (file.is_open()) {
        cout << "File open." << endl;
        while (file >> nodeid) {
            file >> latx;
            file >> lony;
            cityNodes[nodeid].push_back(make_pair(latx,lony));
        }
    }
    file.close();
    FindCities();
}

void Graph::FindCities() {
    // algo for finding closest node to predetermined lat/long
    string city;
    int lat;
    int lon;
    ifstream file;
    file.open(citiesFile);
    if (file.is_open()) {
        cout << "Cities file open." << endl;
        while (file >> city) {
            file >> lat;
            file >> lon;
            // find group of nodes within range
            map<int, vector<pair<float, float>>>::iterator itt;
            int range = 500;
            int temprange = 0;
            int closestNode;
            for (itt = cityNodes.begin(); itt != cityNodes.end(); itt++) {
                for (int j = 0; j < itt->second.size(); j++) {
                    // if lat is in range
                    if (itt->second[j].first > lat - 100 && itt->second[j].first < lat + 100) {
                        // if long is in range
                        if (itt->second[j].second > lon - 100 && itt->second[j].second < lon + 100) {
                            // get difference from the estimated normalized x y coordinates
                            temprange += abs(itt->second[j].first - lat);
                            temprange += abs(itt->second[j].second - lon);
                            if (temprange < range) {
                                // if node is closer than the current closest
                                closestNode = itt->first;
                                range = temprange;
                                temprange = 0;
                            }
                        }
                    }
                }
            }
            cities[city] = closestNode;
            cout << city << " " << closestNode << endl;
        }
    }
    file.close();
}
