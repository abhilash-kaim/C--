#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void dfs(int node, int parent, int& time, vector<int>& disc, vector<int>& low, vector<bool>& visited, unordered_map<int, vector<int>>& graph, vector<vector<int>>& result) {
    visited[node] = true;
    disc[node] = low[node] = ++time;

    for (int neighbor : graph[node]) {
        if (neighbor == parent) // Skip the parent node
            continue;

        if (!visited[neighbor]) {
            dfs(neighbor, node, time, disc, low, visited, graph, result);
            low[node] = min(low[node], low[neighbor]);

            if (low[neighbor] > disc[node])
                result.push_back({node, neighbor});
        }
        else {
            low[node] = min(low[node], disc[neighbor]);
        }
    }
}

vector<vector<int>> findCriticalConnections(int n, vector<vector<int>>& connections) {
    unordered_map<int, vector<int>> graph;
    for (const auto& conn : connections) {
        graph[conn[0]].push_back(conn[1]);
        graph[conn[1]].push_back(conn[0]);
    }

    vector<int> disc(n, -1);
    vector<int> low(n, -1);
    vector<bool> visited(n, false);
    vector<vector<int>> result;

    int time = 0;
    dfs(0, -1, time, disc, low, visited, graph, result);

    return result;
}

int main() {
    int n = 4;
    vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};

    vector<vector<int>> criticalConnections = findCriticalConnections(n, connections);

    cout << "Critical Connections:\n";
    for (const auto& conn : criticalConnections) {
        cout << "[" << conn[0] << ", " << conn[1] << "]\n";
    }

    return 0;
}
