#include<bits/stdc++.h>
using namespace std;

vector<int> shortestDistanceDijkstra(int src, int n, vector<vector<int>>& adjMat) {
    vector<int> distance(n, INT_MAX);
    unordered_map<int, int> done;
    set<pair<int, int>> st;
    
    st.insert({0, src});
    distance[src] = 0;

    while(!st.empty()) {
        auto frontNode = *(st.begin());
        int node = frontNode.second;
        int weight = frontNode.first;

        st.erase(st.begin());
        done[node] = 1;

        for(int i=0; i<n; i++) {
            if(done[i] != 1 && adjMat[node][i] != 0 && distance[i] > weight + adjMat[node][i]) {
                auto result = st.find({distance[i], i});
                if(result != st.end()) {
                    st.erase(result);
                }
                distance[i] = weight + adjMat[node][i];
                st.insert({distance[i], i});
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
    cout << "Shortest Distance with Dijkstra Algorithm : " << endl;
    vector<int> distance = shortestDistanceDijkstra(0, n, adjMat);
    for(int i=0; i<n; i++) {
        cout << "0 -> " << i << " = " << distance[i] << endl;
    }
    return 0;
}