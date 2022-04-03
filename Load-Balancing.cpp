#include <bits/stdc++.h>
/// #pragma GCC optimize ("Ofast")
/// #pragma GCC target ("avx2")
/// #pragma GCC optimize("unroll-loops")

        using namespace std;

        using ll = long long;
        using ii = pair<ll, ll>;
        using vi = vector<int>;

        #define ff first
        #define ss second
        #define pb push_back
        #define all(x) (x).begin(), (x).end()
        /// #define int ll

        const int oo = 1e9 + 7;

        int N, st[4000001][2];
        ii arr[1000001];
        void update(int v, int l, int r, int pos, int val, int t) {
            if(l == r) {
                st[v][t] += val;
                return;
            }
            int md = (l + r) / 2;
            if(pos <= md) update(v * 2, l, md, pos, val, t);
            else update(v * 2 + 1, md + 1, r, pos, val, t);
            st[v][t] = st[v * 2][t] + st[v * 2 + 1][t];
        }
        int query(int v, int l, int r, int lx, int rx, int lf, int rf) {
            if(l == r) {
                if(lx < rx) lx += st[v][0];
                else rx += st[v][0];

                if(lf < rf) lf += st[v][1];
                else rf += st[v][1];

                return max({lx, rx, lf, rf});
            }

            int md = (l + r) / 2;
            int aa = max(lx + st[v * 2][0], lf + st[v * 2][1]);
            int bb = max(rx + st[v * 2 + 1][0], rf + st[v * 2 + 1][1]);

            if(aa < bb) return query(v * 2 + 1, md + 1, r, lx + st[v * 2][0], rx, lf + st[v * 2][1], rf);
            else return query(v * 2, l, md, lx, rx + st[v * 2 + 1][0], lf, rf + st[v * 2 + 1][1]);
        }
        bool cmp(ii a, ii b) {
            if(a.ss != b.ss) return a.ss < b.ss;
            return a.ff < b.ff;
        }

	int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("balancing.in", "r", stdin);
            freopen("balancing.out", "w", stdout);
            cin >> N; int res = oo;
            for(int l = 0; l < N; l++)
                cin >> arr[l].ff >> arr[l].ss;
            sort(arr, arr + N);
            int curr = 0, pr = arr[0].ff;
            for(int l = 0; l < N; l++) {
                if(arr[l].ff != pr) {
                    pr = arr[l].ff;
                    curr++;
                }
                arr[l].ff = curr;
            }
            sort(arr, arr + N, cmp);
            for(int l = 0; l < N; l++) {
                update(1, 0, curr, arr[l].ff, 1, 0);
            }
            for(int l = 0; l < N; ) {
                int i = l;
                while(i < N && arr[l].ss == arr[i].ss) {
                    update(1, 0, curr, arr[i].ff, -1, 0);
                    update(1, 0, curr, arr[i].ff, 1, 1);
                    i++;
                }
                res = min(res, query(1, 0, curr, 0, 0, 0, 0));
                l = i;
            }
            cout << res << "\n";
	}
