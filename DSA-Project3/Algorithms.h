//
// Created by Carlos Houghton on 25/07/2022.
//

#ifndef DSA_PROJECT3_ROAD_TRIP_DIJKSTRA_H
#define DSA_PROJECT3_ROAD_TRIP_DIJKSTRA_H

#endif //DSA_PROJECT3_ROAD_TRIP_DIJKSTRA_H

#include Graph.h
#include <limits>
#include <set>
#include <stack>

stack<int> Dijkstra(map<int, vector<pair<int, float>>> graph, int source, int dest) {

    int V = graph.size(); // Represents the number of vertices.

    set<int> S; // Computed vertices.
    set<int> VS; // Vertices to be computed.

    for (auto pair : graph) {

        VS.emplace(pair.first);

    }

    int d[V]; // Contains distances.
    int p[V]; // Contains predecessor node indices, for finding the shortest path.

    for (int i = 0; i < V; i++) {

        d[i] = numeric_limits<int>::max(); // Sets each value in 'd' to 'infinity' (max integer value).
        p[i] = -1;

    }

    d[source] = 0;

    int min = source; // 'min' tracks the closest node to source in 'VS', initially source itself.

    while (!VS.empty()) {

        for (auto pair : graph[min]) { // Checks nodes which graph[min] leads to.

            if (d[pair.first] > d[min] + pair.second) {

                d[pair.first] = d[min] + pair.second;
                p[pair.first] = min;

            }

        }

        S.emplace(min); // Adds minimum distance element to S.
        VS.erase(min); // Removes minimum distance element from VS.

        min = *(VS.begin()); // Resets min to help find new smallest distance in VS.

        for (auto arr : VS) {

            if (d[arr] < d[min]) {

                min = arr; // Finds next minimum distance from indices in VS.

            }

        }

    }

    stack<int> path; // Represents the shortest path found; source on the top, destination on the bottom.
    path.push(dest); // Thus, destination is pushed first.

    int temp = p[dest];

    while (temp != source) {

        path.push(temp);
        temp = p[temp];

    }

    path.push(source); // Pushes source to the top of the stack to complete the path.

    return path;

}

stack<int> BellmanFord(map<int, vector<pair<int, float>>> graph, int source, int dest, int E) {

    int V = graph.size(); // Represents number of vertices.
    int d[V]; // Holds distances from the source vertex to each vertex in the array.
    int p[V]; // Contains predecessor node indices, for finding the shortest path.

    for (int i = 0; i < V; i++) {

        d[i] = numeric_limits<int>::max(); // Sets each value in 'd' to 'infinity' (max integer value).
        p[i] = -1;

    }

    d[source] = 0;

    for (int i = 0; i < V - 1; i++) { // Relaxes all edges in the graph |V - 1| times.

        for (auto pair : graph) { // Iterates through each entry in the Adjacency List.

            for (auto subPair : pair.second) { // Iterates through each entry in the corresponding vector.

                if (d[pair.first] != numeric_limits<int>::max() && d[subPair.first] > (d[pair.first] + subPair.second) {

                    d[subPair.first] = d[pair.first] + subPair.second;
                    p[subPair.first] = pair.first;

                }

            }

        }

    }

    stack<int> path; // Represents the shortest path found; source on the top, destination on the bottom.
    path.push(dest); // Thus, destination is pushed first.

    int temp = p[dest];

    while (temp != source) {

        path.push(temp);
        temp = p[temp];

    }

    path.push(source); // Pushes source to the top of the stack to complete the path.

    return path;

}
