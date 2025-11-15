#include <bits/stdc++.h>

using namespace std;

bool dfs_cycle(int v, const vector<vector<int>> &g, vector<int> &vis) {
    vis[v] = 1;
    for (int to : g[v]) {
        if (vis[to] == 0) {
            if (!dfs_cycle(to, g, vis)) return false;
        } else if (vis[to] == 1) {
            return false; // found cycle
        }
    }
    vis[v] = 2;
    return true;
}

bool is_dag(int n, const vector<vector<int>> &g) {
    vector<int> vis(n, 0);
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            if (!dfs_cycle(i, g, vis)) return false;
        }
    }
    return true;
}

int main(){

}
/*
When to use

Detect cycles in directed graph.

Check if DAG / topological sort possible.

Part of detecting infinite recursion / impossible constraints.

Mental model + common problems

Mental model: DFS with color:

0 = unvisited, 1 = visiting, 2 = done.

If from a vis=1 node you go to another vis=1 → cycle.

Typical:

“Is there a cycle in dependencies?”

Check if schedule / ordering exists.
*/