#include <bits/stdc++.h>
using namespace std;

struct Z {
    static int MOD;
    int v;

    Z(long long _v = 0) {
        v = int((_v % MOD + MOD) % MOD); 
    }

    Z& operator+=(const Z &o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    Z& operator-=(const Z &o) { if ((v -= o.v) <  0 ) v += MOD; return *this; }
    Z& operator*=(const Z &o) { v = int((1LL * v * o.v) % MOD); return *this; }
    Z& operator++(){ if(++v==MOD) v=0; return *this; }
    Z operator++(int){ Z t=*this; ++(*this); return t; }
    Z& operator--(){ if(v==0) v=MOD-1; else --v; return *this; }
    Z operator--(int){ Z t=*this; --(*this); return t; }


    static Z pow(Z a, long long e) {
        Z r = 1;
        while (e) { if (e & 1) r *= a; a *= a; e >>= 1; }
        return r;
    }
    static Z inv(Z a) { return pow(a, MOD - 2); }

    Z& operator/=(const Z &o) { return (*this) *= inv(o); }

    friend Z operator+(Z a, const Z &b) { return a += b; }
    friend Z operator-(Z a, const Z &b) { return a -= b; }
    friend Z operator*(Z a, const Z &b) { return a *= b; }
    friend Z operator/(Z a, const Z &b) { return a /= b; }
    friend bool operator==(const Z& a, const Z& b){ return a.v==b.v; }
    friend bool operator!=(const Z& a, const Z& b){ return a.v!=b.v; }

    friend ostream& operator<<(ostream& os, const Z& a) { return os << a.v; }
    friend istream& operator>>(istream& is, Z& a) { long long x; is >> x; a = Z(x); return is; }
};

int main(){
    Z::MOD = 1e9+7;

    Z a = 3434;
}