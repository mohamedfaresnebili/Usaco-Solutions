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

                int N, Q, cur = 1, res[100001];
                bool rem[300001], A[100001], vis[100001];
                pair<int, int> E[300001];
                vector<int> adj[100001];
                vector<array<int, 3>> Qr;
                void dfs(int v, int t) {
                    if(res[v] > 0) return;
                    res[v] = t;
                    for(auto u : adj[v]) dfs(u, t);
                }

                int32_t main() {
                    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
                    cin >> N >> Q;
                    for(int l = 1; l <= N; l++) A[l] = 1;
                    for(int l = 0; l < Q; l++) {
                        char t; cin >> t;
                        if(t == 'A') {
                            int U, V; cin >> U >> V; E[cur++] = {U, V};
                            Qr.push_back({0, U, V});
                        }
                        if(t == 'R') {
                            int R; cin >> R; rem[R] = 1;
                            Qr.push_back({1, R, R});
                        }
                        if(t == 'D') {
                            int V; cin >> V; A[V] = 0;
                            Qr.push_back({2, V, V});
                        }
                    }
                    for(int R = 1; R < cur; R++) {
                        if(rem[R]) continue;
                        adj[E[R].ff].push_back(E[R].ss);
                        adj[E[R].ss].push_back(E[R].ff);
                    }
                    for(int l = 1; l <= N; l++)
                        if(A[l] > 0) dfs(l, Q);
                    for(int l = Q - 1; l > 0; l--) {
                        int t = Qr[l][0];
                        if(t == 1) {
                            int R = Qr[l][1];
                            int U = E[R].ff, V = E[R].ss;
                            adj[U].push_back(V);
                            adj[V].push_back(U);
                            if(res[U] != 0 || res[V] != 0) {
                                dfs(U, l); dfs(V, l);
                            }
                        }
                        if(t == 2) { int V = Qr[l][1]; dfs(V, l); }
                    }
                    for(int l = 1; l <= N; l++)
                        cout << res[l] << "\n";
                    return 0;
                }




