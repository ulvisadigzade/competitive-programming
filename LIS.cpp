#include <bits/stdc++.h>

using namespace std;

int LIS(const vector<int> &a) {
    vector<int> d;
    for (int x : a) {
        auto it = lower_bound(d.begin(), d.end(), x);
        if (it == d.end()) d.push_back(x);
        else *it = x;
    }
    return (int)d.size();
}

int main(){
    /*
    For non-decreasing LIS → use upper_bound instead of lower_bound.
    “Subsequence, preserve order, maximize length, n up to 1e5, value range large” → this.
    
    */
    //Longers increasing subsequence
}