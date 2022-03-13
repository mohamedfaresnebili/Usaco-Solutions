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

        int n, m, k, adj[30][30];
        string s; int dp[100005][30], pref[100005][30];
        int solve(int i, int let) {
            if(i == n + 1) return 0;
            if(dp[i][let] != -1) return dp[i][let];
            int u = s[i - 1] - 'a';
            int best = 1000 * 1000 * 1000 + 7;
            if(let < m) best = adj[u][let] + solve(i + 1, let);
            if(i + k <= n + 1)
                for(int l = 0; l < m; l++)
                    best = min(best, pref[i + k - 1][l] - pref[i - 1][l] + solve(i + k, l));
            return dp[i][let] = best;
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("cowmbat.in", "r", stdin);
            freopen("cowmbat.out", "w", stdout);
            cin >> n >> m >> k >> s;
            memset(dp, -1, sizeof dp);
            for(int l = 0; l < m; l++)
                for(int i = 0; i < m; i++)
                    cin >> adj[l][i];
            for(int l = 0; l < m; l++)
                for(int i = 0; i < m; i++)
                    for(int j = 0; j < m; j++)
                        adj[i][j] = min(adj[i][j], adj[i][l] + adj[l][j]);
            for(int l = 0; l <= n; l++)
                pref[l][m] = 1000 * 1000 * 1000 + 7;
            for(int l = 0; l < m; l++) {
                for(int i = 1; i <= n; i++) {
                    pref[i][l] = pref[i - 1][l];
                    int u = s[i - 1] - 'a';
                    pref[i][l] += adj[u][l];
                }
            }
            cout << solve(1, m) << "\n";
        }




