#include <bits/stdc++.h>
using namespace std;

const int NX = 100000;

vector<int> spf(NX + 1);   // spf[x] = smallest prime factor of x (spf[1] = 1)

void build_spf(){
    iota(spf.begin(), spf.end(), 0);   // spf[i] = i
    spf[0] = 0; spf[1] = 1;

    for(int i = 2; i * 1LL * i <= NX; ++i){
        if(spf[i] == i){               // i is prime
            for(long long j = 1LL * i * i; j <= NX; j += i){
                if(spf[j] == j) spf[j] = i; // set first time visited
            }
        }
    }
}
inline bool is_prime(int x){
    if(x <= 1) return false;
    return spf[x] == x;
}

// factorization in O(#prime factors)
vector<pair<int,int>> factorize(int x){
    vector<pair<int,int>> f;
    if(x<=1) return f;
    while(x > 1){
        int p = spf[x], c = 0;
        while(x % p == 0) x /= p, ++c;
        f.push_back({p, c});
    }
    return f;
}

// get all divisors from factorization
vector<long long> divisors_from_factorization(const vector<pair<int,int>>& f){
    vector<long long> divs = {1};
    for(auto [p, e] : f){
        int sz = (int)divs.size();
        long long cur = 1;
        for(int k=1;k<=e;++k){
            cur *= p;
            for(int i=0;i<sz;++i) divs.push_back(divs[i]*cur);
        }
    }
    return divs;
}
