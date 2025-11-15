#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    int n;
    vector<long long> tree, lazy;

    SegTree(int n) : n(n) {
        tree.assign(4*n, 0);
        lazy.assign(4*n, 0);
    }

    void build(const vector<long long> &a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            tree[v] = tree[v*2] + tree[v*2+1];
        }
    }

    void apply(int v, int tl, int tr, long long add) {
        tree[v] += add * (tr - tl + 1);
        lazy[v] += add;
    }

    void push(int v, int tl, int tr) {
        if (lazy[v] != 0) {
            int tm = (tl + tr) / 2;
            apply(v*2, tl, tm, lazy[v]);
            apply(v*2+1, tm+1, tr, lazy[v]);
            lazy[v] = 0;
        }
    }

    void update(int v, int tl, int tr, int l, int r, long long add) {
        if (l > r) return;
        if (l <= tl && tr <= r) {
            apply(v, tl, tr, add);
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        if (l <= tm) update(v*2, tl, tm, l, min(r, tm), add);
        if (r > tm)  update(v*2+1, tm+1, tr, max(l, tm+1), r, add);
        tree[v] = tree[v*2] + tree[v*2+1];
    }

    long long query(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l <= tl && tr <= r) return tree[v];
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        long long res = 0;
        if (l <= tm) res += query(v*2, tl, tm, l, min(r, tm));
        if (r > tm)  res += query(v*2+1, tm+1, tr, max(l, tm+1), r);
        return res;
    }
};

// vector<long long> a(n);
// SegTree st(n);
// st.build(a, 1, 0, n-1);
// st.update(1, 0, n-1, l, r, val);
// long long ans = st.query(1, 0, n-1, l, r);

