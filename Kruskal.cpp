#include <bits/stdc++.h>

using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n,1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

long long kruskal(int n, vector<array<int,3>> &edges) {
    sort(edges.begin(), edges.end(), [](auto &a, auto &b){
        return a[2] < b[2]; // sort by weight
    });

    DSU dsu(n);
    long long mst_cost = 0;

    for (auto &e : edges) {
        int u = e[0], v = e[1], w = e[2];
        if (dsu.unite(u, v)) {
            mst_cost += w;
        }
    }
    return mst_cost;
}

