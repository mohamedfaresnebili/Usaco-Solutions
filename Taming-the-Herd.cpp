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

        int n, arr[255], dp[255][255][255];
        int solve(int i, int curr, int t_left) {
            if(i == n) {
                if(t_left > 0) return 1000 * 1000 * 1000 + 7;
                return 0;
            }
            if(dp[i][curr][t_left] != -1) return dp[i][curr][t_left];
            if(i == 0)
                return (arr[i] != curr) + solve(i + 1, 1, t_left - 1);
            int best = (arr[i] != curr) + solve(i + 1, curr + 1, t_left);
            if(t_left > 0)
                best = min(best, (arr[i] != 0) + solve(i + 1, 1, t_left - 1));
            return dp[i][curr][t_left] = best;
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("taming.in", "r", stdin);
            freopen("taming.out", "w", stdout);
            cin >> n; memset(dp, -1, sizeof dp);
            for(int l = 0; l < n; l++) cin >> arr[l];
            for(int l = 1; l <= n; l++) {
                cout << solve(0, 0, l) << "\n";
            }
        }

