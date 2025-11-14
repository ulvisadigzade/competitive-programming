#include <bits/stdc++.h>
using namespace std;


struct LCA {
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> adj;

    LCA(int n) : n(n) {
        LOG = 32 - __builtin_clz(n);
        up.assign(n, vector<int>(LOG));
        depth.assign(n, 0);
        adj.assign(n, {});
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p) {
        up[v][0] = p;
        for (int i = 1; i < LOG; i++)
            up[v][i] = up[ up[v][i-1] ][i-1];
        for (int u : adj[v]) if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }

    void build(int root = 0) {
        dfs(root, root);
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int diff = depth[a] - depth[b];
        for (int i = LOG-1; i >= 0; i--)
            if (diff & (1 << i))
                a = up[a][i];
        if (a == b) return a;
        for (int i = LOG-1; i >= 0; i--)
            if (up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        return up[a][0];
    }

    int dist(int a, int b) {
        int c = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }
};

//dist(a, b) = depth[a] + depth[b] - 2*depth[lca(a, b)]

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    LCA lca(n);

    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        lca.addEdge(u, v);
    }

    lca.build(0); // or whatever root you want

    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lca.lca(a, b) << "\n";
    }
 }

 //K-th node on path from A to B

 int lift(int v, int k, LCA &l) {
    for (int i = 0; i < l.LOG; i++)
        if (k & (1 << i))
            v = l.up[v][i];
    return v;
}

int kth_on_path(int a, int b, int k, LCA &l) {
    int c = l.lca(a, b);
    int da = l.depth[a] - l.depth[c];
    if (k <= da) return lift(a, k, l);
    int db = l.depth[b] - l.depth[c];
    int rest = k - da;
    return lift(b, db - rest, l);
}

//Is X on the path from A to B?
//X lies on path A–B iff
//dist(A,X) + dist(X,B) == dist(A,B)