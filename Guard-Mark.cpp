#include <bits/stdc++.h>

        using namespace std;

        int N, H, DP[(1 << 20) + 5][2];
        vector<array<int, 3>> A;

        int32_t main()
        {
            ios_base::sync_with_stdio(false);
            cin.tie(0); cout.tie(0);
            freopen("guard.in", "r", stdin);
            freopen("guard.out", "w", stdout);
            cin >> N >> H;
            for(int l = 0; l < N; l++) {
                int h, w, s; cin >> h >> w >> s;
                A.push_back({h, w, s});
            }
            int res = 0;
            DP[0][0] = 0, DP[0][1] = 1000000007;
            for(int mask = 1; mask < (1 << N); mask++) {
                for(int l = 0; l < N; l++) {
                    if(mask & (1 << l)) {
                        int P = mask ^ (1 << l);
                        DP[mask][0] += A[l][0];
                        DP[mask][1] = max(DP[mask][1],
                                    min(DP[P][1] - A[l][1], A[l][2]));
                    }
                }
            }
            for(int l = 1; l < (1 << N); l++)
                if(DP[l][0] >= H) res = max(res, DP[l][1]);
            if(res == 0) cout << "Mark is too tall\n";
            else cout << res << "\n";
        }

