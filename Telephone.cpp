#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")

        using namespace std;

        using ll = long long;
        using ii = pair<ll, ll>;

        #define ff first
        #define ss second
        #define pb push_back

        const int MOD = 1e9 + 7;

        int n, k, arr[50001], mat[51][51];
        vector<int> dist[51];

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            /// freopen("gravity.in", "r", stdin);
            /// freopen("gravity.out", "w", stdout);
            cin >> n >> k;
            for(int l = 1; l <= n; l++) cin >> arr[l];
            for(int l = 1; l <= k; l++) {
                for(int i = 1; i <= k; i++) {
                    char c; cin >> c;
                    mat[l][i] = c - '0';
                }
                mat[l][0] = mat[l][arr[n]];
            }
            arr[n] = 0;
            for(int l = 0; l <= k; l++) {
                dist[l].assign(n + 1, -1);
            }
            deque<ii> q; q.push_front({arr[1], 1});
            dist[arr[1]][1] = 0;
            while(!q.empty()) {
                int b = q.front().ff, a = q.front().ss; q.pop_front();
                if(a - 1 >= 1 && dist[b][a - 1] == -1) {
                    dist[b][a - 1] = dist[b][a] + 1;
                    q.push_back({b, a - 1});
                }
                if(a + 1 <= n && dist[b][a + 1] == -1) {
                    dist[b][a + 1] = dist[b][a] + 1;
                    q.push_back({b, a + 1});
                }
                if(mat[b][arr[a]] && dist[arr[a]][a] == -1) {
                    dist[arr[a]][a] = dist[b][a];
                    q.push_front({arr[a], a});
                }
            }
            cout << dist[0][n] << "\n";
        }

