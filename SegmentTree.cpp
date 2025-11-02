#include <bits/stdc++.h>

using namespace std;

#define ll long long 


vector<int>v;

struct Seg{
    vector<ll>seg;

    Seg(int sz){
        seg.resize(4*(sz+10));
    }

    // left inde, right index, seg index
    void build(int l,int r,int in){
        if(l==r){
            seg[in]=v[l];
            return;
        }
        int m = (l+r)/2;
        build(l,m,2*in);
        build(m+1,r,2*in+1);
        seg[in]=seg[2*in]+seg[2*in+1];
    }

    // current left, current right,left index,right index, segtree index;
    ll query(int ql,int qr,int l,int r,int in){
        if(ql>r || qr<l)return 0;
        if(ql>=l && qr<=r)return seg[in];
        int m = (ql+qr)/2;
        return query(ql,m,l,r,2*in)+query(m+1,qr,l,r,2*in+1);
    }

    //left index,right index,segtree index,chnage index,new element
    void update(int l,int r,int in,int ind,int nw){
        if(ind<l || ind>r)return;
        if(l==r){seg[in]=nw;return;}
        int m = (l+r)/2;
        if(ind<=m)update(l,m,2*in,ind,nw);
        else update(m+1,r,2*in+1,ind,nw);
        seg[in] = seg[2*in] + seg[2*in+1];
    }
};

int main(){
}