#include<bits/stdc++.h>
using namespace std;

bool isBipartiteBFS(int src, vector<int>& color, unordered_map<int, vector<pair<int, int>>>& adjList, int currColor) {
    queue<int> q;
    q.push(src);
    color[src] = currColor;

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(auto nbr : adjList[node]) {
            if(color[nbr.first] == color[node]) {
                return false;
            } else if(color[nbr.first] == -1) {
                color[nbr.first] = 1 - color[node];
                q.push(nbr.first);
            }
        }
    }

    return true;
}

bool isBipartiteDFS(int src, vector<int>& color, unordered_map<int, vector<pair<int, int>>>& adjList, int currColor) {
    color[src] = currColor;
    for(auto nbr : adjList[src]) {
        if(color[nbr.first] == currColor) {
            return false;
        }
        if(color[nbr.first] == -1 && !isBipartiteDFS(nbr.first, color, adjList, 1-currColor)) {
            return false;
        }
    }
    return true;
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
    cout << "Is given graph Bipartite(BFS) : ";
    vector<int> color(n, -1);
    bool isBipartite = true;
    for(int i=0; i<n; i++) {
        if(color[i] == -1 && !isBipartiteBFS(i, color, adjList, 1)) {
            isBipartite = false;
        }
    }
    cout << isBipartite << endl;
    cout << endl;
    cout << "Is given graph Bipartite(DFS) : ";
    isBipartite = true;
    vector<int> color1(n, -1);
    for(int i=0; i<n; i++) {
        if(color1[i] == -1 && !isBipartiteDFS(i, color1, adjList, 1)) {
            isBipartite = false;
        }
    }
    cout << isBipartite << endl;
    cout << endl;
    return 0;
}