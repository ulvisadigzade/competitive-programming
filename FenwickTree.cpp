#include <bits/stdc++.h>

using namespace std;

#define ll long long 

struct Fenwick {
    int n;
    vector<ll> bit;

    Fenwick(int n) : n(n), bit(n+1, 0) {}

    void add(int i, ll v) {
        for (; i <= n; i += i & -i) bit[i] += v;
    }

    ll sum(int i) {
        long long s = 0;
        for (; i > 0; i -= i & -i) s += bit[i];
        return s;
    }

    ll range(int l, int r) { return sum(r) - sum(l-1); }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
 }

