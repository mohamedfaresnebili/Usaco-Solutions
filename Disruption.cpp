#include <bits/stdc++.h>

        using namespace std;

        using ll = long long;
        using ii = pair<int, int>;
        using vi = vector<int>;

        #define ff first
        #define ss second
        #define pb push_back
        #define all(x) x.begin(), x.end()

        int n, m; vector<int> adj[2*100005]; map<ii, ll> ans;
        int par[2*100005][20], dep[2*100005], sz[2*100005], tp[2*100005];
        int tin[2*100005], heavy[2*100005], child[2*100005], timer;
        int st[2*100005], lazy[2*100005];

        void prop(int v, int l, int r) {
            if(l == r || lazy[v] == 1000000007) return;
            lazy[v * 2] = min(lazy[v * 2], lazy[v]);
            lazy[v * 2 + 1] = min(lazy[v * 2 + 1], lazy[v]);
            st[v * 2] = min(st[v * 2], lazy[v]);
            st[v * 2 + 1] = min(st[v * 2 + 1], lazy[v]);
            lazy[v] = 1000000007;
        }
        void update(int v, int l, int r, int lo, int hi, int val) {
            prop(v, l, r);
            if(l > hi || r < lo) return;
            if(l >= lo && r <= hi) {
                st[v] = min(st[v], val);
                lazy[v] = min(lazy[v], val);
                prop(v, l, r);
                return;
            }
            update(v * 2, l, (l + r)/2, lo, hi, val);
            update(v * 2 + 1, (l + r)/2 + 1, r, lo, hi, val);
            st[v] = min(st[v * 2], st[v * 2 + 1]);
        }
        void upd(int a, int b, int val) {
            while(tp[a] != tp[b]) {
                if(dep[tp[a]] < dep[tp[b]]) swap(a, b);
                update(1, 0, n - 1, tin[tp[a]], tin[a], val);
                a = par[tp[a]][0];
            }
            if(dep[a] > dep[b]) swap(a, b);
            update(1, 0, n - 1, tin[a], tin[b], val);
        }
        int query(int v, int l, int r, int pos) {
            prop(v, l, r);
            if(l == r) return st[v];
            int md = (l + r) / 2;
            if(pos <= md) return query(v * 2, l, md, pos);
            else return query(v * 2 + 1, md + 1, r, pos);
        }
        int dfs(int v, int p) {
            dep[v] = dep[p] + 1; par[v][0] = p; sz[v] = 1;
            for(auto u : adj[v]) {
                if(u == p) continue;
                sz[v] += dfs(u, v);
            }
            return sz[v];
        }
        void HLD(int v, int p, int top) {
            tp[v] = top; tin[v] = timer++;
            int curr = 0, node = -1;
            for(auto u : adj[v]) {
                if(u == p) continue;
                if(sz[u] > curr) {
                    curr = sz[u], node = u;
                }
            }
            heavy[v] = node;
            if(node == -1) return;
            HLD(heavy[v], v, top);
            for(auto u : adj[v]) {
                if(u == p || u == heavy[v]) continue;
                HLD(u, v, u);
            }
        }
        int jump(int u, int v) {
            if(dep[u] < dep[v]) swap(u, v);
            int k = dep[u] - dep[v];
            for(int l = 0; l < 20; l++)
                if(k & (1 << l))
                    u = par[u][l];
            if(u == v) return u;
            for(int l = 20 - 1; l >= 0; l--)
                if(par[u][l] != par[v][l])
                    u = par[u][l], v = par[v][l];
            return par[u][0];
        }
        int nd(int u, int k) {
            for(int l = 0; l < 20; l++)
                if(k & (1 << l))
                    u = par[u][l];
            return u;
        }

        int32_t main()
        {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("disrupt.in", "r", stdin);
            freopen("disrupt.out", "w", stdout);
            cin >> n >> m; vector<ii> edges;
            for(int l = 0; l < 4 * n; l++) st[l] = lazy[l] = 1000000007;
            for(int l = 0; l < n - 1; l++) {
                int u, v; cin >> u >> v; u--; v--;
                adj[u].pb(v); adj[v].pb(u);
                edges.pb({u, v});
            }
            dep[0] = -1; dfs(0, 0); HLD(0, 0, 0);
            for(int i = 1; i < 20; i++)
                for(int l = 0; l < n; l++)
                    par[l][i] = par[par[l][i-1]][i-1];
            for(int l = 0; l < m; l++) {
                int u, v; ll len; cin >> u >> v >> len; u--; v--;
                if(dep[u] < dep[v]) swap(u, v);
                int lca = jump(u, v); upd(nd(u, dep[u] - dep[lca] - 1), u, len);
                if(v != lca) upd(nd(v, dep[v] - dep[lca] - 1), v, len);
            }
            for(int l = 0; l < n - 1; l++) {
                int u = edges[l].ff, v = edges[l].ss;
                if(dep[u] < dep[v]) swap(u, v);
                int ans = query(1, 0, n - 1, tin[u]);
                if(ans == 1000000007) ans = -1;
                cout << ans << "\n";
            }
            return 0;
        }
