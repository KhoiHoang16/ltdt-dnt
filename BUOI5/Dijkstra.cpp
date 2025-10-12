#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL<<60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    if (!(cin >> n >> m >> s >> t)) return 0;

    vector<vector<pair<int,int>>> adj(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<long long> dist(n+1, INF);
    vector<int> par(n+1, -1), used(n+1, 0);
    dist[s] = 0;

    // Dijkstra O(n^2) – chọn đỉnh có dist nhỏ nhất chưa dùng
    for (int it = 1; it <= n; ++it) {
        int u = -1;
        long long best = INF;
        for (int i = 1; i <= n; ++i)
            if (!used[i] && dist[i] < best) best = dist[i], u = i;
        if (u == -1) break;
        used[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                par[v] = u;
            }
        }
    }

    if (dist[t] >= INF/2) {
        cout << "-1 -1\n\n";
        return 0;
    }

    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    cout << (int)path.size() << " " << dist[t] << "\n";
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << "\n";
    return 0;
}
