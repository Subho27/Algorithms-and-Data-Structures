#include<bits/stdc++.h>
using namespace std;

vector<int> shortestPathBFS(int src, int dest, vector<int>& visited, unordered_map<int, vector<pair<int, int>>>& adjList) {
    vector<int> parent(visited.size(), -1);
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
            }
        }
    }

    vector<int> shortest;
    int target = dest;
    shortest.push_back(target);
    while(parent[target] != -1) {
        shortest.push_back(parent[target]);
        target = parent[target];
    }

    reverse(shortest.begin(), shortest.end());

    return shortest;
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
    cout << "Printing Shortest Path (BFS) : ";
    vector<int> visited(n, 0);
    vector<int> path = shortestPathBFS(0, n-1, visited, adjList);
    cout << path[0];
    for(int i=1; i<path.size(); i++) {
        cout << " -> " << path[i]; 
    }
    cout << endl;
    return 0;
}