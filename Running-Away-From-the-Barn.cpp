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

        ll n, m, par[2 * 100005][20]; ll len[2 * 100005][20];
        ll st[4 * 2 * 100005], lazy[4 * 2 * 100005]; vector<ii> adj[2 * 100005];
        ll dep[2 * 100005], tp[2 * 100005], tin[2 * 100005], sz[2 * 100005], timer;

        void prop(ll v, ll l, ll r) {
            if(l == r || lazy[v] == 0) return;
            lazy[v * 2] += lazy[v], lazy[v * 2 + 1] += lazy[v];
            ll md = (l + r) / 2; ll a = md - l + 1, b = r - md;
            st[v * 2] += a * lazy[v], st[v * 2 + 1] += b * lazy[v];
            lazy[v] = 0;
        }
        void update(ll v, ll l, ll r, ll lo, ll hi) {
            prop(v, l, r);
            if(l > hi || r < lo) return;
            if(l >= lo && r <= hi) {
                lazy[v]++; st[v] += (r - l + 1);
                prop(v, l, r); return;
            }
            update(v * 2, l, (l + r) / 2, lo, hi);
            update(v * 2 + 1, (l + r) / 2 + 1, r, lo, hi);
            st[v] = st[v * 2] + st[v * 2 + 1];
        }
        void upd(ll u, ll v) {
            while(tp[u] != tp[v]) {
                if(dep[tp[u]] < dep[tp[v]]) swap(u, v);
                update(1, 0, n - 1, tin[tp[u]], tin[u]);
                u = par[tp[u]][0];
            }
            if(dep[u] > dep[v]) swap(u, v);
            update(1, 0, n - 1, tin[u], tin[v]);
        }
        ll query(ll v, ll l, ll r, ll pos) {
            prop(v, l, r);
            if(l == r) return st[v];
            ll md = (l + r) / 2;
            if(pos <= md) return query(v * 2, l, md, pos);
            else query(v * 2 + 1, md + 1, r, pos);
        }
        ll dfs(ll v) {
            sz[v] = 1;
            for(auto u : adj[v]) {
                par[u.ff][0] = v; len[u.ff][0] = u.ss;
                dep[u.ff] = dep[v] + 1; sz[v] += dfs(u.ff);
            }
            return sz[v];
        }
        void hld(ll v, ll p, ll top) {
            tp[v] = top; tin[v] = timer++;
            ll curr = 0, node = -1;
            for(auto u : adj[v]) {
                if(sz[u.ff] > curr) {
                    curr = sz[u.ff]; node = u.ff;
                }
            }
            if(node == -1) return;
            hld(node, p, top);
            for(auto u : adj[v]) {
                if(u.ff == node) continue;
                hld(u.ff, v, u.ff);
            }
        }

        int32_t main()
        {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("runaway.in", "r", stdin);
            freopen("runaway.out", "w", stdout);
            cin >> n >> m;
            for(ll l = 1; l < n; l++) {
                ll u, k; cin >> u >> k; u--;
                adj[u].pb({l, k});
            }
            dfs(0); hld(0, 0, 0);
            for(ll i = 1; i < 20; i++)
                for(ll l = 0; l < n; l++) {
                    par[l][i] = par[par[l][i - 1]][i - 1];
                    len[l][i] = len[l][i - 1] + len[par[l][i - 1]][i - 1];
                }
            for(ll l = 0; l < n; l++) {
                ll u = l, curr = m;
                for(ll i = 20 - 1; i >= 0; i--) {
                    if(curr - len[u][i] < 0) continue;
                    curr -= len[u][i], u = par[u][i];
                }
                upd(l, u);
            }
            for(ll l = 0; l < n; l++)
                cout << query(1, 0, n - 1, tin[l]) << "\n";
            return 0;
        }
