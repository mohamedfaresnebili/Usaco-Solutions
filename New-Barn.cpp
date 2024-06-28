#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

        using namespace std;

        int Q, N;
        vector<array<int, 2>> qry;
        vector<int> adj[100001];
        set<pair<int, int>> A[100001], B[100001];
        int sub[100001], par[100001];
        int subT[100001][17], depT[100001][17];
        int levF[100001];
        bool inact[100001], rem[100001];

        int getSize(int v, int p) {
            sub[v] = 1;
            for(auto u : adj[v]) {
                if(u == p || rem[u]) continue;
                sub[v] += getSize(u, v);
            }
            return sub[v];
        }
        int getCentroid(int v, int p, int s) {
            for(auto u : adj[v]) {
                if(u == p || rem[u]) continue;
                if(2 * sub[u] >= s)
                    return getCentroid(u, v, s);
            }
            return v;
        }
        int dfs(int v, int p, int cur, int dep, int level) {
            depT[v][level] = dep;
            subT[v][level] = cur;
            for(auto u : adj[v]) {
                if(u == p || rem[u]) continue;
                dfs(u, v, cur, dep + 1, level);
            }
        }

        void build(int v, int p, int D) {
            int _N = getSize(v, -1);
            int centroid = getCentroid(v, -1, _N);
            rem[centroid] = 1; par[centroid] = p; int cur = 0;
            levF[centroid] = D;
            for(auto u : adj[centroid]) {
                if(rem[u]) continue;
                dfs(u, centroid, cur++, 1, D);
            }
            for(auto u : adj[centroid]) {
                if(rem[u]) continue;
                build(u, centroid, D + 1);
            }
        }
        void update(int V) {
            int level = levF[V];
            int U = par[V]; level--;
            while(U != -1) {
                auto it = A[U].lower_bound({subT[V][level], 0});
                if(it == A[U].end() || (*it).first != subT[V][level]) {
                    A[U].insert({subT[V][level], depT[V][level]});
                    B[U].insert({-depT[V][level], subT[V][level]});
                }
                else {
                    if(depT[V][level] > (*it).second) {
                        auto pt1 = A[U].find({subT[V][level], (*it).second});
                        auto pt2 = B[U].find({-(*it).second, subT[V][level]});
                        if(pt1 != A[U].end()) A[U].erase(pt1);
                        if(pt2 != B[U].end()) B[U].erase(pt2);
                        A[U].insert({subT[V][level], depT[V][level]});
                        B[U].insert({-depT[V][level], subT[V][level]});
                    }
                }
                while(B[U].size() > 2) {
                    auto it = B[U].end(); it--;
                    int X = (*it).first, Y = (*it).second; X = -X;
                    if(it != B[U].begin()) B[U].erase(it);
                    A[U].erase(A[U].find({Y, X}));
                }
                U = par[U]; --level;
            }
        }
        int query(int V) {
            int res = 0;
            if(!B[V].empty()) res = -(*B[V].begin()).first;
            int level = levF[V];
            int U = par[V]; level--;
            while(U != -1) {
                if(inact[U]) {
                    int D = depT[V][level];
                    auto it = B[U].begin();
                    while(it != B[U].end() && (*it).second == subT[V][level]) ++it;
                    if(it != B[U].end())
                        res = max(res, D - (*it).first);
                    res = max(res, D);
                }
                U = par[U]; --level;
            }
            return res;
        }

        int32_t main() {
            ios_base::sync_with_stdio(0);
            cin.tie(0); cout.tie(0);
            freopen("newbarn.in", "r", stdin);
            freopen("newbarn.out", "w", stdout);
            cin >> Q;
            for(int l = 0; l < Q; l++) {
                char ch; int V; cin >> ch >> V;
                if(ch == 'B') {
                    qry.push_back({1, ++N});
                    if(V != -1) {
                        adj[N].push_back(V);
                        adj[V].push_back(N);
                    }
                }
                if(ch == 'Q') qry.push_back({2, V});
            }
            reverse(qry.begin(), qry.end());
            for(int l = 1; l <= N; l++) {
                if(!rem[l]) build(l, -1, 0);
            }

            for(int l = 1; l <= N; l++)
                adj[l].clear();
            while(!qry.empty()) {
                int t = qry.back()[0], V = qry.back()[1]; qry.pop_back();
                if(t == 1) inact[V] = 1, update(V);
                if(t == 2) cout << query(V) << "\n";
            }
            return 0;
        }

