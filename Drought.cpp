#include <bits/stdc++.h>
/// #pragma GCC optimize ("Ofast")
/// #pragma GCC target ("avx2")
/// #pragma GCC optimize("unroll-loops")

                using namespace std;

                using ll = long long;
                using ld = long double;
                using ii = pair<ll, ll>;
                using vi = vector<int>;

                #define ff first
                #define ss second
                #define pb push_back
                #define all(x) (x).begin(), (x).end()
                #define lb lower_bound
                #define int ll

                const int MOD = 1e9 + 7;

                int N, H[101], DP[2][1001];

                int32_t main() {
                    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
                    cin >> N; int res = 0, K = MOD;
                    for(int l = 1; l <= N; l++)
                        cin >> H[l], K = min(K, H[l] + 1);
                    if(N % 2 == 0) K = 1;
                    while(K--) {
                        for(int l = 0; l <= 1000; l++)
                            DP[0][l] = 1 + min(l, H[1]);
                        for(int l = 2; l <= N; l++) {
                            fill(DP[1], DP[1] + 1001, 0);
                            for(int i = 0; i <= H[l]; i++)
                                DP[1][i] = DP[0][H[l] - i] % MOD;
                            for(int i = 1; i <= 1000; i++) {
                                DP[1][i] += DP[1][i - 1];
                                DP[1][i] %= MOD;
                            }
                            swap(DP[0], DP[1]);
                        }
                        res += DP[0][0]; res %= MOD;
                        for(int l = 1; l <= N; l++) H[l]--;
                    }
                    cout << res << "\n";
                    return 0;
                }


