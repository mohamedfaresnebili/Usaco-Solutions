#include <bits/stdc++.h>
/// #pragma GCC optimize ("Ofast")
/// #pragma GCC target ("avx2")

        using namespace std;

        using ll = long long;
        using ii = pair<ll, ll>;
        using vi = vector<int>;
        using db = double;

        #define ff first
        #define ss second
        #define pb push_back
        #define all(x) x.begin(), x.end()
        #define lb lower_bound
        #define ub upper_bound

        const ll INF = LONG_LONG_MAX / 2;

        const ll nx[4] = {0, 0, 1, -1}, ny[4] = {1, -1, 0, 0};

        ll n, m, t, grid[555][555], res, lf;
        ll par[555 * 555], occ[555 * 555], diff[555 * 555];
        set<ll> arr[555 * 555];

        struct node{
            ll u, v, cost;
            bool operator <(const node& other) {
                if(cost != other.cost) return cost < other.cost;
                if(u != other.cost) return u < other.u;
                return v < other.v;
            }
        };

        void init() {
            for(ll l = 0; l < n; l++)
                for(ll i = 0; i < m; i++)
                    occ[l * m + i] = 1, par[l * m + i] = l * m + i;
        }
        ll findSet(ll v) {
            if(par[v] == v) return v;
            return par[v] = findSet(par[v]);
        }
        bool sameSet(ll u, ll v) {
            return findSet(u) == findSet(v);
        }
        void unionSet(ll u, ll v, ll cost) {
            u = findSet(u), v = findSet(v);
            if(u == v) return;
            if(occ[u] > occ[v]) swap(u, v);
            for(auto e : arr[u]) arr[v].insert(e);
            par[u] = v; occ[v] += occ[u];
            diff[v] = max(diff[v], diff[u]);
            diff[v] = max(diff[v], cost);
            if(occ[v] >= t) {
                res += arr[v].size() * diff[v]; lf -= (arr[v].size()); arr[v].clear();
            }
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("skilevel.in", "r", stdin);
            freopen("skilevel.out", "w", stdout);
            cin >> n >> m >> t; init();
            vector<node> edges;
            for(ll l = 0; l < n; l++)
                for(ll i = 0; i < m; i++)
                    cin >> grid[l][i];
            for(ll l = 0; l < n; l++)
                for(ll i = 0; i < m; i++)
                    for(ll j = 0; j < 4; j++) {
                        ll x = l + nx[j], y = i + ny[j];
                        if(x >= 0 && x < n && y >= 0 && y < m) {
                            ll curr = abs(grid[l][i] - grid[x][y]);
                            edges.pb({l * m + i, x * m + y, curr});
                        }
                    }
            sort(all(edges));
            for(ll l = 0; l < n; l++) {
                for(ll i = 0; i < m; i++) {
                    ll u; cin >> u;
                    if(u) arr[l * m + i].insert(l * m + i), lf++;
                }
            }
            for(ll l = 0; l < (ll)edges.size() && lf; l++) {
                node e = edges[l];
                ll u = e.u, v = e.v, cost = e.cost;
                if(sameSet(u, v)) continue;
                unionSet(u, v, cost);
            }
            cout << res << "\n";
        }
