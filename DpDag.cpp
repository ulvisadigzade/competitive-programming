#include <bits/stdc++.h>

using namespace std;

// Topological sort (DAG)
vector<int> topo_sort(int n, vector<vector<int>> &g) {
    vector<int> indeg(n,0);
    for (int v=0; v<n; v++)
        for (int u: g[v]) indeg[u]++;

    queue<int> q;
    for (int i=0;i<n;i++) if(!indeg[i]) q.push(i);

    vector<int> order;
    while(!q.empty()){
        int v=q.front(); q.pop();
        order.push_back(v);
        for(int u:g[v]) if(--indeg[u]==0) q.push(u);
    }
    return order; // if size<n -> graph had cycle
}

long long dag_longest_path(int n, vector<vector<int>> &g, int s) {
    auto order = topo_sort(n, g);
    const long long NEG_INF = (long long)-4e18;
    vector<long long> dp(n, NEG_INF);
    dp[s] = 0;
    for (int v : order) {
        if (dp[v] == NEG_INF) continue;
        for (int u : g[v]) {
            dp[u] = max(dp[u], dp[v] + 1); // or +weight
        }
    }
    long long best = NEG_INF;
    for (int i = 0; i < n; i++) best = max(best, dp[i]);
    return best;
}

int main(){

}

/*
Good — that honesty will save you time.
Let me give you the **leanest possible explanation** so you go from “don’t know topo sort” → “can use it in contest tomorrow”.

No fluff. No theory. Just what it *is*, *why it exists*, and *how you use it*.

---

# **1. What is topo sort? (the only version you need in ICPC)**

For any **directed acyclic graph (DAG)**, topo sort gives you an ordering of nodes such that:

> **Every node appears *after* all its prerequisites.**

That’s it.

Example:

```
A → B → C
A → D
B → D
```

Topo orders could be:

```
A B C D
A B D C
A D B C   // NO (D depends on B), invalid
```

---

# **2. Why does topo sort exist? (intuition)**

Imagine tasks with prerequisites:

* You can’t do task B until task A is done.
* You can’t do D until B and A are done.

Topo sort produces a valid order to do the tasks.

It’s literally just **"sort by dependency"**.

---

# **3. When do you use it? (the part you were actually missing)**

Whenever a problem consists of:

### ✔ “Tasks with prerequisites”

### ✔ “States that depend on earlier states”

### ✔ “Directed acyclic graph”

### ✔ “Find valid order of execution”

### ✔ “DP where transitions go forward”

### ✔ “Longest/shortest path in DAG”

If any of these appear → **use topo**.

It’s not optional. It’s the *only* correct tool.

---

# **4. The algorithm you need (Kahn’s algorithm)**

This is the version you will use 99% of the time.

### Code skeleton you can drop in immediately:

```cpp
vector<int> topo_sort(int n, vector<vector<int>> &g) {
    vector<int> indeg(n, 0);
    for (int v = 0; v < n; v++)
        for (int u : g[v])
            indeg[u]++;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        order.push_back(v);
        for (int u : g[v]) {
            if (--indeg[u] == 0) q.push(u);
        }
    }

    // if order.size() < n => graph had a cycle
    return order;
}
```

You must understand only one thing for usage:

### Nodes with indegree = 0 are ready to process.

Because they have no prerequisites left.

---

# **5. The simplest useful example**

Graph:

```
0 → 1
0 → 2
1 → 3
2 → 3
```

Topo gives:

```
0 1 2 3
```

or

```
0 2 1 3
```

Now suppose you want **longest path** in this DAG.

### DP using topo:

```cpp
vector<int> order = topo_sort(n, g);
vector<int> dp(n, -1e9);
dp[start] = 0;

for (int v : order) {
    for (int u : g[v]) {
        dp[u] = max(dp[u], dp[v] + weight(v,u));
    }
}
```

This works ONLY because topo ensures that when processing `v`, all nodes that lead to `v` have already been processed.

---

# **6. The “aha” that makes topo click**

Topo sorting is nothing more than:

> **“Process nodes in an order where dependencies are respected.”**

Dependencies → DAG → Topo.

It’s just ordering the work.

Same way you don’t study an advanced math chapter before learning basic definitions — you respect dependency ordering. That’s literally all it is.

---

# **7. What topo sort is *not***

* It’s not for undirected graphs
* It’s not for shortest path in general graphs (use Dijkstra)
* It’s not for BFS-like level order
* It's not for trees (though trees trivially have topo order if rooted)

Topo is only for **directed acyclic structure**.

---

# **8. Why topo is insanely useful in ICPC**

Because half of DP-on-graph problems reduce to:

1. Is graph a DAG?
2. If yes → topo sort
3. Do DP in topo order

It collapses complexity from impossible to trivial.

---

# **If you want: I can give you 5 real ICPC problems where topo is the key and walk you through the thought process how you'd detect it in 10 seconds.**

*/