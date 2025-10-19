#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL<<60);



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    if (!(cin >> n >> m >> s >> t)) return 0;

    vector<vector<pair<int,int>>> adj(n+1);
    adj.reserve(n+1);

    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<long long> dist(n+1, INF);
    vector<int> trace(n+1, -1);

    using P = pair<long long,int>;              // (dist, node)
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du != dist[u]) continue;            // bỏ bản sao cũ
        if (u == t) break;                      // có thể dừng sớm

        for (auto [v, w] : adj[u]) {
            if (dist[v] > du + w) {
                dist[v] = du + w;
                trace[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[t] == INF) {
        cout << 0 << " " << -1 << "\n";
        return 0;
    }

    vector<int> path;
    for (int cur = t; cur != -1; cur = trace[cur]) path.push_back(cur);
    reverse(path.begin(), path.end());

    cout << path.size() << " " << dist[t] << "\n";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << "\n";
    return 0;
}
