#include <bits/stdc++.h>

using namespace std;

struct Kuhn {
    int nL, nR;
    vector<vector<int>> g;   // g[u] = list of right vertices v
    vector<int> matchR;      // matchR[v] = u or -1
    vector<int> vis;         // used for DFS

    Kuhn(int nL, int nR) : nL(nL), nR(nR) {
        g.assign(nL, {});
        matchR.assign(nR, -1);
        vis.assign(nR, 0);
    }

    void add_edge(int u, int v) {
        // u in [0, nL), v in [0, nR)
        g[u].push_back(v);
    }

    bool dfs(int u, int vid) {
        for (int v : g[u]) {
            if (vis[v] == vid) continue;
            vis[v] = vid;
            if (matchR[v] == -1 || dfs(matchR[v], vid)) {
                matchR[v] = u;
                return true;
            }
        }
        return false;
    }

    int max_matching() {
        int matches = 0;
        int vid = 1;
        for (int u = 0; u < nL; ++u) {
            if (dfs(u, vid++)) ++matches;
        }
        return matches;
    }

    // Optional: get matchL (for left side)
    vector<int> get_matchL() {
        vector<int> matchL(nL, -1);
        for (int v = 0; v < nR; ++v) {
            if (matchR[v] != -1) matchL[matchR[v]] = v;
        }
        return matchL;
    }
};

int main(){
    int nL, nR, m;
    cin >> nL >> nR >> m;
    Kuhn kuhn(nL, nR);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v; // make sure it's 0-based or convert
        kuhn.add_edge(u, v);
    }
    int maxMatch = kuhn.max_matching();
    auto matchL = kuhn.get_matchL();

}
