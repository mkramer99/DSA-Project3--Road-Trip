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

void ReformatGraph(Graph& temp) { // Adds entries for all nodes into Adjacency List, reducing complexity of the
                                  // algorithms - must be called before using Dijkstra() or BellmanFord().
    for (auto pair : temp.graph) {

        for (auto subPair : pair.second) {

            temp.graph[subPair.first].emplace(make_pair(pair.first, subpair.second));

        } // Previously, the only nodes which had entries in the Adjacency List were the ones listed as 'start'
          // nodes within the initially input data. After calling this, there will be entries for every node.
          // This significantly reduces the complexity of the algorithms, and thus their complexities align with
          // their 'textbook versions'.
    }

}

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

    temp.push(source); // Pushes source to the top of the stack to complete the path.

    return path;

}

stack<int> BellmanFord(map<int, vector<pair<int, float>>> graph, int source, int dest, int E) {

    int V = graph.size(); // Represents number of vertices.
    int d[V]; // Holds distances from the source vertex to each vertex in the array.

    for (int i = 0; i < V; i++) {

        d[i] = numeric_limits<int>::max(); // Sets each value in 'd' to 'infinity' (max integer value).

    }

    d[source] = 0;

    for (int i = 0; i < V - 1; i++) {

        for (int j = 0; j < E; j++) {



        }

    }

}