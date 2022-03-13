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

        int n, s, dis[100005][2];
        vector<int> adj[100005], lf;
        void dfs(int v, int p) {
            int children = 0;
            for(auto u : adj[v]) {
                if(u == p) continue;
                children++; dfs(u, v);
            }
            if(children == 0) {
                lf.pb(v);
                dis[v][1] = 0;
            }
        }
        int solve(int v, int p) {
            if(dis[v][0] >= dis[v][1]) return 1;
            int best = 0;
            for(auto u : adj[v]) {
                if(u == p) continue;
                if(dis[u][0] >= dis[u][1]) best++;
                else best += solve(u, v);
            }
            return best;
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("atlarge.in", "r", stdin);
            freopen("atlarge.out", "w", stdout);
            cin >> n >> s; s--;
            for(int l = 0; l < n; l++) dis[l][0] = dis[l][1] = 1000000007;
            for(int l = 0; l < n - 1; l++) {
                int u, v; cin >> u >> v; u--; v--;
                adj[u].pb(v); adj[v].pb(u);
            }
            dfs(s, s); dis[s][0] = 0; queue<int> q; q.push(s);
            while(!q.empty()) {
                int a = q.front(); q.pop();
                for(auto u : adj[a]) {
                    if(dis[u][0] <= dis[a][0] + 1) continue;
                    dis[u][0] = dis[a][0] + 1;
                    q.push(u);
                }
            }
            for(auto u : lf) q.push(u);
            while(!q.empty()) {
                int a = q.front(); q.pop();
                for(auto u : adj[a]) {
                    if(dis[u][1] <= dis[a][1] + 1) continue;
                    dis[u][1] = dis[a][1] + 1;
                    q.push(u);
                }
            }
            cout << solve(s, s) << "\n";
        }


