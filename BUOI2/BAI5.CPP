#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v;
    Edge(int _u, int _v) : u(_u), v(_v) {}
};

// 1. Ma trận kề → Danh sách kề
vector<vector<int>> matrixToAdjList(const vector<vector<int>>& mat) {
    int n = mat.size();
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j]) adj[i].push_back(j);
        }
    }
    return adj;
}

// 2. Ma trận kề → Danh sách cạnh
vector<Edge> matrixToEdgeList(const vector<vector<int>>& mat) {
    int n = mat.size();
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) { // đồ thị vô hướng
            if (mat[i][j]) edges.push_back(Edge(i, j));
        }
    }
    return edges;
}

// 3. Danh sách kề → Ma trận kề
vector<vector<int>> adjListToMatrix(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<vector<int>> mat(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int v : adj[i]) {
            mat[i][v] = 1;
        }
    }
    return mat;
}

// 4. Danh sách kề → Danh sách cạnh
vector<Edge> adjListToEdgeList(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<Edge> edges;
    vector<vector<bool>> mark(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        for (int v : adj[i]) {
            if (!mark[i][v] && !mark[v][i]) {
                edges.push_back(Edge(i, v));
                mark[i][v] = mark[v][i] = true;
            }
        }
    }
    return edges;
}

// 5. Danh sách cạnh → Ma trận kề
vector<vector<int>> edgeListToMatrix(int n, const vector<Edge>& edges) {
    vector<vector<int>> mat(n, vector<int>(n, 0));
    for (auto e : edges) {
        mat[e.u][e.v] = mat[e.v][e.u] = 1; // vô hướng
    }
    return mat;
}

// 6. Danh sách cạnh → Danh sách kề
vector<vector<int>> edgeListToAdjList(int n, const vector<Edge>& edges) {
    vector<vector<int>> adj(n);
    for (auto e : edges) {
        adj[e.u].push_back(e.v);
        adj[e.v].push_back(e.u);
    }
    return adj;
}

// In ma trận
void printMatrix(const vector<vector<int>>& mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat.size(); j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

// In danh sách kề
void printAdjList(const vector<vector<int>>& adj) {
    for (int i = 0; i < adj.size(); i++) {
        cout << i << ": ";
        for (int v : adj[i]) cout << v << " ";
        cout << endl;
    }
}

// In danh sách cạnh
void printEdgeList(const vector<Edge>& edges) {
    for (auto e : edges) {
        cout << "(" << e.u << "," << e.v << ") ";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n; // nhập số đỉnh
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }

    cout << "=== Ma tran ke goc ===" << endl;
    printMatrix(mat);

    // 1. Ma trận kề -> Danh sách kề
    auto adj1 = matrixToAdjList(mat);
    cout << "\nDanh sach ke (tu ma tran ke):" << endl;
    printAdjList(adj1);

    // 2. Ma trận kề -> Danh sách cạnh
    auto edges1 = matrixToEdgeList(mat);
    cout << "\nDanh sach canh (tu ma tran ke):" << endl;
    printEdgeList(edges1);

    // 3. Danh sách kề -> Ma trận kề
    auto mat2 = adjListToMatrix(adj1);
    cout << "\nMa tran ke (tu danh sach ke):" << endl;
    printMatrix(mat2);

    // 4. Danh sách kề -> Danh sách cạnh
    auto edges2 = adjListToEdgeList(adj1);
    cout << "\nDanh sach canh (tu danh sach ke):" << endl;
    printEdgeList(edges2);

    // 5. Danh sách cạnh -> Ma trận kề
    auto mat3 = edgeListToMatrix(n, edges1);
    cout << "\nMa tran ke (tu danh sach canh):" << endl;
    printMatrix(mat3);

    // 6. Danh sách cạnh -> Danh sách kề
    auto adj2 = edgeListToAdjList(n, edges1);
    cout << "\nDanh sach ke (tu danh sach canh):" << endl;
    printAdjList(adj2);

    return 0;
}
/*
========================cach chay code====================== 
bien dich: g++ Graph.cpp -o Graph.exe
Tạo file input ví dụ:

4
0 1 1 0
1 0 1 1
1 1 0 0
0 1 0 0
Chạy:

Graph.exe < input.txt
*/
