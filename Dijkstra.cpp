#include <bits/stdc++.h>
using namespace std;

using ll  = long long;          
using pii = pair<int, int>;     
using pll = pair<ll, int>;      // priority_queue (dist, node)

#define pb      push_back
#define fi      first
#define se      second

const ll INF = 1e18;             
vector<vector<pii>> g;           
vector<ll> dist;

// --- Dijkstra Algorithm ---
void dijkstra(int s){
    int n = g.size() - 1;   // number of nodes (assuming 1-based indexing)
    dist.assign(n+1, INF);
    
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dist[s]=0;
    pq.push({0, s});

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();

        if(d > dist[u]) continue;

        for(auto [v, w]: g[u]){
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

void solve(){
    int n, m; // n = number of nodes, m = number of edges
    cin >> n >> m;

    g.assign(n + 1, {}); 
    /*
        Declaring graph in there.
        Example:
        for (int i = 0; i < m; i++) {
            int x, y, w;
            cin >> x >> y >> w;
            g[x].pb({y, w});
            g[y].pb({x, w}); // Remove this line if the graph is directed
        }
    */
    dijkstra(1);    // Start from node 1
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
 }