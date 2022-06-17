#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

        using namespace std;
        using namespace __gnu_pbds;

        using ll = long long;
        using ii = pair<int, int>;

        #define pb push_back
        #define pp pop_back
        #define ff first
        #define ss second
        #define int ll

        typedef tree<int, null_type, less<int>, rb_tree_tag,
            tree_order_statistics_node_update> indexed_set;

        int N, A[100001], B[100001], S[100001], st[400005];
        void update(int v, int l, int r, int p, int val) {
            if(l == r) {
                st[v] = val;
                return;
            }
            int md = (l + r) / 2;
            if(p <= md) update(v * 2, l, md, p, val);
            else update(v * 2 + 1, md + 1, r, p, val);
            st[v] = st[v * 2] + st[v * 2 + 1];
        }
        int query(int v, int l, int r, int lo, int hi) {
            if(l > hi || r < lo) return 0;
            if(l >= lo && r <= hi) return st[v];
            return query(v * 2, l, (l + r) / 2, lo, hi)
                +  query(v * 2 + 1, (l + r) / 2 + 1, r, lo, hi);
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("mincross.in", "r", stdin);
            freopen("mincross.out", "w", stdout);
            cin >> N;
            for(int l = 1; l <= N; l++) {
                int V; cin >> V; A[V] = l;
            }
            for(int l = 1; l <= N; l++) {
                int V; cin >> V; B[V] = l;
            }
            for(int l = 1; l <= N; l++)
                S[A[l]] = B[l];
            int res = 1e18, inv = 0;
            for(int l = 1; l <= N; l++) {
                inv += query(1, 1, N, S[l], N);
                update(1, 1, N, S[l], 1);
            }
            for(int l = N; l >= 1; l--) {
                inv += 2 * (S[l] - 1) - N + 1;
                res = min(res, inv);
            }
            for(int l = N; l >= 1; l--) {
                inv += 2 * (S[l] - 1) - N + 1;
                res = min(res, inv);
            }
            for(int l = 1; l <= N; l++)
                S[B[l]] = A[l];
            fill(st, st + 400005, 0);
            inv = 0;
            for(int l = 1; l <= N; l++) {
                inv += query(1, 1, N, S[l], N);
                update(1, 1, N, S[l], 1);
            }
            for(int l = N; l >= 1; l--) {
                inv += 2 * (S[l] - 1) - N + 1;
                res = min(res, inv);
            }
            cout << res << "\n";
            return 0;
        }




