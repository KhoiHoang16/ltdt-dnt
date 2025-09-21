#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define FI "MATRANKE.INP"
#define FO "MATRANKE.OUT"

void solve() {
    ifstream fi(FI);
    ofstream fo(FO);

    int n;
    fi >> n;  // đọc số đỉnh

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fi >> a[i][j];
        }
    }

    // Tính bậc các đỉnh và ghi ra file
    fo << n << endl;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++) {
            deg += a[i][j];
        }
        fo << deg << endl;
    }

    fi.close();
    fo.close();
}

int main() {
    solve(); // chỉ cần gọi hàm
    return 0;
}
