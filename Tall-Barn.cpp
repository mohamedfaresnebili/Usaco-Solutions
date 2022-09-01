#include <bits/stdc++.h>

            using namespace std;
            using ll = long long;

            const ll INF = INT64_MAX / 2;
            const double EPS = 1e-9;

            ll N, K, A[100005];
            ll solve(double v) {
                ll res = 0;
                for(int l = 0; l < N; l++) {
                    res += ll((sqrt(1LL + ((4LL * A[l]) / v)) - 1LL) / 2LL);
                }
                return res;
            }

            int32_t main() {
                ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
                freopen("tallbarn.in", "r", stdin);
                freopen("tallbarn.out", "w", stdout);
                cin >> N >> K; K -= N;
                for(int l = 0; l < N; l++) cin >> A[l];
                double lo = 0, hi = 1e18;
                while(fabs(hi - lo) > EPS) {
                    double md = (lo + hi) / 2;
                    if(solve(md) < K) hi = md;
                    else lo = md;
                }
                double ans = 0; ll T = 0;
                for(int i = 0; i < N; i++) {
                    ll C = ll((sqrt(1LL + (4LL * A[i]) / lo) - 1LL) / 2LL);
                    T += C; ans += 1.0 * A[i] / (C + 1);
                }
                cout << (ll)round(ans - (K - T) * lo) << "\n";
                return 0;
            }

