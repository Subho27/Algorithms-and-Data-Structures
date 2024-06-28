#include<bits/stdc++.h>
using namespace std;

void topologySortBFS(int n, unordered_map<int, vector<pair<int, int>>>& adjList) {
    unordered_map<int, int> inDegree;
    queue<int> q;

    for(auto nbrList : adjList) {
        for(auto nbr : nbrList.second) {
            inDegree[nbr.first]++;
        }
    }

    for(int i=0; i<n; i++) {
        if(inDegree[i] == 0) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << ", ";
        for(auto nbr : adjList[node]) {
            inDegree[nbr.first]--;
            if(inDegree[nbr.first] == 0) {
                q.push(nbr.first);
            }
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
    cout << "Topology Sort (BFS) : ";
    topologySortBFS(n, adjList);
    cout << endl;
    cout << "Topology Sort (DFS) : ";
    vector<int> visited(n, 0);
    stack<int> topo;
    for(int i=0; i<n; i++) {
        if(visited[i] != 1) {
            topologySortDFS(i, adjList, topo, visited);
        }
    }
    while(!topo.empty()) {
        cout << topo.top() << ", ";
        topo.pop();
    }
    return 0;
}