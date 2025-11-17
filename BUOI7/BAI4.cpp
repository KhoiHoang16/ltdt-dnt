#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool required;
    bool operator<(const Edge& other) const {
        if (required != other.required) {
            return required > other.required; // Cạnh bắt buộc được ưu tiên
        }
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
    
    freopen("BAI4.inp", "r", stdin);
    freopen("BAI4.out", "w", stdout);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].required = false;
    }
    
    // Đánh dấu các cạnh bắt buộc
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        for (Edge& e : edges) {
            if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
                e.required = true;
                break;
            }
        }
    }
    
    // Khởi tạo DSU
    parent.resize(n + 1);
    rank_set.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    
    // Thêm các cạnh bắt buộc trước
    long long mst_weight = 0;
    int edges_used = 0;
    
    for (const Edge& e : edges) {
        if (e.required) {
            if (findSet(e.u) != findSet(e.v)) {
                unionSet(e.u, e.v);
                mst_weight += e.w;
                edges_used++;
            }
        }
    }
    
    // Sắp xếp các cạnh còn lại theo trọng số
    sort(edges.begin(), edges.end());
    
    // Thêm các cạnh còn lại
    for (const Edge& e : edges) {
        if (!e.required && findSet(e.u) != findSet(e.v)) {
            unionSet(e.u, e.v);
            mst_weight += e.w;
            edges_used++;
            if (edges_used == n - 1) break;
        }
    }
    
    if (edges_used == n - 1) {
        cout << mst_weight << "\n";
    } else {
        cout << -1 << "\n"; // Không thể tạo MST với các ràng buộc
    }
    
    return 0;
}



