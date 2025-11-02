#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ull = unsigned long long;
using ld  = long double;

#define all(x)  (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb      push_back
#define mp      make_pair
#define fi      first
#define se      second
#define startt ios::sync_with_stdio(0);cin.tie(0); 
#define pii pair<int,int>
#define pll pair<ll,ll>

int di[8] = {1,0,-1,0,-1,1,-1,1};
int dj[8] = {0,1,0,-1,-1,1,1,-1};

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

#ifndef ONLINE_JUDGE
template<class T> void _dbg(const T &x){ cerr << x; }
template<class A, class B> void _dbg(const pair<A,B>& p){ cerr << '(' << p.first << ',' << p.second << ')'; }
template<class T> void _dbg(const vector<T>& v){ cerr << '['; for(size_t i=0;i<v.size();++i){ if(i) cerr << ','; _dbg(v[i]); } cerr << ']'; }
template<class T> void _dbg(const set<T>& s){ cerr << '{'; bool f=0; for(auto &x:s){ if(f) cerr<<','; f=1; _dbg(x); } cerr << '}'; }

template<class... Ts> void dbg_out(const char* names, Ts&&... ts){
    cerr << "[dbg] " << names << " = ";
    size_t n = 0;
    ((cerr << (n++?", ":""), _dbg(ts)), ...);
    cerr << '\n';
}
#define dbg(...) dbg_out(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...) ((void)0)
#endif

void solve(){
    
}

int main() {
    startt 
    int t=1;

    //cin>>t;
    while(t--){
        solve();
    }
}