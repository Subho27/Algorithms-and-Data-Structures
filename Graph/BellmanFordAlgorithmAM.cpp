#include<bits/stdc++.h>
using namespace std;

vector<int> shortestDistanceBF(int src, int n, vector<vector<int>>& adjMat) {
    vector<int> distance(n, INT_MAX);
    distance[src] = 0;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<n; k++) {
                if(adjMat[j][k] != 0 && distance[j] != INT_MAX) {
                    distance[k] = min(distance[k], adjMat[j][k] + distance[j]);
                }
            }
        }
    }

    bool negativeCycle = false;
    for(int j=0; j<n; j++) {
        for(int k=0; k<n; k++) {
            if(adjMat[j][k] != 0 && distance[j] != INT_MAX && distance[k] > adjMat[j][k] + distance[j]) {
                negativeCycle = true;
                break;
            }
        }
    }

    if(negativeCycle) {
        cout << "There exists a negative cycle, so distances are not useful." << endl;
    }

    return distance;
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
    cout << "Shortest Distance with Bellman-Ford Algorithm : " << endl;
    vector<int> distance = shortestDistanceBF(0, n, adjMat);
    for(int i=0; i<n; i++) {
        cout << "0 -> " << i << " = " << distance[i] << endl;
    }
    return 0;
}