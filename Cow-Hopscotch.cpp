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
        /// #define mp make_pair

        using pi = pair<ii, ii>;
        const int nx[4] = {0, 0, -1, 1}, ny[4] = {1, -1, 0, 0};
        const int MOD = 1000000007;

        struct seg{
            int n; vector<int> st;
            void init(int _n) { n = _n; st.assign(4 * n, 0); }
            void update(int v, int l, int r, int pos, int val) {
                if(l == r) {
                    st[v] += val; st[v] %= MOD;
                    return;
                }
                int md = (l + r) / 2;
                if(pos <= md) update(v * 2, l, md, pos, val);
                else update(v * 2 + 1, md + 1, r, pos, val);
                st[v] = st[v * 2] % MOD + st[v * 2 + 1] % MOD;
                st[v] %= MOD;
            }
            int query(int v, int l, int r, int lo, int hi) {
                if(l > hi || r < lo) return 0;
                if(l >= lo && r <= hi) return st[v] % MOD;
                return (query(v * 2, l, (l + r) / 2, lo, hi) % MOD + query(v * 2 + 1, (l + r) / 2 + 1, r, lo, hi) % MOD) % MOD;
            }
            void update(int pos, int val) {
                update(1, 0, n + 2, pos, val);
            }
            int query(int lo, int hi) {
                return query(1, 0, n + 2, lo, hi);
            }
        };

        int n, m, k, arr[755][755], q[755];

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("hopscotch.in", "r", stdin);
            freopen("hopscotch.out", "w", stdout);
            cin >> n >> m >> k;
            seg col[k + 3], t;
            map<int, int> mp[k + 3];
            vector<int> v[k + 3];
            t.init(m + 1);

            for(int l = 1; l <= n; l++)
                for(int i = 1; i <= m; i++) {
                    cin >> arr[l][i];
                    v[arr[l][i]].pb(i);
                }
            for(int l = 1; l <= k; l++) {
                sort(all(v[l]));
                for(auto u : v[l])
                    if(!mp[l][u]) mp[l][u] = mp[l].size();
                col[l].init(mp[l].size() + 2);
            }
            t.update(1, 1);
            col[arr[1][1]].update(mp[arr[1][1]][1], 1);

            for(int l = 2; l <= n; l++) {
                for(int i = 2; i <= m; i++) {
                    int u = arr[l][i];
                    q[i] = t.query(1, i - 1) - col[u].query(1, mp[u][i] - 1) + MOD;
                    q[i] %= MOD;
                }
                for(int i = 2; i <= m; i++) {
                    int u = arr[l][i];
                    t.update(i, q[i]);
                    col[u].update(mp[u][i], q[i]);
                }
            }
            cout << q[m] % MOD << "\n";
        }









