#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Graph {
private:
    int V; // Số đỉnh
    vector<vector<int>> adj; // Danh sách kề

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Thuật toán tô màu greedy
    vector<int> greedyColoring() {
        vector<int> color(V, -1); // Mảng lưu màu của mỗi đỉnh
        vector<bool> available(V, true); // Mảng đánh dấu màu có sẵn

        // Đỉnh đầu tiên được tô màu 0
        color[0] = 0;

        // Tô màu cho các đỉnh còn lại
        for (int u = 1; u < V; u++) {
            // Đánh dấu các màu đã được sử dụng bởi các đỉnh kề
            for (int v : adj[u]) {
                if (color[v] != -1) {
                    available[color[v]] = false;
                }
            }

            // Tìm màu đầu tiên có sẵn
            int cr;
            for (cr = 0; cr < V; cr++) {
                if (available[cr]) {
                    break;
                }
            }

            color[u] = cr; // Gán màu cho đỉnh u

            // Reset lại mảng available cho đỉnh tiếp theo
            for (int v : adj[u]) {
                if (color[v] != -1) {
                    available[color[v]] = true;
                }
            }
        }

        return color;
    }

    // Thuật toán tô màu với backtracking (tối ưu hơn)
    bool isSafe(int v, int c, vector<int>& color) {
        for (int u : adj[v]) {
            if (color[u] == c) {
                return false;
            }
        }
        return true;
    }

    bool graphColoringUtil(int v, int maxColors, vector<int>& color) {
        if (v == V) {
            return true;
        }

        for (int c = 0; c < maxColors; c++) {
            if (isSafe(v, c, color)) {
                color[v] = c;
                if (graphColoringUtil(v + 1, maxColors, color)) {
                    return true;
                }
                color[v] = -1; // Backtrack
            }
        }
        return false;
    }

    vector<int> backtrackingColoring() {
        vector<int> color(V, -1);
        
        // Thử với số màu tăng dần
        for (int maxColors = 1; maxColors <= V; maxColors++) {
            if (graphColoringUtil(0, maxColors, color)) {
                return color;
            }
        }
        return color;
    }

    int getV() {
        return V;
    }
};

int main() {
    ifstream inp("inp.txt");
    ofstream out("out.txt");

    if (!inp.is_open()) {
        cout << "Khong the mo file inp.txt" << endl;
        return 1;
    }

    if (!out.is_open()) {
        cout << "Khong the mo file out.txt" << endl;
        return 1;
    }

    int V, E;
    inp >> V >> E;

    Graph g(V);

    // Đọc các cạnh
    for (int i = 0; i < E; i++) {
        int u, v;
        inp >> u >> v;
        // Chuyển từ đánh số 1-based sang 0-based
        g.addEdge(u - 1, v - 1);
    }

    inp.close();

    // Sử dụng thuật toán greedy
    vector<int> color = g.greedyColoring();

    // Tìm số màu đã sử dụng
    int maxColor = *max_element(color.begin(), color.end()) + 1;

    // Ghi kết quả ra file
    out << maxColor << endl;
    for (int i = 0; i < V; i++) {
        out << "Dinh " << (i + 1) << ": Mau " << (color[i] + 1) << endl;
    }

    out.close();

    cout << "Da to mau do thi thanh cong!" << endl;
    cout << "So mau su dung: " << maxColor << endl;
    cout << "Ket qua da duoc ghi vao file out.txt" << endl;

    return 0;
}

