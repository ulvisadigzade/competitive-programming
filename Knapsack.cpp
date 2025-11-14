#include <bits/stdc++.h>

using namespace std;

// 0/1 knapsack (each item at most once)
// values and weights are 0..n-1, capacity = W
long long knap01(const vector<int> &w, const vector<long long> &v, int W) {
    const long long NEG_INF = (long long)-4e18;
    vector<long long> dp(W+1, NEG_INF);
    dp[0] = 0;
    int n = w.size();
    for (int i = 0; i < n; i++) {
        for (int cap = W; cap >= w[i]; cap--) {
            dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
        }
    }
    long long best = 0;
    for (int cap = 0; cap <= W; cap++) best = max(best, dp[cap]);
    return best;
}

//Unbounded knapsack (infinite copies)
long long unbounded_knap(const vector<int> &w, const vector<long long> &v, int W) {
    vector<long long> dp(W+1, 0);
    int n = w.size();
    for (int i = 0; i < n; i++) {
        for (int cap = w[i]; cap <= W; cap++) {
            dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
        }
    }
    return dp[W];
}

int main(){
    
}