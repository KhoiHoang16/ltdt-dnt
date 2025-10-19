// DOTHINUAEULER.CPP
#include <bits/stdc++.h>
using namespace std;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<vector<long long>> a(n + 1, vector<long long>(n + 1, 0));
    vector<long long> deg(n + 1, 0);
    long long m2 = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            long long x; cin >> x;
            a[i][j] = x;
            deg[i] += x;
        }
        m2 += deg[i];
    }

    // không có cạnh nào => không coi là nửa Euler (không có đường đi dùng hết cạnh)
    if (m2 == 0) { cout << 0 << "\n"; return 0; }

    // tìm đỉnh bậc lẻ
    vector<int> odd;
    for (int i = 1; i <= n; ++i) if (deg[i] % 2) odd.push_back(i);

    // nửa Euler yêu cầu đúng 2 đỉnh bậc lẻ
    if ((int)odd.size() != 2) { cout << 0 << "\n"; return 0; }

    // kiểm tra liên thông trên tập đỉnh có bậc > 0
    int start_conn = -1;
    for (int i = 1; i <= n; ++i) if (deg[i] > 0) { start_conn = i; break; }
    vector<int> vis(n + 1, 0);
    stack<int> st;
    st.push(start_conn); vis[start_conn] = 1;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (int v = 1; v <= n; ++v) if (a[u][v] > 0 && !vis[v]) {
            vis[v] = 1; st.push(v);
        }
    }
    for (int i = 1; i <= n; ++i) if (deg[i] > 0 && !vis[i]) {
        cout << 0 << "\n"; return 0;
    }

    // chọn điểm bắt đầu: nếu 1 là đỉnh lẻ thì bắt đầu ở 1; ngược lại là odd[0] (nhỏ hơn)
    int s = (odd[0] == 1 || odd[1] == 1) ? 1 : min(odd[0], odd[1]);

    // Hierholzer không đệ quy cho ma trận kề
    vector<int> path; path.reserve(m2 + 5);
    vector<int> stk2; stk2.reserve(m2 + 5);
    vector<int> nxt(n + 1, 1);
    stk2.push_back(s);

    while (!stk2.empty()) {
        int u = stk2.back();
        int v = 0;
        for (int &j = nxt[u]; j <= n; ++j) if (a[u][j] > 0) { v = j; break; }
        if (v == 0) {
            path.push_back(u);
            stk2.pop_back();
        } else {
            a[u][v]--; a[v][u]--;
            stk2.push_back(v);
        }
    }
    reverse(path.begin(), path.end());

    // Với đồ thị nửa Euler, đường đi sẽ bắt đầu ở 1 trong 2 đỉnh lẻ, kết thúc ở đỉnh lẻ còn lại.
    // Nếu chưa bắt đầu ở 's', xoay lại (hiếm khi cần với cách chọn ở trên)
    if (!path.empty() && path.front() != s) {
        int k = -1;
        for (int i = 0; i < (int)path.size(); ++i) if (path[i] == s) { k = i; break; }
        if (k != -1) {
            vector<int> rot; rot.reserve(path.size());
            for (int i = 0; i < (int)path.size(); ++i) rot.push_back(path[(k + i) % path.size()]);
            path.swap(rot);
        }
    }

    // Xác thực dùng hết cạnh
    // (độ dài đường đi = số cạnh + 1; tổng bậc/2 = số cạnh)
    long long m = m2 / 2;
    if ((long long)path.size() != m + 1) { cout << 0 << "\n"; return 0; }

    cout << 1 << "\n";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << "\n";
    return 0;
}
