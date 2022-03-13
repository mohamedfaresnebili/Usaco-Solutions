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

        const int MOD = 1000 * 1000 * 1000 + 9;
        ll n, m, k, arr[1005], arr0[1005];
        ll dp[1005][1005][12];
        ll solve(ll i, ll j, ll calc) {
            if(i == n || j == m) return (calc == 0);
            if(dp[i][j][calc] != -1) return dp[i][j][calc] % MOD;
            ll best = solve(i + 1, j, calc) % MOD;
            best += solve(i, j + 1, calc) % MOD;
            best -= solve(i + 1, j + 1, calc) % MOD;
            best += MOD;
            if(arr[i] > arr0[j] && calc) best += solve(i + 1, j + 1, calc - 1) % MOD;
            return dp[i][j][calc] = best % MOD;
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("team.in", "r", stdin);
            freopen("team.out", "w", stdout);
            cin >> n >> m >> k;
            memset(dp, -1, sizeof dp);
            for(ll l = 0; l < n; l++) cin >> arr[l];
            for(ll l = 0; l < m; l++) cin >> arr0[l];
            cout << solve(0, 0, k) % MOD << "\n";
        }
