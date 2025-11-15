#include <bits/stdc++.h>

using namespace std;

const long long INF = (1LL << 60);

void floyd_warshall(int n, vector<vector<long long>> &dist) {
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;
                long long nd = dist[i][k] + dist[k][j];
                if (nd < dist[i][j]) dist[i][j] = nd;
            }
}


int main(){

}

/*
When to use

All-pairs shortest paths.

n small (≤ 400 typically).

Graph dense or edges roughly O(n^2).

Mental model + common problems

Mental model: dynamic programming on intermediate vertices: at step k, you allow paths using vertices 1..k.

Typical problems:

All-pair shortest path queries.

Find graph diameter on small graphs.

Detect negative cycles (check dist[i][i] < 0).

Compute transitive closure (bool instead of distance).
*/