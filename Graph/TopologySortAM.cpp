#include<bits/stdc++.h>
using namespace std;

void topologySortBFS(int n, vector<vector<int>>& adjMat) {
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

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << ", ";
        for(int i=0; i<n; i++) {
            if(adjMat[node][i] == 1) {
                inDegree[i]--;
                if(inDegree[i] == 0) {
                    q.push(i);
                }
            }
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
    cout << "Topology Sort (BFS) : ";
    topologySortBFS(n, adjMat);
    cout << endl;
    cout << "Topology Sort (DFS) : ";
    vector<int> visited(n, 0);
    stack<int> topo;
    for(int i=0; i<n; i++) {
        if(visited[i] != 1) {
            topologySortDFS(i, visited, adjMat, topo);
        }
    }
    while(!topo.empty()) {
        cout << topo.top() << ", ";
        topo.pop();
    }
    return 0;
}