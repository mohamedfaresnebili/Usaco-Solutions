#include <bits/stdc++.h>

                    using namespace std;
                    using ll = long long;

                    const int MOD = 1e9 + 7;

                    int N, P[100005];
                    int L[100005], R[100005];

                    int32_t main() {
                        ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
                        int T, B; cin >> T >> B;
                        while(T--) {
                            cin >> N; int res = 0;
                            for(int l = 2; l <= N; l++) cin >> P[l];
                            pair<int, int> C = {MOD, -MOD};
                            int X[N + 1], Y[N + 1];
                            for(int l = 1; l <= N; l++) {
                                cin >> L[l] >> R[l];
                                X[l] = R[l], Y[l] = L[l];
                                C.first = min(C.first, X[l]);
                                C.second = max(C.second, Y[l]);
                                if(l > 1)
                                    X[l] = min(X[l], X[P[l]]),
                                    Y[l] = max(Y[l], Y[P[l]]);
                                res = max(res, Y[l] - X[l]);
                            }
                            res = max(res, (C.second - C.first + 1) / 2);
                            int md = (C.second + C.first) / 2;
                            cout << res << "\n";
                            if(B == 1) {
                                for(int l = 1; l <= N; l++) {
                                    if(l > 1) cout << " ";
                                    cout << max(min(md, R[l]), L[l]);
                                }
                                cout << "\n";
                            }
                        }
                    }


