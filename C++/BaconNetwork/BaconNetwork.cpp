//
//  File:   BaconNetwork.cpp
//  Author: Landon Holmes
//  Purpose: Implementation of the adjacency list implementation of the graph ADT
//
#include "AdjListGraph.hpp"
#include "AdjMatrixGraph.hpp"
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <list>

using namespace std;

// Check if a path is a simple cycle
bool isSimpleCycle(Graph<string>& graph, const vector<string>& path) {
    if (path.size() < 3 || path.front() != path.back()) return false;

    vector<string> visited;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        if (!graph.adjacent(path[i], path[i + 1])) return false;
        if (find(visited.begin(), visited.end(), path[i]) != visited.end()) return false;
        visited.push_back(path[i]);
    }
    return true;
}

// Find path from start to "Kevin Bacon"
bool pathToKevinBacon(Graph<string>& graph, const string& start, list<string>& outPath) {
    map<string, string> cameFrom;
    map<string, bool> visited;
    queue<string> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        string current = q.front(); q.pop();
        if (current == "Kevin Bacon") {
            // Reconstruct path
            string node = current;
            while (node != start) {
                outPath.push_front(node);
                node = cameFrom[node];
            }
            outPath.push_front(start);
            return true;
        }
        for (const string& neighbor : graph.neighbors(current)) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                cameFrom[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    return false;
}

int main() {
    // Create graph
    AdjListGraph<string> socialGraph;
    vector<string> people = { "Landon", "Liam", "Olivia", "Carol", "David", "Noah", "Emma", "Oliver",
                             "Amelia", "Ivan", "Theodore", "Charlotte", "Leo", "Mallory", "James", "Mia",
                             "Elijah", "Isabella", "Isabella", "Kevin Bacon" };

    for (const auto& person : people)
        socialGraph.addNode(person);

    // Add some connections
    socialGraph.addEdge("Landon", "Liam");
    socialGraph.addEdge("Liam", "Olivia");
    socialGraph.addEdge("Olivia", "Carol");
    socialGraph.addEdge("Carol", "David");
    socialGraph.addEdge("David", "Kevin Bacon");

    // Test pathToKevinBacon
    list<string> path;
    if (pathToKevinBacon(socialGraph, "Landon", path)) {
        cout << "Connected to Kevin Bacon. Path: ";
        for (const string& name : path) cout << name << " ";
        cout << "\nKevin Bacon number: " << (path.size() - 1) << endl;
    }
    else {
        cout << "Not connected to Kevin Bacon.\n";
    }

    // Test isSimpleCycle
    vector<string> cyclePath = { "Liam", "Olivia", "Carol", "Liam" };
    bool isCycle = isSimpleCycle(socialGraph, cyclePath);
    cout << "The path Liam -> Olivia -> Carol -> Liam is "
        << (isCycle ? "a simple cycle." : "not a simple cycle.") << endl;

    return 0;
}
