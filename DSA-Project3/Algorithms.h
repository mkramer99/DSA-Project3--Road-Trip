//
// Created by Carlos Houghton on 25/07/2022.
//

#ifndef DSA_PROJECT3_ROAD_TRIP_DIJKSTRA_H
#define DSA_PROJECT3_ROAD_TRIP_DIJKSTRA_H

#endif //DSA_PROJECT3_ROAD_TRIP_DIJKSTRA_H

#include <limits>
#include <set>
#include <stack>
#include <map>
#include <vector>
#include <queue>
#include <chrono>
using namespace std::chrono;
using Clock = std::chrono::steady_clock;

// there are two Dijstra implementations
// the second one is utilized in main method
// first will be commented out



float BellmanFord(map<int, vector<pair<int, float>>> graph, int source, int dest) {
    cout << "Bellman Ford" << endl;
    auto tic = Clock::now();
    int V = graph.size(); // Represents number of vertices.
    float d[V]; // Holds distances from the source vertex to each vertex in the array.
    int p[V]; // Contains predecessor node indices, for finding the shortest path.
    set<int> S; // Computed vertices.
    float distance = 0;
    int nodes = 0;
    cout << "first for loop" << endl;
    for (int i = 0; i < V; i++) {
        d[i] = numeric_limits<int>::max(); // Sets each value in 'd' to 'infinity' (max integer value).
        p[i] = -1;
    }

    d[source] = 0;
    cout << "nested for loop" << endl;
    bool flag = true;
    while (flag == true) {
        for (int i = 0; i < V - 1; i++) { // Relaxes all edges in the graph |V - 1| times.
            for (auto pair: graph) { // Iterates through each entry in the Adjacency List.
                for (auto subPair: pair.second) { // Iterates through each entry in the corresponding vector.
                    if (d[pair.first] != numeric_limits<int>::max() &&
                        d[subPair.first] > (d[pair.first] + subPair.second)) {
                        d[subPair.first] = d[pair.first] + subPair.second;
                        p[subPair.first] = pair.first;
                        nodes++;
                        if (pair.first == dest) {
                            cout << "DESTINATION BELLMAN " << pair.first << endl;
                            cout << d[subPair.first] << " " << d[pair.first] << endl;
                            distance = d[subPair.first];
                            flag = false;
                            break;
                        }
                    }
                }
                if (flag == false) { break; }
            }
            if (flag == false) { break; }
        }
    }
    auto toc = Clock::now();
    cout << "elapsed time: " << duration_cast<std::chrono::milliseconds>(toc - tic).count() << endl;

    return distance;
}
                    
// MKramer                  
float Dijkstra(map<int, vector<pair<int, float>>> graph, int source, int dest) {
    cout << "entered Dijkstra" << endl;
    auto tic = Clock::now();
    int V = graph.size(); // Represents the number of vertices.
    set<int> S; // Computed vertices.
    set<int> VS; // Vertices to be computed.
    priority_queue<pair<int, float>> pq;

    for (auto pair: graph) {

        VS.emplace(pair.first);
    }
    cout << "VS initial size: " << VS.size() << endl;
    float d[V]; // Contains distances.
    int p[V]; // Contains predecessor node indices, for finding the shortest path.

    for (int i = 0; i < V; i++) {

        d[i] = numeric_limits<int>::max(); // Sets each value in 'd' to 'infinity' (max integer value).
        p[i] = -1;

    }
    cout << "numeric for loop complete" << endl;
    d[source] = 0;
    float distance = 0;
    int nodes = 0;
    int min = source; // 'min' tracks the closest node to source in 'VS', initially source itself.
    pq.push(make_pair(source, 0));
    while (!pq.empty()) {


        pair<int, float> curr = pq.top();
        pq.pop();
        int u = curr.first;
        for (auto it = graph[u].begin(); it != graph[u].end(); it++) {
            int v = it->first; // neighbor
            float w = it->second; // weight
            // if node not already checked
            if (S.find(v) == S.end()) {
                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    pq.push(make_pair(v, d[v]));

                    S.emplace(v);
                    VS.erase(V);
                    nodes++;
                    if (v == dest) {
                        cout << "DESTINATION" << endl;
                        cout << pq.size() << endl;
                        distance = d[v];
                        break;
                    }
                }
            }
        }
    }

    stack<int> path; // Represents the shortest path found; source on the top, destination on the bottom.
    path.push(dest); // Thus, destination is pushed first.
    cout << "distance: " << distance << endl;
    cout << "nodes checked: " << nodes << endl;

    auto toc = Clock::now();
    cout << "elapsed time: " << duration_cast<std::chrono::milliseconds>(toc - tic).count() << endl;
    return distance;
}
                    
