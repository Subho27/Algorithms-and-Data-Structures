#include <vector>
using namespace std;

struct UnionFind {
    vector<int> parent, rank;
    int components;

    UnionFind(int n) : components(n) {
        parent.resize(n);
        rank.resize(n, 1); 
        for (int i = 0; i < n; ++i) {
            parent[i] = i; 
        }
    }

    int find(int u) {
        if(u == parent[u]) {
            return u;
        }
        return parent[u] = find(parent[u]);
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] >= rank[rootV]) {
                parent[rootV] = rootU;
                rank[rootU] += rank[rootV];
            } else {
                parent[rootU] = rootV;
                rank[rootV] += rank[rootU];
            }
            components--; 
        }
    }

    int getComponents() const {
        return components;
    }
};