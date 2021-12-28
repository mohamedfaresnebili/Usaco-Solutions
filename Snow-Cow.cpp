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

        int n, q; vector<int> adj[2 * 100005];
        int tin[2 * 100005], out[2 * 100005], sub[2 * 100005], timer;
        ll st[4 * 2 * 100005], st0[4 * 2 * 100005];
        map<int, int> col[2 * 100005];

        void dfs(int v, int p) {
            tin[v] = timer++;
            for(auto u : adj[v]) {
                if(u == p) continue;
                dfs(u, v);
            }
            out[v] = timer - 1; sub[v] = out[v] - tin[v] + 1;
        }
        void update(int v, int l, int r, int pos, int val) {
            if(l == r) {
                st[v] += val;
                return;
            }
            int md = (l + r)/2;
            if(pos <= md) update(v * 2, l, md, pos, val);
            else update(v * 2 + 1, md + 1, r, pos, val);
            st[v] = st[v * 2] + st[v * 2 + 1];
        }
        void update0(int v, int l, int r, int pos, int val) {
            if(l == r) {
                st0[v] += val;
                return;
            }
            int md = (l + r)/2;
            if(pos <= md) update0(v * 2, l, md, pos, val);
            else update0(v * 2 + 1, md + 1, r, pos, val);
            st0[v] = st0[v * 2] + st0[v * 2 + 1];
        }
        ll query0(int v, int l, int r, int lo, int hi) {
            if(l > hi || r < lo) return 0;
            if(l >= lo && r <= hi) return st0[v];
            return query0(v * 2, l, (l + r)/ 2, lo, hi) + query0(v * 2 + 1, (l + r) / 2 + 1, r, lo, hi);
        }
        ll query(int v, int l, int r, int lo, int hi) {
            if(l > hi || r < lo) return 0;
            if(l >= lo && r <= hi) return st[v];
            return query(v * 2, l, (l + r)/ 2, lo, hi) + query(v * 2 + 1, (l + r) / 2 + 1, r, lo, hi);
        }

        int32_t main()
        {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            cin >> n >> q;
            for(int l = 0; l < n - 1; l++) {
                int u, v; cin >> u >> v; u--; v--;
                adj[u].pb(v); adj[v].pb(u);
            }
            dfs(0, 0);
            while(q--) {
                int t; cin >> t;
                if(t == 1) {
                    int u, v; cin >> u >> v; u--;
                    auto it = col[v].ub(tin[u]);
                    if(it != col[v].begin() && out[prev(it)->ss] >= out[u]) continue;
                    while(it != col[v].end() && out[it->ss] <= out[u]) {
                        update(1, 0, n, tin[it->ss], -1);
                        update(1, 0, n, out[it->ss] + 1, 1);
                        update0(1, 0, n, tin[it->ss], -sub[it->ss]);
                        col[v].erase(it++);
                    }
                    col[v][tin[u]] = u;
                    update(1, 0, n, tin[u], 1); update(1, 0, n, out[u] + 1, -1);
                    update0(1, 0, n, tin[u], sub[u]);
                }
                else if(t == 2) {
                    int u; cin >> u; u--;
                    ll res = query(1, 0, n, 0, tin[u]) * sub[u] + query0(1, 0, n, tin[u] + 1, out[u]);
                    cout << res << "\n";
                }
            }
            return 0;
        }
