#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int n, m;
vector<int> deg;

void input(string fiName) {
    ifstream fi(fiName);
    fi >> n >> m;
    deg.assign(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        fi >> u >> v;
        deg[u]++;
        deg[v]++;
    }

    fi.close();
}

void solve(string foName) {
    ofstream fo(foName);

    fo << n << endl;
    for (int i = 1; i <= n; i++) {
        fo << deg[i] << endl;
    }

    fo.close();
}

int main() {
    input("DANHSACHCANH.INP");
    solve("DANHSACHCANH.OUT");
    return 0;
}
