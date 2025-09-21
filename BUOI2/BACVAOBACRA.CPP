#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> a; // ma trận kề

// Hàm nhập từ file
void input(string fiName) {
    ifstream fi(fiName);
    fi >> n;

    a.assign(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fi >> a[i][j];
        }
    }

    fi.close();
}

// Hàm xử lý và xuất kết quả
void solve(string foName) {
    ofstream fo(foName);

    fo << n << endl;
    for (int i = 0; i < n; i++) {
        int indeg = 0, outdeg = 0;

        // Bậc ra = tổng hàng i
        for (int j = 0; j < n; j++) {
            outdeg += a[i][j];
        }

        // Bậc vào = tổng cột i
        for (int j = 0; j < n; j++) {
            indeg += a[j][i];
        }

        fo << indeg << " " << outdeg << endl;
    }

    fo.close();
}

int main() {
    input("BACVAOBACRA.INP");
    solve("BACVAOBACRA.OUT");
    return 0;
}
