#include <bits/stdc++.h>

using namespace std;

#define ll long long 

struct DSU
{
  vector<int> pr,sz;
  void init(int n)
  {
    pr.resize(n+10);
    sz.resize(n+10);
    for(int i=0;i<=n;i++){
        pr[i]=i;
        sz[i]=1;
    }
  }

  int find(int x){
    if(x==pr[x])return x;
    return pr[x]=find(pr[x]);
  }

  bool unite(int x, int y){
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (sz[x]<sz[y]) swap(x, y);
    sz[x]+=sz[y];
    pr[y]=x;
    return true;
  }

  bool same(int x,int y){
    return find(x)==find(y);
  }

  int size(int x){
    return sz[find(x)];
  }
};

int main(){
}