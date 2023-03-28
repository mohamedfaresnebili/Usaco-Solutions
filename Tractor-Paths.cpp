#include <bits/stdc++.h>

        using namespace std;

        int N, M;
        string SP, S;
        int P[200005][20], C[200005][20];
        int L[200005][20], R[200005][20];
        int Pr[200005], Sf[200005];

        int32_t main()
        {
            ios_base::sync_with_stdio(false);
            cin.tie(0); cout.tie(0);
            cin >> N >> M >> S >> SP;

            for(int l = 0; l < N; l++) {
                Pr[l] = (SP[l] == '1');
                if(l > 0) Pr[l] += Pr[l - 1];
            }
            for(int i = N - 1; i >= 0; i--) {
                Sf[i] = (SP[i] == '1');
                if(i < N - 1) Sf[i] += Sf[i + 1];
            }

            deque<int> Q;
            for(int l = 0, i = 1, j = 1; l < 2 * N; l++) {
                if(S[l] == 'L')
                    Q.push_front(i++);
                if(S[l] == 'R') {
                    L[j][0] = Pr[Q.front() - 1];
                    P[j++][0] = Q.front();
                    Q.pop_back();
                }
            }
            for(int l = 2 * N - 1, i = N, j = N; l >= 0; l--) {
                if(S[l] == 'R')
                    Q.push_front(i--);
                if(S[l] == 'L') {
                    if(Q.front() > 1)
                        R[j][0] = Pr[Q.front() - 2];
                    C[j--][0] = Q.front();
                    Q.pop_back();
                }
            }

            for(int l = 1; l < 20; l++)
                for(int i = 1; i <= N; i++) {
                    P[i][l] = P[P[i][l - 1]][l - 1];
                    L[i][l] = L[i][l - 1] + L[P[i][l - 1]][l - 1];

                    C[i][l] = C[C[i][l - 1]][l - 1];
                    R[i][l] = R[i][l - 1] + R[C[i][l - 1]][l - 1];
                }

            while(M--) {
                int U, V; cin >> U >> V;
                int A = U, B = V;
                int res = 0, ans = 0;
                for(int l = 20 - 1; l >= 0; l--) {
                    if(C[V][l] > A) {
                        ans += L[U][l] - R[V][l];
                        U = P[U][l], V = C[V][l];
                        res += (1 << l);
                    }
                }
                ans += (SP[A - 1] == '1');
                ans += (SP[B - 1] == '1');
                cout << res + 1 << " " << ans << "\n";
            }
        }
