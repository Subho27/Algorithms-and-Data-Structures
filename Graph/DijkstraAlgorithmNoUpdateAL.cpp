#include<bits/stdc++.h>
using namespace std;

vector<int> shortestDistanceDijkstra(int src, int n, unordered_map<int, vector<pair<int, int>>>& adjList) {
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

        for(auto nbr : adjList[node]) {
            if(done[nbr.first] != 1 &&distance[nbr.first] > weight + nbr.second) {
                auto result = st.find({distance[nbr.first], nbr.first});
                if(result != st.end()) {
                    st.erase(result);
                }
                distance[nbr.first] = weight + nbr.second;
                st.insert({distance[nbr.first], nbr.first});
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
    cout << "Shortest Distance with Dijkstra Algorithm : " << endl;
    vector<int> distance = shortestDistanceDijkstra(0, n, adjList);
    for(int i=0; i<n; i++) {
        cout << "0 -> " << i << " = " << distance[i] << endl;
    }
    return 0;
}