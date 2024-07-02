#include <bits/stdc++.h>

		using namespace std;

		string perm;
		string S;
		int N, K, adj[25][25];
		int bit[(1 << 20) + 5];
		map<char, int> M;


		int32_t main() {
			ios_base::sync_with_stdio(0);
			cin.tie(0); cout.tie(0);
			///freopen("input", "r", stdin);
			///freopen("output", "w", stdout);
			cin >> S; N = S.length();
			int res = N; set<char> st;
			for(int l = 0; l < N; l++) {
				if(st.count(S[l])) continue;
				st.insert(S[l]); perm += S[l]; ++K;
			}
			for(int l = 0; l < K; l++)
				M[perm[l]] = l;
			for(int l = 1; l < N; l++) {
				int i = M[S[l]], j = M[S[l - 1]];
				adj[j][i]++;
			}
			for(int l = 1; l < (1 << K); l++) bit[l] = N;
			bit[0] = 1;
			for(int l = 1; l < (1 << K); l++) {
				for(int i = 0; i < K; i++) {
					if(l & (1 << i)) {
						int mask = l ^ (1 << i);
						int cur = 0;
						for(int j = 0; j < K; j++)
							if(l & (1 << j))
								cur += adj[M[perm[i]]][M[perm[j]]];
						bit[l] = min(bit[l], bit[mask] + cur);
					}
				}
			}
			cout << bit[(1 << K) - 1] << "\n";
		}
