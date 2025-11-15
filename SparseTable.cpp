#include <bits/stdc++.h>

using namespace std;

struct SparseTable {
    int n, K;
    vector<int> lg;
    vector<vector<long long>> st;

    SparseTable() {}
    SparseTable(const vector<long long> &a) { build(a); }

    void build(const vector<long long> &a) {
        n = (int)a.size();
        K = 1;
        while ((1 << K) <= n) ++K;
        st.assign(K, vector<long long>(n));
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;

        for (int i = 0; i < n; ++i) st[0][i] = a[i];
        for (int k = 1; k < K; ++k) {
            for (int i = 0; i + (1 << k) <= n; ++i) {
                st[k][i] = min(st[k-1][i], st[k-1][i + (1 << (k-1))]);
            }
        }
    }

    long long query(int l, int r) { // inclusive
        int len = r - l + 1;
        int k = lg[len];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

int main(){
    
}