#include <bits/stdc++.h>

using namespace std;

#define ll long long 

struct SegTree {
    int n;
    vector<ll> tree;

    SegTree(int n) : n(n), tree(4 * (n + 1), 0) {}

    SegTree(const vector<ll> &a) : n(a.size()), tree(4 * (a.size() + 1), 0) {
        build(a, 1, 0, n - 1);
    }

    void build(const vector<ll> &a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(a, 2 * v, tl, tm);
        build(a, 2 * v + 1, tm + 1, tr);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    // Point update: set a[pos] = val
    void update(int v, int tl, int tr, int pos, ll val) {
        if (tl == tr) {
            tree[v] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(2 * v, tl, tm, pos, val);
        else
            update(2 * v + 1, tm + 1, tr, pos, val);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    // Range query on [l, r]
    ll query(int v, int tl, int tr, int l, int r) {
        if (l > r || tl > r || tr < l) return 0;
        if (l <= tl && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return query(2 * v, tl, tm, l, r) + query(2 * v + 1, tm + 1, tr, l, r);
    }

    // Convenient wrappers (0-indexed [0, n-1]):
    void update(int pos, ll val) { update(1, 0, n - 1, pos, val); }
    ll query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}