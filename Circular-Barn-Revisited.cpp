#include <bits/stdc++.h>

        using namespace std;

        using ll = long long;
        using ii = pair<ll, ll>;
        using vi = vector<int>;

        #define ff first
        #define ss second
        #define pb push_back
        #define all(x) x.begin(), x.end()
        #define lb lower_bound
        #define ub upper_bound

        int n, k; ll arr[100]; ll dp[100][100][100][7];
        ll solve(int i, int base, int prec, int state) {
            if(i == base) return 1000000007;
            if(dp[i][base][prec][state] != -1) return dp[i][base][prec][state];
            ll best = solve((n + i - 1) % n, base, prec, state);
            if(state) {
                ll curr = 0;
                for(int l = prec; l != i; l = (n + l - 1) % n) {
                    if(l == prec) continue;
                    if(l >= i) curr += arr[l] * (l - i);
                    else curr += arr[l] * (l + n - i);
                }
                best = min(best, curr + solve((n + i - 1) % n, base, i, state - 1));
            }
            if(!state) {
                ll curr = 0;
                for(int l = i; l != base; l = (n + l - 1) % n) {
                    if(l == prec) continue;
                    if(l >= base) curr += arr[l] * (l - base);
                    else curr += arr[l] * (l + n - base);
                }
                return curr;
            }
            return dp[i][base][prec][state] = best;
        }

        int32_t main()
        {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("cbarn2.in", "r", stdin);
            freopen("cbarn2.out", "w", stdout);
            cin >> n >> k; ll res = 1000000007;
            memset(dp, -1, sizeof dp);
            for(int l = 0; l < n; l++) cin >> arr[l];
            for(int l = 0; l < (n + k - 1) / k ; l++) {
                res = min(res, solve((n + l - 1) % n, l, l, k - 1));
            }
            cout << res << "\n";
            return 0;
        }
