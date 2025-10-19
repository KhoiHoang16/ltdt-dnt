// HAMILTON.CPP
#include <bits/stdc++.h>
using namespace std;


int n;
vector<vector<int>> a;
vector<int> path;
vector<int> used;
bool found = false;

void dfs(int pos) {
    if (found) return;
    if (pos == n) {
        // đủ n đỉnh, kiểm tra cạnh nối cuối -> đầu để thành chu trình
        if (a[path[n-1]][path[0]]) {
            found = true;
        }
        return;
    }
    int u = path[pos-1];
    // thử các v chưa dùng và kề u
    for (int v = 1; v <= n && !found; ++v) if (!used[v] && a[u][v]) {
        used[v] = 1; path[pos] = v;
        dfs(pos + 1);
        if (!found) used[v] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    a.assign(n + 1, vector<int>(n + 1, 0));
    vector<int> deg(n + 1, 0);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
            if (a[i][j]) deg[i]++;
        }

    // nếu đỉnh 1 cô lập thì chắc chắn không có chu trình Hamilton bắt đầu ở 1
    if (deg[1] == 0) {
        cout << 0 << "\n";
        return 0;
    }

    path.assign(n, 0);
    used.assign(n + 1, 0);

    // Bắt đầu từ đỉnh 1 (để khớp đề). Nếu muốn bắt đầu ở đỉnh khác, thay số 1 ở đây.
    path[0] = 1;
    used[1] = 1;

    // (nhẹ) cắt tỉa: mọi đỉnh phải có bậc >= 2 để có chu trình Hamilton (không đủ thì fail sớm)
    for (int i = 1; i <= n; ++i) {
        if (deg[i] < 2) {
            cout << 0 << "\n";
            return 0;
        }
    }

    dfs(1);

    if (!found) {
        cout << 0 << "\n";
        return 0;
    }

    cout << 1 << "\n";
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << ' ' << path[0] << "\n"; // đóng chu trình
    return 0;
}
