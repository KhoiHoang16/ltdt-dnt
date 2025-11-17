#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Kiểm tra xem có thể tô màu đỉnh v bằng màu c không
    bool isSafe(int v, int c, vector<int>& color) {
        for (int u : adj[v]) {
            if (color[u] == c) {
                return false;
            }
        }
        return true;
    }

    // Thuật toán backtracking để tìm số màu tối thiểu
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

    // Tìm số màu tối thiểu (chromatic number)
    vector<int> findOptimalColoring() {
        vector<int> color(V, -1);
        
        // Thử với số màu tăng dần từ 1 đến V
        for (int maxColors = 1; maxColors <= V; maxColors++) {
            fill(color.begin(), color.end(), -1);
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

    for (int i = 0; i < E; i++) {
        int u, v;
        inp >> u >> v;
        g.addEdge(u - 1, v - 1);
    }

    inp.close();

    // Sử dụng backtracking để tìm số màu tối thiểu
    vector<int> color = g.findOptimalColoring();

    int maxColor = *max_element(color.begin(), color.end()) + 1;

    out << maxColor << endl;
    for (int i = 0; i < V; i++) {
        out << "Dinh " << (i + 1) << ": Mau " << (color[i] + 1) << endl;
    }

    out.close();

    cout << "Da to mau do thi thanh cong (toi uu)!" << endl;
    cout << "So mau toi thieu: " << maxColor << endl;
    cout << "Ket qua da duoc ghi vao file out.txt" << endl;

    return 0;
}

