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

        const int nx[4] = {-1, 0, 0, 1}, ny[4] = {0, 1, -1, 0};

        int n, q, par[100005], calc[100005], res[100005];
        vector<pair<int, ii>> edges, query;
        void init() {
            for(int l = 1; l <= n; l++) par[l] = l, calc[l] = 1;
        }
        int findSet(int v) {
            if(par[v] == v) return v;
            return par[v] = findSet(par[v]);
        }
        bool sameSet(int u, int v) {
            return findSet(u) == findSet(v);
        }
        void unionSet(int u, int v) {
            u = findSet(u), v = findSet(v);
            if(u == v) return;
            calc[v] += calc[u]; par[u] = v;
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("mootube.in", "r", stdin);
            freopen("mootube.out", "w", stdout);
            cin >> n >> q; init();
            for(int l = 0; l < n - 1; l++) {
                int u, v, k; cin >> u >> v >> k;
                edges.pb({k, {u, v}});
            }
            sort(all(edges));
            for(int l = 0; l < q; l++) {
                int u, v; cin >> u >> v;
                query.pb({u, {l, v}});
            }
            sort(all(query)); reverse(all(query));
            for(int l = 0; l < q; l++) {
                int k = query[l].ff, ind = query[l].ss.ff, nd = query[l].ss.ss;
                while(!edges.empty()) {
                    int k0 = edges.back().ff;
                    int u = edges.back().ss.ff, v = edges.back().ss.ss;
                    if(k0 < k) break;
                    edges.pop_back(); unionSet(u, v);
                }
                res[ind] = calc[findSet(nd)] - 1;
            }
            for(int l = 0; l < q; l++) cout << res[l] << "\n";
        }




