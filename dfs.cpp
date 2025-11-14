#include <bits/stdc++.h>

using namespace std;

void dfs(int v, int p, const vector<vector<int>> &g, vector<int> &vis) {
    vis[v] = 1;
    for (int u : g[v]) {
        if (u == p) continue;   // ignore parent for trees
        if (!vis[u]) dfs(u, v, g, vis);
    }
}


int main(){
    int n;
    vector<vector<int>> g(n);
    vector<int> vis(n, 0);

    dfs(1, -1, g, vis);
}