#include<bits/stdc++.h>
using namespace std;

void dfs(int src, int parent, vector<int>& visited, unordered_map<int, vector<pair<int, int>>>& adjList,
            int& time, vector<int>& tin, vector<int>& low) {
    visited[src] = 1;
    tin[src] = time;
    low[src] = time;
    time++;

    for(auto nbr : adjList[src]) {
        if(parent == nbr.first) 
            continue;
        if(visited[nbr.first] == 0) {
            dfs(nbr.first, src, visited, adjList, time, tin, low);
            low[src] = min(low[src], low[nbr.first]);

            if(low[nbr.first] > tin[src]) {
                cout << src << "--" << nbr.first << " is a Bridge" << endl;
            }
        } else {
            low[src] = min(low[src], low[nbr.first]);
        }
    }
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
    cout << "Printing Bridges : " << endl;
    vector<int> visited(n, 0);
    vector<int> tin(n);
    vector<int> low(n);
    int time = 1;
    for(int i=0; i<n; i++) {
        if(visited[i] != 1)
            dfs(i, -1, visited, adjList, time, tin, low);
    }
    cout << endl;
    return 0;
}