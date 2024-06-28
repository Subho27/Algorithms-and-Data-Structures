#include<bits/stdc++.h>
using namespace std;

bool cycleDetectionBFS(int src, vector<int>& visited, unordered_map<int, vector<pair<int, int>>>& adjList) {
    unordered_map<int, int> parent;
    queue<int> q;
    q.push(src);
    visited[src] = 1;
    parent[src] = -1;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(auto nbr : adjList[node]) {
            if(visited[nbr.first] == 0) {
                visited[nbr.first] = 1;
                q.push(nbr.first);
                parent[nbr.first] = node;
            } else {
                if(parent[node] != nbr.first) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool cycleDetectionDFS(int src, vector<int>& visited, unordered_map<int, vector<pair<int, int>>>& adjList, int parent) {
    visited[src] = 1;
    for(auto nbr : adjList[src]) {
        if(visited[nbr.first] == 0) {
            bool p = cycleDetectionDFS(nbr.first, visited, adjList, src);
            if(p) return true;
        } else {
            if(parent != nbr.first) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    bool directed = false;
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
    cout << "Cycle present in this graph (BFS) : ";
    vector<int> visited(n, 0);
    bool present = false;
    for(int i=0; i<n; i++) {
        if(visited[i] != 1){
            present = cycleDetectionBFS(i, visited, adjList);
            break;
        }
    }
    cout << ((present) ? "YES" : "NO") << endl;
    cout << "Cycle present in this graph (DFS) : ";
    vector<int> visited1(n, 0);
    present = false;
    int parent = -1;
    for(int i=0; i<n; i++) {
        if(visited1[i] != 1) {
            present = cycleDetectionDFS(i, visited1, adjList, parent);
            break;
        }
    }
    cout << ((present) ? "YES" : "NO") << endl;
    return 0;
}