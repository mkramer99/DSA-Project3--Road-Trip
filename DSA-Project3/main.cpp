#include <iostream>
#include "Graph.h"
#include "Algorithms.h"


int main() {
    // load the road network graph
    Graph g;
    // to test Dijkstra
    stack<int> path = Dijkstra(g.graph, 147477, 166505);
    int d = 0;
    while (!path.empty()) {
        d += path.top();
        path.pop();
    }
    cout << "distance in main: " << d << endl;
    //float path = Dijkstra(g.graph, 147477, 166504);
    //cout << path;
    return 0;
}
