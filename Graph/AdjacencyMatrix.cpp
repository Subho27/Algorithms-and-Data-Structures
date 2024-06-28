#include<bits/stdc++.h>
using namespace std;

void bfs(int src, vector<int>& visited, vector<vector<int>>& adjMat) {
    queue<int> q;
    q.push(src);
    visited[src] = 1;

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << ", ";
        for(int i=0; i<adjMat.size(); i++) {
            if(adjMat[node][i] != 0 && visited[i] == 0) {
                visited[i] = 1;
                q.push(i);
            }
        }
    }
}

void dfs(int src, vector<int>& visited, vector<vector<int>>& adjMat) {
    visited[src] = 1;
    cout << src << ", ";
    for(int i=0; i<adjMat.size(); i++) {
        if(adjMat[src][i] != 0 && visited[i] == 0) {
            dfs(i, visited, adjMat);
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
    vector<vector<int>> adjMat(n, vector<int>(n, 0));
    for(int i=0; i<e; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = (weighted) ? edges[i][2] : 1; 
        adjMat[u][v] = w;
        if(!directed) {
            adjMat[v][u] = w;
        } 
    }
    cout << "Printing graph with Adjacency Matrix : " << endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << adjMat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Printing BFS Traversal : ";
    vector<int> visited(n, 0);
    for(int i=0; i<n; i++) {
        if(visited[i] != 1)
            bfs(i, visited, adjMat);
    }
    cout << endl;
    cout << "Printing DFS Traversal : ";
    vector<int> visited1(n, 0);
    for(int i=0; i<n; i++) {
        if(visited1[i] != 1)
            dfs(i, visited1, adjMat);
    }
    cout << endl;
    return 0;
}