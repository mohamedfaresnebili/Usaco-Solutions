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

        int n, k; ll arr[2005]; ll dp[205][10];
        ll solve(int i, int state, int en) {
            if(i == en) return 0;
            if(dp[i][state] != -1) return dp[i][state];
            ll best = 1000000007, curr = 0;
            for(int l = i + 1; l < en; l++) {
                curr += (l - i) * arr[l];
                if(state) best = min(best, curr + solve(l + 1, state - 1, en));
            }
            return dp[i][state] = best;
        }

        int32_t main()
        {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("cbarn2.in", "r", stdin);
            freopen("cbarn2.out", "w", stdout);
            cin >> n >> k; ll res = 1000000007;
            memset(dp, -1, sizeof dp);
            for(int l = 1; l <= n; l++) cin >> arr[l];
            for(int l = n + 1; l <= 2 * n; l++) arr[l] = arr[l - n];
            for(int l = 1; l <= n; l++) {
                memset(dp, -1, sizeof dp);
                res = min(res, solve(l, k, n + l));
            }
            cout << res << "\n";
            return 0;
        }

