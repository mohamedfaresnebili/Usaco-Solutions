#include <bits/stdc++.h>
/// #pragma GCC optimize ("Ofast")
/// #pragma GCC target ("avx2")

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

        const int INF = INT_MAX;

        int n, m, k;
        vector<ii> adj[10005];
        int dist[10005], p[10005], arr[10005];
        ll occ[10005];

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("shortcut.in", "r", stdin);
            freopen("shortcut.out", "w", stdout);
            cin >> n >> m >> k;
            for(int l = 0; l < n; l++) {
                cin >> arr[l];
                dist[l] = INF, p[l] = INF;
            }
            for(int l = 0; l < m; l++) {
                int u, v, w; cin >> u >> v >> w; u--; v--;
                adj[u].pb({v, w}); adj[v].pb({u, w});
            }
            priority_queue<ii, vector<ii>, greater<ii>> pq;
            pq.push({0, 0}); dist[0] = 0;
            while(!pq.empty()) {
                int w = pq.top().ff, a = pq.top().ss; pq.pop();
                if(dist[a] != w) continue;
                for(auto u : adj[a]) {
                    int len = u.ss + w;
                    if(dist[u.ff] > len) {
                        dist[u.ff] = len;
                        pq.push({len, u.ff});
                        p[u.ff] = a;
                    }
                    else if(dist[u.ff] == len && a < p[u.ff]) {
                        p[u.ff] = a; pq.push({len, u.ff});
                    }
                }
            }
            for(int l = 0; l < n; l++) {
                int i = l;
                while(i != INF) {
                    occ[i] += arr[l];
                    i = p[i];
                }
            }
            ll res = 0;
            for(int l = 0; l < n; l++) {
                res = max(res, (ll)(occ[l] * (dist[l] - k)));
            }
            cout << res << "\n";
        }
