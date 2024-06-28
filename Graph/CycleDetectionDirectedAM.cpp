#include<bits/stdc++.h>
using namespace std;

bool cycleDetectionBFS(int n, vector<vector<int>>& adjMat) {
    unordered_map<int, int> inDegree;
    queue<int> q;

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(adjMat[i][j] == 1) {
                inDegree[j]++;
            }
        }
    }

    for(int i=0; i<n; i++) {
        if(inDegree[i] == 0) {
            q.push(i);
        }
    }
    int count = 0;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        count++;
        for(int i=0; i<n; i++) {
            if(adjMat[node][i] == 1) {
                inDegree[i]--;
                if(inDegree[i] == 0) {
                    q.push(i);
                }
            }
        }
    }
    if(count == n) return false;
    return true;
}

bool cycleDetectionDFS(int src, vector<int>& visited, vector<vector<int>>& adjMat, unordered_map<int, int>& active) {
    visited[src] = 1;
    active[src] = 1;
    for(int i=0; i<adjMat.size(); i++) {
        if(visited[i] == 0) {
            if(adjMat[src][i] != 0) {
                bool p = cycleDetectionDFS(i, visited, adjMat, active);
                if(p) return true;
            }
        } else {
            if(adjMat[src][i] != 0 && active[i] == 1)
                return true;
        }
    }
    active[src] = 0;
    return false;
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
    cout << "Cycle present in this graph (BFS) : ";
    int present = cycleDetectionBFS(n, adjMat);
    cout << ((present) ? "YES" : "NO") << endl;
    cout << "Cycle present in this graph (DFS) : ";
    vector<int> visited1(n, 0);
    unordered_map<int, int> active;
    present = false;
    for(int i=0; i<n; i++) {
        if(visited1[i] != 1 && cycleDetectionDFS(i, visited1, adjMat, active)) {
            present = true;
            break;
        }
    }
    cout << ((present) ? "YES" : "NO") << endl;
    return 0;
}