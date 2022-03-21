#include <bits/stdc++.h>

        using namespace std;

        using ll = long long;
        using ii = pair<ll, ll>;

        #define ff first
        #define ss second
        #define pb push_back

        const int nx[4] = {0, 0, 1, -1}, ny[4] = {1, -1, 0, 0};

        struct node{
            int x, y;
        };

        int n, m, grid[501][501], dist[501][501][2];

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("gravity.in", "r", stdin);
            freopen("gravity.out", "w", stdout);
            cin >> n >> m; node s, e;
            for(int l = 0; l < n; l++) {
                for(int i = 0; i < m; i++) {
                    char ch; cin >> ch;
                    if(ch == '.') grid[l][i] = 1;
                    if(ch == 'C') { s = {l, i}; grid[l][i] = 1; }
                    if(ch == 'D') { e = {l, i}; grid[l][i] = 1; }
                    dist[l][i][0] = dist[l][i][1] = 1000000007;
                }
            }
            using pi = array<int, 4>;
            priority_queue<pi, vector<pi>, greater<pi>> q;
            q.push({0, s.x, s.y, 0}); dist[s.x][s.y][0] = dist[s.x][s.y][1] = 0;
            while(!q.empty()) {
                int w = q.top()[0], i = q.top()[1], j = q.top()[2], flip = q.top()[3]; q.pop();
                if(dist[i][j][flip] < w) continue;
                bool done = 0;
                while(i >= 0 && i < n && grid[i][j] == 1) {
                    i += nx[2 + flip];
                    if(i < 0 || i == n) break;
                    if(grid[i][j] == 0) { done = 1; break; }
                    dist[i][j][flip] = min(dist[i][j][flip], w);
                }
                if(!done) continue;
                i += nx[3 - flip];
                for(int l = 0; l < 2; l++) {
                    int x0 = i + nx[l], y0 = j + ny[l];
                    if(x0 >= 0 && x0 < n && y0 >= 0 && y0 < m && grid[x0][y0] == 1) {
                        if(dist[x0][y0][flip] > w) {
                            dist[x0][y0][flip] = w;
                            q.push({w, x0, y0, flip});
                        }
                    }
                }
                flip = 1 - flip;
                while(i >= 0 && i < n && grid[i][j] == 1) {
                    i += nx[2 + flip];
                    if(i < 0 || i == n) break;
                    if(grid[i][j] == 0) {
                        done = 1; break;
                    }
                    dist[i][j][flip] = min(dist[i][j][flip], w + 1);
                }
                if(!done) continue;
                i += nx[3 - flip];
                q.push({w + 1, i, j, flip});
            }
            int res = min(dist[e.x][e.y][0], dist[e.x][e.y][1]);
            cout << ((res != 1000000007) ? res : -1) << "\n";
        }
