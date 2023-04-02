#include <bits/stdc++.h>

        using namespace std;

        int N, L, D[22], G[22][22][1001];
        vector<pair<int, int>> DP;
        vector<int> A[22];

        int32_t main()
        {
            ios_base::sync_with_stdio(false);
            cin.tie(0); cout.tie(0);
            freopen("movie.in", "r", stdin);
            freopen("movie.out", "w", stdout);
            cin >> N >> L;
            for(int l = 0; l < N; l++) {
                int K; cin >> D[l] >> K;
                for(int i = 0; i < K; i++) {
                    int U; cin >> U;
                    A[l].push_back(U);
                }
            }
            for(int l = 0; l < N; l++) {
                for(int i = 0; i < N; i++) {
                    if(l == i) continue;
                    for(int j = 0; j < A[l].size(); j++) {
                        auto it = upper_bound(A[i].begin(), A[i].end(), A[l][j] + D[l]);
                        if(it == A[i].begin()) {
                            G[l][i][j] = -1;
                            continue;
                        }
                        it--; int st = *it;
                        if(st + D[i] < A[l][j] + D[l] || st > A[l][j] + D[l]) {
                            G[l][i][j] = -1;
                            continue;
                        }
                        G[l][i][j] = it - A[i].begin();
                    }
                }
            }

            DP.resize(1 << N, {-1, -1});
            int res = N + 1; DP[0] = {0, 0};

            for(int mask = 0; mask < (1 << N); mask++) {
                if(DP[mask].first == -1) continue;
                for(int l = 0; l < N; l++) {
                    if(mask & (1 << l)) continue;
                    int bit = mask | (1 << l);
                    int C;
                    if(mask == 0) C = (A[l][0] == 0 ? 0 : -1);
                    else C = G[DP[mask].first][l][DP[mask].second];
                    if(C == -1) continue;
                    if(DP[bit].first == -1 ||
                       A[DP[bit].first][DP[bit].second] + D[DP[bit].first]
                       < A[l][C] + D[l]) DP[bit] = {l, C};
                    if(A[DP[bit].first][DP[bit].second] + D[DP[bit].first] >= L)
                        res = min(res, __builtin_popcount(bit));
                }
            }
            cout << (res != N + 1 ? res : -1) << "\n";
        }

