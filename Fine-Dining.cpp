#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")

        using namespace std;

        using ll = long long;
        using ii = pair<int, int>;
        using vi = vector<int>;
        using db = double;

        #define ff first
        #define ss second
        #define pb push_back
        #define all(x) x.begin(), x.end()
        #define lb lower_bound
        #define ub upper_bound

        int n, m, k;
        vector<array<int, 2>> adj[50005];
        int dist[50005][2];

        void dijkstra(int s, int curr) {
            priority_queue<ii, vector<ii>, greater<ii>> pq;
            pq.push({0, s}); dist[s][curr] = 0;
            vector<bool> vis(n + 1, 0);
            while(!pq.empty()) {
                int a = pq.top().ss, w = pq.top().ff; pq.pop();
                if(vis[a] || dist[a][curr] < w) continue;
                vis[a] = 1;
                for(auto u : adj[a]) {
                    int len = dist[a][curr] + u[1];
                    if(dist[u[0]][curr] <= len || vis[u[0]]) continue;
                    dist[u[0]][curr] = len; pq.push({len, u[0]});
                }
            }
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("dining.in", "r", stdin);
            freopen("dining.out", "w", stdout);
            cin >> n >> m >> k;
            for(int l = 0; l <= n; l++) dist[l][0] = dist[l][1] = 1000000007;
            for(int l = 0; l < m; l++) {
                int u, v, w; cin >> u >> v >> w; u--; v--;
                adj[u].pb({v, w}); adj[v].pb({u, w});
            }
            dijkstra(n - 1, 0);
            for(int l = 0; l < k; l++) {
                int u, v; cin >> u >> v; u--;
                adj[n].pb({u, dist[u][0] - v});
            }
            dijkstra(n, 1);
            for(int l = 0; l < n - 1; l++) {
                cout << (dist[l][0] >= dist[l][1]) << "\n";
            }
        }
