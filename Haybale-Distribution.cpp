#include <bits/stdc++.h>

		using namespace std;
		using ll = long long;

		#define int ll

		int N, Q;
		int P[200005];
		vector<int> A;

		int lowerB(int v) {
			int lo = 0, hi = N - 1;
			int res = -1;
			while(lo <= hi) {
				int md = (lo + hi) / 2;
				if(A[md] <= v)
					res = md, lo = md + 1;
				else hi = md - 1;
			}
			return res;
		}

		int solve(int v, int a, int b) {
			int i = lowerB(v);
			int res = 0;
			res += (v * (i + 1) - P[i]) * a;
			res += (P[N - 1] - P[i] - (N - i - 1) * v) * b;

			return res;
		}

		int32_t main() {
			ios_base::sync_with_stdio(0);
			cin.tie(0); cout.tie(0);
			///freopen("input.txt", "r", stdin);
			///freopen("output.txt", "w", stdout);

			cin >> N; A = vector<int> (N);
			for(int l = 0; l < N; l++)
				cin >> A[l];
			sort(A.begin(), A.end());

			for(int l = 0; l < N; l++) {
				P[l] = A[l];
				if(l > 0) P[l] += P[l - 1];
			}

			cin >> Q; 
			while(Q--) {
				int X, Y; cin >> X >> Y;
				int lo = A[0], hi = A[N - 1];

				while(lo < hi) {
					int md = (lo + hi) / 2;
					if(solve(md, X, Y) < solve(md + 1, X, Y)) hi = md;
					else lo = md + 1;
				}
				cout << solve(lo, X, Y) << "\n";
			}

		}
