#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL<<60);

struct DijkstraResult {
    vector<long long> dist;
    vector<int> trace;
};

DijkstraResult dijkstra(int n, const vector<vector<pair<int,int>>>& adj, int src) {
    vector<long long> dist(n+1, INF);
    vector<int> trace(n+1, -1);
    using P = pair<long long,int>; // (dist, node)
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > du + w) {
                dist[v] = du + w;
                trace[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return {move(dist), move(trace)};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t, x;
    if (!(cin >> n >> m >> s >> t >> x)) return 0;

    vector<vector<pair<int,int>>> adj(n+1);
    adj.reserve(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w; // có hướng, w >= 0
        adj[u].push_back({v, w});
    }

    // Dijkstra s->* và x->*
    auto fromS = dijkstra(n, adj, s);
    auto fromX = dijkstra(n, adj, x);

    if (fromS.dist[x] >= INF || fromX.dist[t] >= INF) {
        cout << 0 << " " << -1 << "\n";
        return 0;
    }

    // Khôi phục đường đi s -> x
    vector<int> path1;
    for (int cur = x; cur != -1; cur = fromS.trace[cur]) path1.push_back(cur);
    reverse(path1.begin(), path1.end()); // s ... x

    // Khôi phục đường đi x -> t
    vector<int> path2;
    for (int cur = t; cur != -1; cur = fromX.trace[cur]) path2.push_back(cur);
    reverse(path2.begin(), path2.end()); // x ... t

    // Ghép: s ... x + (bỏ x trùng) + ... t
    vector<int> path = path1;
    for (size_t i = 1; i < path2.size(); ++i) path.push_back(path2[i]);

    long long total = fromS.dist[x] + fromX.dist[t];

    cout << path.size() << " " << total << "\n";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << "\n";
    return 0;
}
