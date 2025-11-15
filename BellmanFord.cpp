#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int u, v;
    long long w;
};

const long long INF = (1LL << 60);

bool bellman_ford(int n, int src, const vector<Edge> &edges, vector<long long> &dist) {
    dist.assign(n, INF);
    dist[src] = 0;
    for (int i = 0; i < n - 1; ++i) {
        bool changed = false;
        for (auto &e : edges) {
            if (dist[e.u] == INF) continue;
            long long nd = dist[e.u] + e.w;
            if (nd < dist[e.v]) {
                dist[e.v] = nd;
                changed = true;
            }
        }
        if (!changed) break;
    }
    // Check negative cycle reachable from src
    for (auto &e : edges) {
        if (dist[e.u] == INF) continue;
        if (dist[e.u] + e.w < dist[e.v]) {
            return false; // negative cycle
        }
    }
    return true; // no negative cycle
}

int main(){
}

    /*
    When to use

Single-source shortest paths with negative edges.

Need to detect a negative cycle reachable from source.

Graph sizes like n ≤ ~500, m ≤ ~5000 (ballpark).

Mental model + common problems

Mental model: Keep relaxing edges; if you can still improve after n-1 rounds → negative cycle.

Typical problems:

Currency arbitrage (cycle with product > 1 via log/negative weights).

“Is there a profitable cycle / time loop?” type problems.

Shortest path where Dijkstra isn’t valid because of negative edges.
    */
   