#include<bits/stdc++.h>
using namespace std;

void dfs(int src, vector<int>& visited, unordered_map<int, vector<pair<int, int>>>& adjList) {
    visited[src] = 1;
    cout << src << ", ";
    for(auto nbr : adjList[src]) {
        if(visited[nbr.first] == 0) {
            dfs(nbr.first, visited, adjList);
        }
    }
}

void topologySortDFS(int src, unordered_map<int, vector<pair<int, int>>>& adjList, stack<int>& topo, vector<int>& visited) {
    visited[src] = 1;
    for(auto nbr : adjList[src]) {
        if(visited[nbr.first] == 0) {
            topologySortDFS(nbr.first, adjList, topo, visited);
        }
    }
    topo.push(src);
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
    cout << "Printing SCCs : " << endl;
    vector<int> visited(n, 0);
    stack<int> topo;
    // First run the topological sort
    for(int i=0; i<n; i++) {
        if(visited[i] != 1) {
            topologySortDFS(i, adjList, topo, visited);
        }
    }
    // Reverse all the directions of edges
    unordered_map<int, vector<pair<int, int>>> revAdjList;
    for(auto node : adjList) {
        for(auto nbr : node.second) {
            revAdjList[nbr.first].push_back({node.first, nbr.second});
        }
    }
    // Count number of disconnected component
    vector<int> visited1(n, 0);
    int count = 0, i = 1;
    while (!topo.empty()) {
        int node = topo.top();
        topo.pop();
        if(visited1[node] != 1) {
            cout << i++ << " SCC : ";
            dfs(node, visited1, revAdjList);
            count++;
            cout << endl;
        }
    }
    cout << "Number of Strongly Connected Component : " << count << endl;
    return 0;
}