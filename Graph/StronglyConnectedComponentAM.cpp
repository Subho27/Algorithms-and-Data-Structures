#include<bits/stdc++.h>
using namespace std;

void dfs(int src, vector<int>& visited1, vector<vector<int>>& adjMat) {
    visited1[src] = 1;
    cout << src << ",";
    for(int i=0; i<adjMat[src].size(); i++) {
        if(!visited1[i] && adjMat[src][i] != 0) {
            dfs(i, visited1, adjMat);
        }
    }
}

void topologySortDFS(int src, vector<int>& visited, vector<vector<int>>& adjMat, stack<int>& topo) {
    visited[src] = 1;

    for(int i=0; i<adjMat[src].size(); i++) {
        if(adjMat[src][i] == 1 && visited[i] != 1) {
            topologySortDFS(i, visited, adjMat, topo);
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
    cout << "Printing SCCs : " << endl;
    vector<int> visited(n, 0);
    stack<int> topo;
    // First run the topological sort
    for(int i=0; i<n; i++) {
        if(visited[i] != 1) {
            topologySortDFS(i, visited, adjMat, topo);
        }
    }
    // Reverse all the directions of edges
    vector<vector<int>> revAdjMat(n, vector<int>(n, 0));
    for(int u=0; u<n; u++) {
        for(int v=0; v<n; v++) {
            if(adjMat[u][v] != 0) {
                revAdjMat[v][u] = adjMat[u][v];
            }
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
            dfs(node, visited1, revAdjMat);
            count++;
            cout << endl;
        }
    }
    cout << "Number of Strongly Connected Component : " << count << endl;
    return 0;
}