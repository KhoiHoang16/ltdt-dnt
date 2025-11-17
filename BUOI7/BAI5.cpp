#include <bits/stdc++.h>
using namespace std;

// Bài 5: Tìm MST với Prim's algorithm (thay vì Kruskal)
// Hoặc có thể là bài tìm MST với số lượng cạnh tối đa

struct Edge {
    int v, w;
    bool operator>(const Edge& other) const {
        return w > other.w;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    freopen("BAI5.inp", "r", stdin);
    freopen("BAI5.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    // Prim's algorithm
    vector<bool> inMST(n + 1, false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    
    // Bắt đầu từ đỉnh 1
    pq.push({1, 0});
    long long mst_weight = 0;
    int vertices_in_mst = 0;
    
    while (!pq.empty() && vertices_in_mst < n) {
        Edge current = pq.top();
        pq.pop();
        
        int u = current.v;
        int weight = current.w;
        
        if (inMST[u]) continue;
        
        inMST[u] = true;
        mst_weight += weight;
        vertices_in_mst++;
        
        for (const Edge& e : adj[u]) {
            if (!inMST[e.v]) {
                pq.push(e);
            }
        }
    }
    
    if (vertices_in_mst == n) {
        cout << mst_weight << "\n";
    } else {
        cout << -1 << "\n"; // Đồ thị không liên thông
    }
    
    return 0;
}



