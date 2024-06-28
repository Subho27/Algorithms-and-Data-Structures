#include<bits/stdc++.h>
using namespace std;

vector<int> shortestDistanceBF(int src, int n, unordered_map<int, vector<pair<int, int>>>& adjList) {
    vector<int> distance(n, INT_MAX);
    distance[src] = 0;

    for(int i=0; i<n-1; i++) {
        for(auto node : adjList) {
            for(auto nbr : node.second) {
                int u = node.first;
                int v = nbr.first;
                int w = nbr.second;

                if(distance[u] != INT_MAX) {
                    distance[v] = min(distance[v], w + distance[u]);
                }
            }
        }
    }

    bool negativeCycle = false;
    for(auto node : adjList) {
        for(auto nbr : node.second) {
            int u = node.first;
            int v = nbr.first;
            int w = nbr.second;

            if(distance[u] != INT_MAX && distance[v] > w + distance[u]) {
                negativeCycle = true;
            }
        }
    }

    if(negativeCycle) {
        cout << "There exists a negative cycle, so distances are not useful." << endl;
    }

    return distance;
}

int main() {
    bool directed = false;
    bool weighted = false;
    int n = 0, e = 0;
    vector<vector<int>> edges;
    cout << "Enter 0 if graph is undirected and 1 otherwise : ";
    cin >> directed;
    cout << "Enter 0 if graph is not weighted and 1 otherwise : ";
    cin >> weighted;
    cout << "Enter number of nodes in graph : ";
    cin >> n;
    cout << "Enter number of edges in graph : ";
    cin >> e;
    for(int i=0; i<e; i++) {
        int u = 0, v = 0, w = 0;
        cin >> u >> v;
        vector<int> temp;
        temp.push_back(u);
        temp.push_back(v); 
        if(weighted) {
            cin >> w;
            temp.push_back(w);
        }
        edges.push_back(temp);
    }
    unordered_map<int, vector<pair<int, int>>> adjList;
    for(int i=0; i<e; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = (weighted) ? edges[i][2] : 1;
        adjList[u].push_back({v, w});
        if(!directed) {
            adjList[v].push_back({u, w});
        } 
    }
    cout << "Printing graph with Adjacency List : " << endl;
    for(int i=0; i<n; i++) {
        cout << i << " -> ";
        for(auto j : adjList[i]) {
            cout << "(" << j.first << ","  << j.second << ")" << ", ";
        }
        cout << endl;
    }
    cout << "Shortest Distance with Bellman-Ford Algorithm : " << endl;
    vector<int> distance = shortestDistanceBF(0, n, adjList);
    for(int i=0; i<n; i++) {
        cout << "0 -> " << i << " = " << distance[i] << endl;
    }
    return 0;
}