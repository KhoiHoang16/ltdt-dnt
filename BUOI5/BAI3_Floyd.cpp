#include <bits/stdc++.h>
using namespace std;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    const long long INF = (1LL << 60);
    vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));

    for (int i = 1; i <= n; ++i) d[i][i] = 0;

    for (int i = 0; i < m; ++i) {
        int u, v; long long w;
        cin >> u >> v >> w;
        if (w < d[u][v]) {               // có thể có đa cạnh
            d[u][v] = d[v][u] = w;       // vô hướng
        }
    }

    // Floyd–Warshall: O(n^3)
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            long long dik = d[i][k];
            if (dik == INF) continue;
            for (int j = 1; j <= n; ++j) {
                long long val = dik + d[k][j];
                if (val < d[i][j]) d[i][j] = val;
            }
        }
    }

    // In ma trận kết quả
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            long long out = d[i][j];
            if (out >= (INF >> 1)) out = 0;   // không có đường đi -> 0
            if (j > 1) cout << ' ';
            cout << out;
        }
        cout << '\n';
    }
    return 0;
}
