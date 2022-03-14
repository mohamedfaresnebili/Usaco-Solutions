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

        int n, grid[555][555], par[555 * 555], calc[555 * 555];
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
            par[u] = v; calc[v] += calc[u];
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("tractor.in", "r", stdin);
            freopen("tractor.out", "w", stdout);
            cin >> n;
            for(int l = 0; l < n; l++)
                for(int i = 0; i < n; i++) {
                    cin >> grid[l][i];
                    par[l * n + i] = l * n + i;
                    calc[l * n + i] = 1;
                }
            vector<pair<int, ii>> edges;
            for(int l = 0; l < n; l++)
                for(int i = 0; i < n; i++)
                    for(int j = 0; j < 4; j++) {
                        int x = l + nx[j], y = i + ny[j];
                        if(x >= 0 && x < n && y >= 0 && y < n && grid[l][i] >= grid[x][y]) {
                            edges.pb({grid[l][i] - grid[x][y], {l * n + i, x * n + y}});
                        }
                    }
            sort(all(edges));
            for(auto e : edges) {
                int u = e.ss.ff, v = e.ss.ss;
                unionSet(u, v);
                u = findSet(u);
                if(calc[u] >= (n * n + 1) / 2) {
                    cout << e.ff << "\n";
                    return 0;
                }
            }
        }

