#include <bits/stdc++.h>
using namespace std;



struct Edge { int u, v; bool used; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<Edge> edges;
    edges.reserve(n);

    vector<vector<int>> adj(7); // các đỉnh từ 0..6
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        edges.push_back({x, y, false});
        adj[x].push_back(i);
        adj[y].push_back(i);
    }

    // Bậc
    vector<int> deg(7, 0);
    for (auto &e : edges) deg[e.u]++, deg[e.v]++;

    // kiểm tra tất cả bậc chẵn
    for (int i = 0; i < 7; ++i)
        if (deg[i] % 2) {
            cout << 0 << "\n";
            return 0;
        }

    // tìm đỉnh bắt đầu (đỉnh xuất hiện đầu tiên)
    int start = -1;
    for (int i = 0; i < 7; ++i)
        if (deg[i] > 0) { start = i; break; }
    if (start == -1) { cout << 1 << "\n"; return 0; } // không có domino nào

    // kiểm tra liên thông trong các đỉnh có bậc > 0
    vector<int> vis(7, 0);
    queue<int> q;
    q.push(start); vis[start] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto idx : adj[u]) {
            int v = (edges[idx].u == u ? edges[idx].v : edges[idx].u);
            if (!vis[v]) { vis[v] = 1; q.push(v); }
        }
    }
    for (int i = 0; i < 7; ++i)
        if (deg[i] > 0 && !vis[i]) {
            cout << 0 << "\n";
            return 0;
        }

    // Hierholzer không đệ quy cho đa đồ thị
    vector<int> st;
    vector<pair<int,int>> order; // lưu cặp (u,v) theo thứ tự duyệt
    st.push_back(start);

    vector<int> idx(7, 0);
    while (!st.empty()) {
        int u = st.back();
        while (idx[u] < (int)adj[u].size() && edges[adj[u][idx[u]]].used) idx[u]++;
        if (idx[u] == (int)adj[u].size()) {
            st.pop_back();
            if (!st.empty()) {
                int v = st.back();
                order.push_back({v, u});
            }
        } else {
            int id = adj[u][idx[u]];
            edges[id].used = true;
            int v = (edges[id].u == u ? edges[id].v : edges[id].u);
            st.push_back(v);
        }
    }

    // Nếu chưa dùng hết n cạnh => không chu trình
    int used_count = 0;
    for (auto &e : edges) if (e.used) used_count++;
    if (used_count != n) {
        cout << 0 << "\n";
        return 0;
    }

    // Có chu trình Euler
    cout << 1 << "\n";
    // In thứ tự các quân domino (đảo ngược để khớp thứ tự thật)
    reverse(order.begin(), order.end());
    for (auto &p : order) cout << p.first << " " << p.second << "\n";
    return 0;
}
