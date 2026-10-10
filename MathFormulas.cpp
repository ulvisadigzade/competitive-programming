#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ==========================================
// 1. EXTENDED EUCLIDEAN & MODULAR INVERSE
// ==========================================

// Solves: a*x + b*y = gcd(a, b)
// Returns g = gcd(a, b). x and y are populated with one valid solution.
ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

// Modular Inverse for ANY modulus m (even if m is NOT prime!):
// Solves: a * x = 1 (mod m). Returns x in [0, m-1], or -1 if no inverse exists (i.e. gcd(a, m) != 1).
ll mod_inv(ll a, ll m) {
    ll x, y;
    ll g = extgcd(a, m, x, y);
    if (g != 1) return -1; // inverse doesn't exist
    return (x % m + m) % m;
}

// Solves Linear Diophantine Equation: a*x + b*y = c
// If no solution exists, returns false.
// Otherwise returns true, and (x0, y0) is one particular solution.
// All solutions: x = x0 + k*(b/g), y = y0 - k*(a/g) for any integer k.
bool solve_diophantine(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = extgcd(abs(a), abs(b), x0, y0);
    if (c % g != 0) return false;
    x0 *= (c / g);
    y0 *= (c / g);
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

// ==========================================
// 2. CHINESE REMAINDER THEOREM (GENERAL CRT)
// ==========================================
// Solves system of congruences:
//   x = r1 (mod m1)
//   x = r2 (mod m2)
// Handles non-coprime m1, m2!
// Returns {rem, mod} where x = rem (mod mod), or {-1, -1} if no solution exists.
pair<ll, ll> crt(ll r1, ll m1, ll r2, ll m2) {
    ll x, y;
    ll g = extgcd(m1, m2, x, y);
    if ((r2 - r1) % g != 0) return {-1, -1}; // no solution
    ll mod = m1 / g * m2;
    ll step = (r2 - r1) / g % (m2 / g);
    ll ans = (r1 + (__int128)x * step % (m2 / g) * m1) % mod;
    return {(ans % mod + mod) % mod, mod};
}

// Multi-congruence CRT: merges list of {remainder, modulo}
pair<ll, ll> crt_all(const vector<pair<ll, ll>> &congruences) {
    ll r = 0, m = 1;
    for (auto [r_i, m_i] : congruences) {
        auto res = crt(r, m, r_i, m_i);
        if (res.second == -1) return {-1, -1};
        r = res.first;
        m = res.second;
    }
    return {r, m};
}

// ==========================================
// 3. EULER'S TOTIENT FUNCTION (phi)
// ==========================================

// phi(n) = number of integers 1 <= k <= n such that gcd(k, n) = 1
// Complexity: O(sqrt(n))
ll phi(ll n) {
    ll result = n;
    for (ll p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// Sieve to compute phi for all numbers 1..N in O(N log log N)
vector<int> phi_sieve(int n) {
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    for (int i = 2; i <= n; i++) {
        if (p[i] == i) { // i is prime
            for (int j = i; j <= n; j += i)
                p[j] -= p[j] / i;
        }
    }
    return p;
}

// ==========================================
// 4. PROGRESSIONS & SUMMATIONS MODULO M
// ==========================================

// Fast modular exponentiation: (a^e) % mod
ll modpow(ll a, ll e, ll mod) {
    ll r = 1 % mod;
    a %= mod;
    while (e > 0) {
        if (e & 1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}

// Sum of Geometric Progression: S = sum_{i=0}^{n-1} r^i  (mod M)
// Works EVEN WHEN (r - 1) % mod == 0 (no division by (r - 1) needed!)
// Time complexity: O(log n) via divide-and-conquer
ll gp_sum_mod(ll r, ll n, ll mod) {
    if (n <= 0) return 0;
    if (n == 1) return 1 % mod;
    r %= mod;
    if (n % 2 == 0) {
        ll half = gp_sum_mod(r, n / 2, mod);
        ll term = modpow(r, n / 2, mod);
        return (half + (__int128)half * term) % mod;
    } else {
        return (1 + (__int128)r * gp_sum_mod(r, n - 1, mod)) % mod;
    }
}

// Closed-form exact summations (without modulo or with large ints):
// sum_{i=1}^n i = n * (n + 1) / 2
ll sum_linear(ll n) { return n * (n + 1) / 2; }

// sum_{i=1}^n i^2 = n * (n + 1) * (2n + 1) / 6
ll sum_squares(ll n) { return (__int128)n * (n + 1) * (2 * n + 1) / 6; }

// sum_{i=1}^n i^3 = (n * (n + 1) / 2)^2
ll sum_cubes(ll n) { ll s = sum_linear(n); return s * s; }

// ==========================================
// 5. MATRIX EXPONENTIATION (RECURRENCES IN O(K^3 log N))
// ==========================================
template<int SZ>
struct Matrix {
    ll mat[SZ][SZ];

    Matrix() {
        memset(mat, 0, sizeof(mat));
    }

    static Matrix identity() {
        Matrix res;
        for (int i = 0; i < SZ; i++) res.mat[i][i] = 1;
        return res;
    }

    Matrix operator*(const Matrix &o) const {
        Matrix res;
        for (int i = 0; i < SZ; i++)
            for (int k = 0; k < SZ; k++)
                for (int j = 0; j < SZ; j++) {
                    res.mat[i][j] = (res.mat[i][j] + (__int128)mat[i][k] * o.mat[k][j]);
                }
        return res;
    }

    Matrix mult_mod(const Matrix &o, ll mod) const {
        Matrix res;
        for (int i = 0; i < SZ; i++)
            for (int k = 0; k < SZ; k++)
                for (int j = 0; j < SZ; j++) {
                    res.mat[i][j] = (res.mat[i][j] + (__int128)mat[i][k] * o.mat[k][j]) % mod;
                }
        return res;
    }

    static Matrix power(Matrix a, ll p, ll mod) {
        Matrix res = identity();
        while (p > 0) {
            if (p & 1) res = res.mult_mod(a, mod);
            a = a.mult_mod(a, mod);
            p >>= 1;
        }
        return res;
    }
};

// Computes N-th Fibonacci number modulo MOD in O(log N)
// F(0) = 0, F(1) = 1, F(2) = 1, F(3) = 2, ...
ll fibonacci(ll n, ll mod) {
    if (n == 0) return 0;
    Matrix<2> T;
    T.mat[0][0] = 1; T.mat[0][1] = 1;
    T.mat[1][0] = 1; T.mat[1][1] = 0;
    T = Matrix<2>::power(T, n - 1, mod);
    return T.mat[0][0] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}

/*
========================================================================
             COMBINATORICS & NUMBER THEORY FORMULA CHEAT SHEET
========================================================================

1. STARS AND BARS (DISTRIBUTING N ITEMS INTO K BINS):
   - Number of non-negative integer solutions (x1 + ... + xK = N, xi >= 0):
     C(N + K - 1, K - 1)
   - Number of positive integer solutions (x1 + ... + xK = N, xi >= 1):
     C(N - 1, K - 1)

2. CATALAN NUMBERS:
   - C_n = (1 / (n + 1)) * C(2n, n) = C(2n, n) - C(2n, n - 1)
   - Values: C_0=1, C_1=1, C_2=2, C_3=5, C_4=14, C_5=42, C_6=132
   - Applications:
     * Valid parenthesis strings of length 2n
     * Number of distinct Binary Search Trees (BSTs) with n keys
     * Triangulations of a convex polygon with (n + 2) vertices
     * Monotonic grid paths from (0,0) to (n,n) that never cross the diagonal

3. DERANGEMENTS (PERMUTATIONS WHERE NO ELEMENT IS IN ITS ORIGINAL POSITION):
   - Recurrence: D(n) = (n - 1) * (D(n - 1) + D(n - 2))
   - Explicit:   D(n) = n! * sum_{k=0}^n (-1)^k / k!
   - Values: D(0)=1, D(1)=0, D(2)=1, D(3)=2, D(4)=9, D(5)=44, D(6)=265

4. STIRLING NUMBERS OF THE SECOND KIND S(n, k):
   - Number of ways to partition n labeled items into k non-empty unlabeled subsets
   - Recurrence: S(n, k) = k * S(n - 1, k) + S(n - 1, k - 1)
   - Base cases: S(0, 0) = 1, S(n, 0) = 0 for n > 0

5. EULER'S THEOREM & FERMAT'S LITTLE THEOREM:
   - If gcd(a, m) = 1, then a^(phi(m)) = 1 (mod m)
   - If m is prime, phi(m) = m - 1 => a^(m - 1) = 1 (mod m)
   - To reduce large exponent E in a^E (mod m) when gcd(a, m) = 1:
     a^E = a^(E mod phi(m)) (mod m)

6. BURNSIDE'S LEMMA (COUNTING EQUIVALENT COLORINGS UNDER ROTATION/REFLECTION):
   - Number of orbits = (1 / |G|) * sum_{g in G} |Fix(g)|
   - Example (Coloring vertices of square with C colors under 4 rotations):
     * 0 deg: C^4 fixed colorings
     * 90 deg: C^1 fixed colorings
     * 180 deg: C^2 fixed colorings
     * 270 deg: C^1 fixed colorings
     Total distinct colorings = (C^4 + C^1 + C^2 + C^1) / 4

7. USEFUL GCD IDENTITIES:
   - gcd(a, b) = gcd(a, b - a) = gcd(a, b % a)
   - gcd(a^m - 1, a^n - 1) = a^gcd(m, n) - 1
   - gcd(F_m, F_n) = F_gcd(m, n) (where F is Fibonacci)
   - lcm(a, b) = (a * b) / gcd(a, b)
========================================================================
*/
