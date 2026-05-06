#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge
{
    int u, v, weight;
};

void bellmanFord(int V, int E, vector<Edge> &edges, int source)
{
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);

    dist[source] = 0;

    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    for (int j = 0; j < E; j++)
    {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].weight;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v])
        {
            cout << "There is a negative weight cycle in the graph\n";
            return;
        }
    }

    cout << "Vertex\tWeight\tPath\n";
    for (int i = 0; i < V; i++)
    {
        cout << i << "\t" << dist[i] << "\t\t";
        int curr = i;
        vector<int> path;

        while (curr != -1)
        {
            path.push_back(curr);
            curr = parent[curr];
        }

        for (int j = path.size() - 1; j >= 0; j--)
        {
            cout << path[j];
            if (j != 0)
            {
                cout << "->";
            }
        }
        cout << endl;
    }
}

int main()
{
    int v = 4;
    int e = 4;

    vector<Edge> edges = {
        {0, 1, 2},
        {1, 3, 5},
        {3, 2, 3},
        {2, 1, -10},
        {0, 3, 4}};
    int source = 0;
    bellmanFord(v, e, edges, source);
    return 0;
}