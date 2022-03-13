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

        int b, e, p, n, m;
        vector<int> adj[40005];
        int dis[40005][5];

        int bfs(int s, int k) {
            for(int l = 0; l < n; l++) dis[l][k] = -1;
            dis[s][k] = 0; queue<int> q; q.push(s);
            while(!q.empty()) {
                int a = q.front(); q.pop();
                for(auto u : adj[a]) {
                    if(dis[u][k] != -1) continue;
                    dis[u][k] = dis[a][k] + 1;
                    q.push(u);
                }
            }
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("piggyback.in", "r", stdin);
            freopen("piggyback.out", "w", stdout);
            cin >> b >> e >> p >> n >> m;
            for(int l = 0; l < m; l++) {
                int u, v; cin >> u >> v; u--; v--;
                adj[u].pb(v); adj[v].pb(u);
            }
            bfs(0, 0), bfs(1, 1), bfs(n - 1, 2);
            ll res = dis[n - 1][0] * b + dis[n - 1][1] * e;
            for(int l = 0; l < n; l++) {
                ll curr = dis[l][0] * b + dis[l][1] * e + dis[l][2] * p;
                res = min(res, curr);
            }
            cout << res << "\n";
        }
