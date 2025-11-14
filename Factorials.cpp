#include <bits/stdc++.h>

using namespace std;


vector<long long> fact, invfact;

long long modpow(long long a, long long e, long long mod) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return r;
}


long long inv(long long x, long long mod) {
    return modpow(x, mod - 2, mod);
}


void build_fact(int n, long long mod) {
    fact.resize(n+1);
    invfact.resize(n+1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % mod;
    invfact[n] = inv(fact[n], mod);
    for (int i = n; i > 0; i--) invfact[i-1] = invfact[i] * i % mod;
}

long long C(int n, int k, long long mod) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invfact[k] % mod * invfact[n-k] % mod;
}

int main(){

}