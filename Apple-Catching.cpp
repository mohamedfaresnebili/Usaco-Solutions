#include <bits/stdc++.h>

                    using namespace std;
                    using ll = long long;

                    int N;
                    int q[200005], t[200005];
                    int x[200005], n[200005];
                    vector<array<int, 3>> cow, apple;

                    bool compare(array<int, 3> U, array<int, 3> V) {
                        if(U[1] != V[1]) return U[1] < V[1];
                        if(U[0] != V[0]) return U[0] < V[0];
                        return U[2] < V[2];
                    }

                    int32_t main() {
                        ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
                        cin >> N;

                        for(int l = 1; l <= N; l++) {
                            cin >> q[l] >> t[l] >> x[l] >> n[l];
                            if(q[l] == 1) cow.push_back({t[l] + x[l], t[l] - x[l], n[l]});
                            if(q[l] == 2) apple.push_back({t[l] + x[l], t[l] - x[l], n[l]});
                        }

                        sort(cow.begin(), cow.end(), compare);
                        sort(apple.begin(), apple.end(), compare);

                        int i = 0, res = 0;
                        set<pair<int, pair<int, int>>> S;

                        for(auto u : apple) {
                            while(i < (int)cow.size() && cow[i][1] <= u[1]) {
                                S.insert({cow[i][0], {cow[i][2], cow[i][1]}}); i++;
                            }
                            int K = u[2];
                            while(K > 0 && !S.empty() && (*S.begin()).first <= u[0]) {
                                auto it = S.lower_bound({u[0], {0, 0}});
                                if(it == S.end() || (*it).first > u[0]) it--;
                                int px = (*it).first, py = (*it).second.second, c = (*it).second.first;
                                int get = min(c, K); res += get; K -= get; c -= get; S.erase(*it);
                                if(c > 0) S.insert({px, {c, py}});
                            }
                        }

                        cout << res << "\n";
                    }


