#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

// Strict-ordered set (unique keys)
template<class T>
using oset = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Strict-ordered map
template<class K, class V>
using omap = tree<K, V, std::less<K>, rb_tree_tag, tree_order_statistics_node_update>;

// Multiset via tie-breaking index (recommended)
struct OMulti {
    // store (value, unique_id)
    oset<pair<long long,int>> t;
    int uid = 0;

    void insert(long long x){ t.insert({x, uid++}); }

    // erase one occurrence of x (if any)
    bool erase_one(long long x){
        auto it = t.lower_bound({x, -1});
        if(it != t.end() && it->first == x){ t.erase(it); return true; }
        return false;
    }

    // count elements strictly < x
    int count_less(long long x) const { return (int)t.order_of_key({x, -1}); }

    // count elements <= x
    int count_leq (long long x) const { return (int)t.order_of_key({x+1, -1}); }
};
