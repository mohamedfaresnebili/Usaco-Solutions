#include <bits/stdc++.h>

        using namespace std;

        using ll = long long;
        using ii = pair<ll, ll>;
        using vi = vector<int>;

        #define ff first
        #define ss second
        #define pb push_back
        #define all(x) x.begin(), x.end()
        #define lb lower_bound
        #define ub upper_bound

        int n, m; vector<int> adj[2 * 100005], rev[2 * 100005];
        int tin[2 * 100005], low[2 * 100005], ind[2 * 100005]; vector<int> S;
        bool vis[2 * 100005]; int timer, curr; vector<int> adj0[2 * 100005];
        int arr[2 * 100005];

        void dfs(int v) {
            tin[v] = low[v] = timer++; vis[v] = 1; S.pb(v);
            for(auto u : adj[v]) {
                if(tin[u] == -1) dfs(u);
                if(vis[u]) low[v] = min(low[v], low[u]);
            }
            if(tin[v] == low[v]) {
                while(1) {
                    int u = S.back(); S.pop_back(); vis[u] = 0;
                    arr[curr]++; ind[u] = curr;
                    if(u == v) break;
                }
                curr++;
            }
        }
        ll solve(int v, int state) {
            if(v == ind[1]) return 0;
            ll best = -1000000007; vis[v] = 1;
            for(auto u : adj0[v]) {
                if(vis[u]) best = max(best, solve(u, state));
                else {
                    best = max(best, arr[u] + solve(u, state));
                    vis[u] = 0;
                }
            }
            if(state) {
                for(auto u : rev[v]) {
                    if(vis[u]) best = max(best, solve(u, 0));
                    else {
                        best = max(best, arr[u] + solve(u, 0));
                        vis[u] = 0;
                    }
                }
            }
            return best;
        }

        int32_t main()
        {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("grass.in", "r", stdin);
            freopen("grass.out", "w", stdout);
            cin >> n >> m; vector<ii> edges;
            for(int l = 0; l < m; l++) {
                int u, v; cin >> u >> v;
                adj[u].pb(v); edges.pb({u, v});
            }
            memset(tin, -1, sizeof tin);
            for(int l = 1; l <= n; l++) {
                if(tin[l] != -1) continue;
                dfs(l);
            }
            set<ii> se;
            for(int l = 0; l < m; l++) {
                int u = edges[l].ff, v = edges[l].ss;
                u = ind[u], v = ind[v];
                if(se.count({u, v}) || u == v) continue;
                adj0[u].pb(v); rev[v].pb(u);
                se.insert({u, v});
            }
            ll best = arr[ind[1]]; memset(vis, 0, sizeof vis);
            for(auto u : adj0[ind[1]]) {
                best = max(best, arr[u] + solve(u, 1));
                vis[u] = 0;
            }
            for(auto u : rev[ind[1]]) {
                best = max(best, arr[u] + solve(u, 0));
                vis[u] = 0;
            }
            cout << best << "\n";
            return 0;
        }
