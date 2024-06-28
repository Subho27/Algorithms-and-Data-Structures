#include<bits/stdc++.h>
using namespace std;

void topologySortDFS(int src, vector<int>& visited, unordered_map<int, vector<pair<int, int>>>& adjList, stack<int>& topo) {
    visited[src] = 1;

    for(auto nbr : adjList[src]) {
        if(visited[nbr.first] != 1) {
            topologySortDFS(nbr.first, visited, adjList, topo);
        }
    }

    topo.push(src);
}

vector<int> shortestDistanceDFS(int n, unordered_map<int, vector<pair<int, int>>>& adjList, stack<int>& topo) {
    vector<int> distance(n, INT_MAX);
    distance[topo.top()] = 0;

    while (!topo.empty()) {
        int node = topo.top();
        topo.pop();

        for(auto nbr : adjList[node]) {
            if(distance[nbr.first] > distance[node] + nbr.second) {
                distance[nbr.first] = distance[node] + nbr.second;
            }
        }
    }
    
    return distance;
}

int main() {
    bool directed = true;
    bool weighted = false;
    int n = 0, e = 0;
    vector<vector<int>> edges;
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
    cout << "Printing shortest path distance from 0 : " << endl;
    vector<int> visited(n, 0);
    stack<int> topo;
    topologySortDFS(0, visited, adjList, topo);
    vector<int> distance = shortestDistanceDFS(n, adjList, topo);
    for(int i=0; i<n; i++) {
        cout << "0 -> " << i << " = " << distance[i] << endl;
    }
    return 0;
}