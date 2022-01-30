#include <bits/stdc++.h>

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

        ll dist(ll x, ll y, ll x0, ll y0) {
            return abs(x - x0) + abs(y - y0);
        }
        int n, k; vector<array<int, 4>> arr;
        vector<int> comp; int st[4 * 200005], ans[4 * 200005];
        void update(int v, int l, int r, int pos, int val) {
            if(l == r) {
                st[v] = min(st[v], val); return;
            }
            int md = (l + r) / 2;
            if(pos <= md) update(v * 2, l, md, pos, val);
            else update(v * 2 + 1, md + 1, r, pos, val);
            st[v] = min(st[v * 2], st[v * 2 + 1]);
        }
        ll query(int v, int l, int r, int lo, int hi) {
            if(l > hi || r < lo) return 1000000007;
            if(l >= lo && r <= hi) return st[v];
            return min(query(v * 2, l, (l + r) / 2, lo, hi), query(v * 2 + 1, (l + r) / 2 + 1, r, lo, hi));
        }
        int ind(int val) {
            return lb(all(comp), val) - comp.begin();
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("boards.in", "r", stdin);
            freopen("boards.out", "w", stdout);
            cin >> n >> k;
            for(int l = 0; l < k; l++) {
                int x, y, x0, y0; cin >> x >> y >> x0 >> y0;
                arr.pb({x, y, l, -1});
                arr.pb({x0, y0, l, 1});
                comp.pb(y); comp.pb(y0);
            }
            sort(all(arr)); sort(all(comp));
            for(auto u : arr) {
                if(u[3] == -1) ans[u[2]] = u[0] + u[1] + query(1, 0, 2 * k - 1, 0, ind(u[1]));
                else if(u[3] == 1) update(1, 0, 2 * k - 1, ind(u[1]), ans[u[2]] - u[0] - u[1]);
            }
            cout << query(1, 0, 2 * k - 1, 0, 2 * k - 1) + 2 * n << "\n";
        }


