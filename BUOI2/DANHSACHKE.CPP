#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int n;
vector<vector<int>> adj;

void input(string fiName) {
    ifstream fi(fiName);
    fi >> n;
    fi.ignore(); // bỏ ký tự xuống dòng sau số n

    adj.assign(n + 1, {}); // đánh số từ 1..n

    string line;
    for (int i = 1; i <= n; i++) {
        getline(fi, line);
        stringstream ss(line);
        int v;
        while (ss >> v) {
            adj[i].push_back(v);
        }
    }

    fi.close();
}

void solve(string foName) {
    ofstream fo(foName);

    fo << n << endl;
    for (int i = 1; i <= n; i++) {
        fo << adj[i].size() << endl;
    }

    fo.close();
}

int main() {
    input("DANHSACHKE.INP");
    solve("DANHSACHKE.OUT");
    return 0;
}
