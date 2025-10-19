#include <bits/stdc++.h>
using namespace std;



struct Node {
    long long d; int r, c;
    bool operator>(const Node& other) const {
        return d > other.d;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, XI, YI, XJ, YJ;
    if (!(cin >> N >> M >> XI >> YI >> XJ >> YJ)) return 0;

    vector<vector<int>> A(N+1, vector<int>(M+1, 0));
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cin >> A[i][j];

    auto inb = [&](int r, int c){ return 1 <= r && r <= N && 1 <= c && c <= M; };

    // Nếu start hoặc end là ô chặn (0) -> không đường đi
    if (A[XI][YI] == 0 || A[XJ][YJ] == 0) {
        cout << 0 << "\n";
        return 0;
    }

    const long long INF = (1LL<<60);
    vector<vector<long long>> dist(N+1, vector<long long>(M+1, INF));
    vector<vector<pair<int,int>>> pre(N+1, vector<pair<int,int>>(M+1, {-1,-1}));

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[XI][YI] = 0; // không tính chi phí ô đầu
    pq.push({0, XI, YI});

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (!pq.empty()) {
        auto [du, r, c] = pq.top(); pq.pop();
        if (du != dist[r][c]) continue;
        if (r == XJ && c == YJ) break;

        for (int k = 0; k < 4; ++k) {
            int nr = r + dr[k], nc = c + dc[k];
            if (!inb(nr, nc) || A[nr][nc] == 0) continue; // chỉ đi ô != 0

            long long w = (nr == XJ && nc == YJ) ? 0 : A[nr][nc]; // không tính ô cuối
            long long nd = du + w;
            if (nd < dist[nr][nc]) {
                dist[nr][nc] = nd;
                pre[nr][nc] = {r, c};
                pq.push({nd, nr, nc});
            }
        }
    }

    if (dist[XJ][YJ] == INF) {
        cout << 0 << "\n";
        return 0;
    }

    // Khôi phục đường đi
    vector<pair<int,int>> path;
    for (int r = XJ, c = YJ; r != -1; ) {
        path.push_back({r, c});
        auto p = pre[r][c];
        r = p.first; c = p.second;
    }
    reverse(path.begin(), path.end());

    cout << 1 << "\n";
    cout << dist[XJ][YJ] << "\n";
    for (auto &cell : path) {
        cout << cell.first << " " << cell.second << "\n";
    }
    return 0;
}
