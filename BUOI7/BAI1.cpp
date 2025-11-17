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
    
    freopen("BAI1.inp", "r", stdin);
    freopen("BAI1.out", "w", stdout);
    
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
    
    // Kruskal algorithm
    for (const Edge& e : edges) {
        if (findSet(e.u) != findSet(e.v)) {
            unionSet(e.u, e.v);
            mst_weight += e.w;
            edges_used++;
            if (edges_used == n - 1) break;
        }
    }
    
    if (edges_used == n - 1) {
        cout << mst_weight << "\n";
    } else {
        cout << -1 << "\n"; // Đồ thị không liên thông
    }
    
    return 0;
}



