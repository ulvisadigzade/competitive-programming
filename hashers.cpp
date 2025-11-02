#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ull = unsigned long long;

// -------- 64-bit SplitMix hash (fast, high quality) --------
struct SplitMix64 {
    static inline uint64_t splitmix64(uint64_t x) noexcept {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        x = x ^ (x >> 31);
        return x;
    }

    size_t operator()(uint64_t x) const noexcept {
        static const uint64_t FIXED_RANDOM =
            (uint64_t)chrono::steady_clock::now().time_since_epoch().count();
        return (size_t)splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(ll x) const noexcept {
        return (*this)((uint64_t)x);
    }
};

// -------- Pair hash using SplitMix64 --------
// Works for pair<T,U> where T,U are 64-bit convertible (e.g., ll/ull/int)
struct PairHash {
    size_t operator()(const pair<ll,ll>& p) const noexcept {
        static const SplitMix64 H;
        // Mix the two 64-bit halves; any reversible combine is fine before mixing.
        uint64_t a = (uint64_t)p.first;
        uint64_t b = (uint64_t)p.second;
        // A simple, fast reversible combine:
        uint64_t combined = (a << 32) ^ (b + 0x9e3779b97f4a7c15ULL + (a >> 32));
        return H(combined);
    }
};

// -------- Generic pair hash (template) --------
// If you want it generic for pair<T,U>:
struct PairHashGeneric {
    template<class T, class U>
    size_t operator()(const pair<T,U>& p) const noexcept {
        static const SplitMix64 H;
        uint64_t a = (uint64_t)p.first;
        uint64_t b = (uint64_t)p.second;
        uint64_t combined = (a << 32) ^ (b + 0x9e3779b97f4a7c15ULL + (a >> 32));
        return H(combined);
    }
};
