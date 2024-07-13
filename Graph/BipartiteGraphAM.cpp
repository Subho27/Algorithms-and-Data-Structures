#include<bits/stdc++.h>
using namespace std;

bool isBipartiteBFS(int src, vector<int>& color, vector<vector<int>>& adjMat, int currColor) {
    queue<int> q;
    q.push(src);
    color[src] = currColor;

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(int i=0; i<adjMat.size(); i++) {
            if(adjMat[node][i] != 0) {
                if(color[i] == color[node]) {
                    return false;
                } else if(color[i] == -1) {
                    color[i] = 1 - color[node];
                    q.push(i);
                }
            }
        }
    }

    return true;
}

bool isBipartiteDFS(int src, vector<int>& color, vector<vector<int>>& adjMat, int currColor) {
    color[src] = currColor;
    for(int i=0; i<adjMat.size(); i++) {
        if(adjMat[src][i] != 0) {
            if(color[i] == currColor) {
                return false;
            }
            if(color[i] == -1 && !isBipartiteDFS(i, color, adjMat, 1-currColor)) {
                return false;
            }
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
    cout << "Is given graph Bipartite(BFS) : ";
    vector<int> color(n, -1);
    bool isBipartite = true;
    for(int i=0; i<n; i++) {
        if(color[i] == -1 && !isBipartiteBFS(i, color, adjMat, 1)) {
            isBipartite = false;
        }
    }
    cout << isBipartite << endl;
    cout << endl;
    cout << "Is given graph Bipartite(DFS) : ";
    isBipartite = true;
    vector<int> color1(n, -1);
    for(int i=0; i<n; i++) {
        if(color1[i] == -1 && !isBipartiteDFS(i, color1, adjMat, 1)) {
            isBipartite = false;
        }
    }
    cout << isBipartite << endl;
    cout << endl;
    return 0;
}