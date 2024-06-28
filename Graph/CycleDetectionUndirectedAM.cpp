#include<bits/stdc++.h>
using namespace std;

bool cycleDetectionBFS(int src, vector<int>& visited, vector<vector<int>>& adjMat, unordered_map<int, int>& parent) {
    queue<int> q;
    q.push(src);
    visited[src] = 1;
    parent[src] = -1;

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(int i=0; i<adjMat.size(); i++) {
            if(visited[i] == 0) {
                if(adjMat[node][i] != 0) {
                    visited[i] = 1;
                    parent[i] = node;
                    q.push(i);
                }
            } else {
                if(adjMat[node][i] != 0 && parent[node] != i) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool cycleDetectionDFS(int src, vector<int>& visited, vector<vector<int>>& adjMat, int parent) {
    visited[src] = 1;
    for(int i=0; i<adjMat.size(); i++) {
        if(visited[i] == 0) {
            if(adjMat[src][i] != 0) {
                bool p = cycleDetectionDFS(i, visited, adjMat, src);
                if(p) return true;
            }
        } else {
            if(adjMat[src][i] != 0 && parent != i)
                return true;
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
    cout << "Cycle present in this graph (BFS) : ";
    vector<int> visited(n, 0);
    unordered_map<int, int> parent;
    int present = false;
    for(int i=0; i<n; i++) {
        if(visited[i] != 1 && cycleDetectionBFS(i, visited, adjMat, parent)) {
            present = true;
            break;
        }
    }
    cout << ((present) ? "YES" : "NO") << endl;
    cout << "Cycle present in this graph (DFS) : ";
    vector<int> visited1(n, 0);
    int p = -1;
    present = false;
    for(int i=0; i<n; i++) {
        if(visited1[i] != 1 && cycleDetectionDFS(i, visited1, adjMat, p)) {
            present = true;
            break;
        }
    }
    cout << ((present) ? "YES" : "NO") << endl;
    return 0;
}