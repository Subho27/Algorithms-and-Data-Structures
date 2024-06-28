#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> shortestDistanceFW(int n, unordered_map<int, vector<pair<int, int>>>& adjList) {
    vector<vector<int>> distance(n, vector<int>(n, 1e9));
    for(int i=0; i<n; i++) {
        distance[i][i] = 0;
    }
    
    for(auto node : adjList) {
        for(auto nbr : node.second) {
            int u = node.first;
            int v = nbr.first;
            int w = nbr.second;
            distance[u][v] = w;
        }
    }

    for(int helper=0; helper<n; helper++) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                distance[i][j] = min(distance[i][j], distance[i][helper] + distance[helper][j]);
            }
        }
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
    cout << "All pair shortest Distance with Floyd Warshall Algorithm : " << endl;
    vector<vector<int>> distance = shortestDistanceFW(n, adjList);
    for(int i=-1; i<n; i++) {
        for(int j=-1; j<n; j++) {
            if(i == -1 && j == -1) cout << " - ";
            else if(i == -1) cout << " " << j << " ";
            else if(j == -1) cout << " " << i << " ";
            else cout << " " << distance[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}