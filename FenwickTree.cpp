#include <bits/stdc++.h>

using namespace std;

#define ll long long 


struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    // O(n) build from 0-indexed array
    Fenwick(const vector<long long>& a) : Fenwick((int)a.size()) {
        for (int i = 1; i <= n; i++) {
            bit[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) bit[j] += bit[i];
        }
    }

    // a[i] += x, O(log n)
    void add(int i, long long x) {
        for (; i <= n; i += i & -i)
            bit[i] += x;
    }

    // Sum [1, i], O(log n)
    long long sum(int i) const {
        long long res = 0;
        for (; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }

    // Sum [l, r], O(log n)
    long long query(int l, int r) const {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }

    // a[i] = x, O(log n)
    void set(int i, long long x) {
        add(i, x - query(i, i));
    }

    // Smallest i with sum(i) >= k, O(log n)
    // Requires nonnegative point frequencies and 1 <= k <= sum(n).
    // Returns n+1 if k > sum(n).
    int kth(long long k) const {
        int pos = 0;
        long long pref = 0;

        int pw = 1;
        while (pw <= n / 2) pw <<= 1;

        for (; pw; pw >>= 1) {
            int nxt = pos + pw;
            if (nxt <= n && pref + bit[nxt] < k) {
                pos = nxt;
                pref += bit[nxt];
            }
        }
        return pos + 1;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
 }

