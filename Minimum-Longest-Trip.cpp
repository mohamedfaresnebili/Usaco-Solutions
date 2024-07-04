#include <bits/stdc++.h>

		using namespace std;
		using ll = long long;

		#define int ll

		int N, M;
		vector<pair<int, int>> rev[200005];
		int out[200005], rnk[200005];
		int len[200005], sum[200005];
		vector<array<int, 4>> cand[200005];


		int32_t main() {
			ios_base::sync_with_stdio(0);
			cin.tie(0); cout.tie(0);

			///freopen("input.txt", "r", stdin);
			///freopen("output.txt", "w", stdout);

			cin >> N >> M;
			for(int l = 0; l < M; l++) {
				int U, V, W; cin >> U >> V >> W;
				rev[V].push_back({U, W});
				out[U]++;
			}

			vector<int> Q;

			for(int l = 1; l <= N; l++) {
				if(out[l] > 0) continue;
				Q.push_back(l);
			}

			while(!Q.empty()) {
				vector<int> nQ;

				for(auto u : Q) {
					for(auto v : rev[u]) {
						out[v.first]--;
						cand[v.first].push_back({-len[u], v.second, rnk[u], sum[u] + v.second});
						if(out[v.first] == 0) {
							len[v.first] = len[u] + 1;
							nQ.push_back(v.first);
						}
					}
				}

				swap(Q, nQ);

				vector<array<int, 3>> R;
				for(auto u : Q) {
					sort(cand[u].begin(), cand[u].end());
					array<int, 4> K = cand[u][0];
					sum[u] = K[3];
					R.push_back({K[1], K[2], u});
				}

				sort(R.begin(), R.end());
				for(int l = 0; l < R.size(); l++)
					rnk[R[l][2]] = l;

			}

			for(int l = 1; l <= N; l++)
				cout << len[l] << " " << sum[l] << "\n";

		}
