#include <iostream>
#include "Graph.h"
#include "Algorithms.h"


int main() {
    // load the road network graph
    Graph g;
    // run the program once and the city nodes will be printed to console
    // can run multiple tests with different locations by hardcoding
    // start and end nodes into the function calls
    // to test Dijkstra's
    float path = Dijkstra(g.graph, 147477, 166504);
    cout << "Dijkstra's: " << path << endl;
    // test Bellmans
    float p = BellmanFord(g.graph, 147477, 166504);
    cout << "BellmanFord: " << p << endl;
    return 0;
}
