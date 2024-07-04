#include <bits/stdc++.h>

		using namespace std;

		int N;
		int A[755][755], DP[755][755];

		int32_t main() {
			ios_base::sync_with_stdio(0);
			cin.tie(0); cout.tie(0);

			cin >> N;
			for(int l = 1; l < N; l++) {
				string S; cin >> S;
				for(int i = 0; i < S.size(); i++) {
					int K = (S[i] - '0');
					A[l][l + i + 1] = K;
				}
			}

			int res = 0;
			for(int l = N - 1; l >= 1; l--) {
				for(int i = l + 1; i <= N; i++) {
					
					for(int j = l; j < i; j++) 
						DP[l][i] ^= A[l][j] * DP[j][i];
					DP[l][i] ^= A[l][i];
					res += DP[l][i];

				}
			}

			cout << res << "\n";

		}
