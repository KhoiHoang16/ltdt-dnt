#include <bits/stdc++.h>
using namespace std;


struct Circle { double x, y, r; };

struct Dist {
    int jumps;   // tiêu chí 1
    int nodes;   // tiêu chí 2
    bool operator<(Dist const& other) const {
        if (jumps != other.jumps) return jumps < other.jumps;
        return nodes < other.nodes;
    }
    bool operator>(Dist const& other) const {
        if (jumps != other.jumps) return jumps > other.jumps;
        return nodes > other.nodes;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S, T, N;
    if (!(cin >> S >> T >> N)) return 0;

    vector<Circle> a(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> a[i].x >> a[i].y >> a[i].r;
    }

    // Xây đồ thị (và loại cạnh theo rule)
    const double EPS = 1e-9;
    vector<vector<pair<int,int>>> adj(N + 1); // (v, type) type: 0=step, 1=jump

    auto gap_between = [&](int i, int j) -> double {
        double dx = a[i].x - a[j].x;
        double dy = a[i].y - a[j].y;
        double d = sqrt(dx*dx + dy*dy);
        double ri = a[i].r, rj = a[j].r;
        double gap;
        if (d >= ri + rj) gap = d - (ri + rj);
        else if (d <= fabs(ri - rj)) gap = fabs(ri - rj) - d;
        else gap = 0.0; // giao/tiếp nhau
        return gap;
    };

    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            double gap = gap_between(i, j);
            if (gap <= 60.0 + EPS) {
                int type = (gap > 50.0 + EPS) ? 1 : 0; // >50 → jump, else step
                adj[i].push_back({j, type});
                adj[j].push_back({i, type});
            }
        }
    }

    // Dijkstra đa tiêu chí (lexicographic) trên (jumps, nodes)
    const int INF = 1e9;
    vector<Dist> dist(N + 1, {INF, INF});
    vector<int> pre(N + 1, -1);      // truy vết đỉnh trước
    vector<int> preType(N + 1, -1);  // 0=step,1=jump (cạnh dùng tới đỉnh này)

    struct Node {
        Dist d; int u;
        bool operator<(Node const& other) const { // for min-heap via greater<>
            if (d.jumps != other.d.jumps) return d.jumps > other.d.jumps;
            return d.nodes > other.d.nodes;
        }
    };

    priority_queue<Node> pq;
    dist[S] = {0, 1}; // bắt đầu ở S (đã đi qua 1 hình tròn)
    pq.push({dist[S], S});

    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du.jumps != dist[u].jumps || du.nodes != dist[u].nodes) continue;
        if (u == T) break;

        for (auto [v, tp] : adj[u]) {
            Dist cand = { du.jumps + (tp == 1 ? 1 : 0), du.nodes + 1 };
            if (cand < dist[v]) {
                dist[v] = cand;
                pre[v] = u;
                preType[v] = tp;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[T].jumps >= INF) {
        cout << 0 << "\n";
        return 0;
    }

    // Khôi phục đường đi
    vector<int> path, edgeType; // edgeType[k] là loại cạnh đi từ path[k-1] -> path[k]
    for (int cur = T; cur != -1; cur = pre[cur]) {
        path.push_back(cur);
        if (cur != S) edgeType.push_back(preType[cur]);
    }
    reverse(path.begin(), path.end());
    reverse(edgeType.begin(), edgeType.end());

    cout << 1 << "\n";
    cout << dist[T].jumps << " " << dist[T].nodes << "\n";
    // In từng bước: "u c" từ S tới trước T
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        cout << path[i] << " " << edgeType[i] << "\n";
    }
    // Dòng cuối in T
    cout << path.back() << "\n";
    return 0;
}
