#include<bits/stdc++.h>
using namespace std;

void dfs(int src, int parent, vector<int>& visited, vector<vector<int>>& adjMat,
            int& time, vector<int>& tin, vector<int>& low) {
    visited[src] = 1;
    tin[src] = time;
    low[src] = time;
    time++;

    for(int i=0; i<adjMat.size(); i++) {
        if(parent == i) 
            continue;
        if(adjMat[src][i] != 0 && visited[i] == 0) {
            dfs(i, src, visited, adjMat, time, tin, low);
            low[src] = min(low[src], low[i]);

            if(low[i] > tin[src]) {
                cout << src << "--" << i << " is a Bridge" << endl;
            }
        } 
        if(adjMat[src][i] != 0 && visited[i] == 1){
            low[src] = min(low[src], low[i]);
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
    cout << "Printing Bridges : " << endl;
    vector<int> visited(n, 0);
    vector<int> tin(n);
    vector<int> low(n);
    int time = 1;
    for(int i=0; i<n; i++) {
        if(visited[i] != 1)
            dfs(i, -1, visited, adjMat, time, tin, low);
    }
    cout << endl;
    return 0;
}