#include <bits/stdc++.h>

using namespace std;

struct DoubleHash {
    static const uint64_t MOD1 = (1ull<<61) - 1;
    static const uint64_t MOD2 = (1ull<<61) - 1; // we just rely on overflow, so same “mod”

    uint64_t base1, base2;
    vector<uint64_t> p1, h1, p2, h2;

    DoubleHash() {}

    DoubleHash(const string &s) { init(s); }

    void init(const string &s) {
        int n = s.size();
        uint64_t seed = chrono::steady_clock::now().time_since_epoch().count();
        base1 = (seed | 1);
        base2 = ((seed << 1) | 1);

        p1.assign(n+1, 0);
        h1.assign(n+1, 0);
        p2.assign(n+1, 0);
        h2.assign(n+1, 0);

        p1[0] = p2[0] = 1;
        for (int i = 0; i < n; i++) {
            unsigned char c = s[i] + 1;
            p1[i+1] = p1[i] * base1;
            p2[i+1] = p2[i] * base2;
            h1[i+1] = h1[i] * base1 + c;
            h2[i+1] = h2[i] * base2 + c;
        }
    }

    pair<uint64_t,uint64_t> get(int l, int r) const {
        uint64_t x1 = h1[r+1] - h1[l] * p1[r-l+1];
        uint64_t x2 = h2[r+1] - h2[l] * p2[r-l+1];
        return {x1, x2};
    }
};

int main(){
    
}