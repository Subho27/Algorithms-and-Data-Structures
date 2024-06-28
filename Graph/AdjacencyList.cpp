#include<bits/stdc++.h>
using namespace std;

void bfs(int src, vector<int>& visited, unordered_map<int, vector<pair<int, int>>>& adjList) {
    queue<int> q;
    q.push(src);
    visited[src] = 1;

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << ", ";
        for(auto nbr : adjList[node]) {
            if(visited[nbr.first] == 0) {
                visited[nbr.first] = 1;
                q.push(nbr.first);
            }
        }
    }
}

void dfs(int src, vector<int>& visited, unordered_map<int, vector<pair<int, int>>>& adjList) {
    visited[src] = 1;
    cout << src << ", ";
    for(auto nbr : adjList[src]) {
        if(visited[nbr.first] == 0) {
            dfs(nbr.first, visited, adjList);
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
    cout << "Printing BFS Traversal : ";
    vector<int> visited(n, 0);
    for(int i=0; i<n; i++) {
        if(visited[i] != 1)
            bfs(i, visited, adjList);
    }
    cout << endl;
    cout << "Printing DFS Traversal : ";
    vector<int> visited1(n, 0);
    for(int i=0; i<n; i++) {
        if(visited1[i] != 1)
            dfs(i, visited1, adjList);
    }
    cout << endl;
    return 0;
}