#include <iostream>
#include <vector>
using namespace std;

bool findHamiltonianPath(const vector<vector<int>>& graph, vector<int>& path) {
    int n = graph.size();
    path.assign(n, -1);

    vector<int> idx(n, 0);
    vector<int> used(n, 0);

    for (int start = 0; start < n; ++start) {
        fill(path.begin(), path.end(), -1);
        fill(idx.begin(), idx.end(), 0);
        fill(used.begin(), used.end(), 0);

        path[0] = start;
        used[start] = 1;
        int pos = 1;

        while (pos >= 1 && pos < n) {
            int prev = path[pos - 1];
            bool moved = false;

            for (int v = idx[pos]; v < n; ++v) {
                idx[pos] = v + 1;
                if (graph[prev][v] && !used[v]) {
                    path[pos] = v;
                    used[v] = 1;
                    pos++;
                    moved = true;
                    break;
                }
            }

            if (!moved) {
                idx[pos] = 0;
                pos--;
                if (pos >= 1) {
                    used[path[pos]] = 0;
                    path[pos] = -1;
                }
            }
        }

        if (pos == n) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> graph[i][j];

    vector<int> path;
    if (findHamiltonianPath(graph, path)) {
        cout << "Hamiltonian Path exists:\n";
        for (int i = 0; i < path.size(); ++i)
            cout << path[i] << (i + 1 < path.size() ? " -> " : "\n");
    } else {
        cout << "No Hamiltonian Path exists.\n";
    }
    return 0;
}