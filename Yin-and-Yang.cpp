#include <bits/stdc++.h>

            using namespace std;
            using ll = long long;

            #define int ll

            int M = 100000;

            int N, A[200005][2][2], B[200005];
            int res, S[100005], turn;
            bool rem[100005];
            vector<pair<int, int>> adj[100005];

            int dfs_size(int v, int p) {
                S[v] = 1;
                for(auto u : adj[v]) {
                    if(u.first == p || rem[u.first]) continue;
                    S[v] += dfs_size(u.first, v);
                }
                return S[v];
            }
            int dfs_centroid(int v, int p, int _N) {
                for(auto u : adj[v]) {
                    if(u.first == p || rem[u.first]) continue;
                    if(2 * S[u.first] >= _N)
                        return dfs_centroid(u.first, v, _N);
                }
                return v;
            }

            void dfs(int v, int p, int cur, int state) {
                for(auto u : adj[v]) {
                    if(u.first == p || rem[u.first]) continue;
                    B[M + cur]++;
                    dfs(u.first, v, cur + u.second, state);
                    B[M + cur]--;
                }
                if(state == 0) {
                    if(cur == 0) res += (A[0][0][1] + A[0][1][1]) + (B[M] > 0);
                    else {
                        if(B[M + cur] == 0) res += A[abs(cur)][1][(cur < 0)];
                        else res += A[abs(cur)][0][(cur < 0)] + A[abs(cur)][1][(cur < 0)];
                    }
                }
                if(state == 1) A[abs(cur)][(B[M + cur] >= 1)][(cur >= 0)]++;
            }

            void build(int v) {
                int _N = dfs_size(v, v);
                int centroid = dfs_centroid(v, v, _N);
                rem[centroid] = 1; M = _N;
                for(int l = 0; l <= M; l++)
                    A[l][0][0] = A[l][0][1] = A[l][1][0] = A[l][1][1] = 0;
                for(auto u : adj[centroid]) {
                    if(rem[u.first]) continue;
                    dfs(u.first, centroid, u.second, 0);
                    dfs(u.first, centroid, u.second, 1);
                }

                for(auto u : adj[centroid]) {
                    if(rem[u.first]) continue;
                    build(u.first);
                }
            }

            int32_t main() {
                ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
                freopen("yinyang.in", "r", stdin);
                freopen("yinyang.out", "w", stdout);
                cin >> N;
                for(int l = 1; l <= N - 1; l++) {
                    int U, V, W; cin >> U >> V >> W;
                    if(W == 0) W = -1;
                    adj[U].push_back({V, W});
                    adj[V].push_back({U, W});
                }
                build(1); cout << res << "\n";
                return 0;
            }


