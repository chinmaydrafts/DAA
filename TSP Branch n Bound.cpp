#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int n;                                  // number of cities
vector<vector<int>> cost;               // cost matrix
int bestCost = INT_MAX;                 // best tour cost found so far
vector<int> bestPath;                   // best path (tour)

// compute a simple lower bound = current cost + sum of cheapest outgoing edges for unvisited cities
int lowerBound(const vector<int>& currPath, const vector<bool>& visited, int currCost) {
    int lb = currCost;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int mn = INT_MAX;
            for (int j = 0; j < n; j++) {
                if (i != j && cost[i][j] < mn)
                    mn = cost[i][j];
            }
            if (mn == INT_MAX) return INT_MAX;
            lb += mn;
        }
    }
    return lb;
}

void branchAndBoundTSP() {
    vector<int> currPath(n + 1, -1);
    vector<bool> visited(n, false);

    int level = 0;
    currPath[0] = 0;
    visited[0] = true;
    int currCost = 0;

    while (level >= 0) {
        if (level == n - 1) {
            if (cost[currPath[level]][0] != INT_MAX) {
                int tourCost = currCost + cost[currPath[level]][0];
                if (tourCost < bestCost) {
                    bestCost = tourCost;
                    bestPath = currPath;
                    bestPath[n] = 0;
                }
            }

            bool moved = false;
            while (level > 0 && !moved) {
                int from = currPath[level - 1];
                int last = currPath[level];
                visited[last] = false;
                currCost -= cost[from][last];

                int next = last + 1;
                moved = false;
                while (next < n) {
                    if (!visited[next] && cost[from][next] != INT_MAX) {
                        int newCost = currCost + cost[from][next];
                        currPath[level] = next;
                        visited[next] = true;
                        int lb = lowerBound(currPath, visited, newCost);
                        if (lb < bestCost) {
                            currCost = newCost;
                            moved = true;
                            break;
                        } else {
                            visited[next] = false;
                        }
                    }
                    next++;
                }
                if (!moved) {
                    level--;
                }
            }
            if (!moved && level == 0) {
                break;
            }
        } else {
            int from = currPath[level];
            int next = (level == 0 ? 1 : 0);
            bool moved = false;

            while (next < n) {
                if (!visited[next] && cost[from][next] != INT_MAX) {
                    int newCost = currCost + cost[from][next];
                    currPath[level + 1] = next;
                    visited[next] = true;

                    int lb = lowerBound(currPath, visited, newCost);
                    if (lb < bestCost) {
                        currCost = newCost;
                        level++;
                        moved = true;
                        break;
                    } else {
                        visited[next] = false;
                    }
                }
                next++;
            }

            if (!moved) {
                if (level == 0) break;
                int last = currPath[level];
                int prev = currPath[level - 1];
                visited[last] = false;
                currCost -= cost[prev][last];
                level--;
            }
        }
    }
}

int main() {
    cout << "Enter number of cities: ";
    cin >> n;
    cost.assign(n, vector<int>(n));
    cout << "Enter cost matrix (use a large number like 99999 for no edge):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    branchAndBoundTSP();

    if (bestCost == INT_MAX) {
        cout << "No Hamiltonian tour exists.\n";
    } else {
        cout << "Minimum cost: " << bestCost << endl;
        cout << "Path: ";
        for (int i = 0; i <= n; i++)
            cout << bestPath[i] << (i < n ? " -> " : "\n");
    }
    return 0;
}