#include <bits/stdc++.h>

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
        #define mp make_pair

        struct node{ int v, c, f; };
        vector<node> adj[1005];
        int n, m; vector<int> fl; bitset<1005> used;
        int solve(int val) {
            vi dist(n, 1000000007); dist[0] = 0;
            priority_queue<ii, vector<ii>, greater<ii>> pq;
            pq.push({0, 0});
            while(!pq.empty()) {
                int a = pq.top().ss, w = pq.top().ff; pq.pop();
                if(dist[a] != w) continue;
                for(auto u : adj[a]) {
                    int len = dist[a] + u.c;
                    if(u.f < val || dist[u.v] < len) continue;
                    dist[u.v] = len; pq.push({len, u.v});
                }
            }
            return (dist[n - 1] != 1000000007 ? (1000000 * val) / dist[n - 1] : -1);
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("pump.in", "r", stdin);
            freopen("pump.out", "w", stdout);
            cin >> n >> m;
            for(int l = 0; l < m; l++) {
                int u, v, c, f; cin >> u >> v >> c >> f; u--; v--;
                adj[u].pb({v, c, f}), adj[v].pb({u, c, f});
                if(used[f]) continue;
                used[f] = 1; fl.push_back(f);
            }
            sort(all(fl)); int ans = -1;
            for(auto u : fl) {
                ans = max(ans, solve(u));
            }
            cout << ans << "\n";
        }




