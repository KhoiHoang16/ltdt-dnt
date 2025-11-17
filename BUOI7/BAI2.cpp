#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

vector<int> parent, rank_set;

int findSet(int u) {
    if (parent[u] != u) {
        parent[u] = findSet(parent[u]);
    }
    return parent[u];
}

void unionSet(int u, int v) {
    u = findSet(u);
    v = findSet(v);
    if (u == v) return;
    
    if (rank_set[u] < rank_set[v]) {
        parent[u] = v;
    } else if (rank_set[u] > rank_set[v]) {
        parent[v] = u;
    } else {
        parent[v] = u;
        rank_set[u]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    freopen("BAI2.inp", "r", stdin);
    freopen("BAI2.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    
    // Khởi tạo DSU
    parent.resize(n + 1);
    rank_set.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    
    // Sắp xếp các cạnh theo trọng số
    sort(edges.begin(), edges.end());
    
    long long mst_weight = 0;
    int edges_used = 0;
    vector<pair<int, int>> mst_edges;
    
    // Kruskal algorithm
    for (const Edge& e : edges) {
        if (findSet(e.u) != findSet(e.v)) {
            unionSet(e.u, e.v);
            mst_weight += e.w;
            mst_edges.push_back({min(e.u, e.v), max(e.u, e.v)});
            edges_used++;
            if (edges_used == n - 1) break;
        }
    }
    
    if (edges_used == n - 1) {
        cout << mst_weight << "\n";
        cout << mst_edges.size() << "\n";
        sort(mst_edges.begin(), mst_edges.end());
        for (auto& edge : mst_edges) {
            cout << edge.first << " " << edge.second << "\n";
        }
    } else {
        cout << -1 << "\n";
    }
    
    return 0;
}



