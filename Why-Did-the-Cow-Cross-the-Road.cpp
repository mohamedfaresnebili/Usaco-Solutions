#include <bits/stdc++.h>

        using namespace std;

        using ll = long long;
        using ii = pair<int, int>;
        using vi = vector<int>;
        using db = double;

        #define ff first
        #define ss second
        #define pb push_back
        #define all(x) x.begin(), x.end()
        #define lb lower_bound
        #define ub upper_bound
        #define mp make_pair

        using pi = pair<ii, ii>;

        const int nx[4] = {0, 0, -1, 1}, ny[4] = {1, -1, 0, 0};
        int n, t, grid[150][150], dist[150][150][3];
        bool vis[150][150][3];

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            freopen("visitfj.in", "r", stdin);
            freopen("visitfj.out", "w", stdout);
            cin >> n >> t;
            for(int l = 0; l < n; l++)
                for(int i = 0; i < n; i++) {
                    cin >> grid[l][i];
                    for(int j = 0; j < 3; j++)
                        dist[l][i][j] = 1000000007;
                }
            priority_queue<pi, vector<pi>, greater<pi>> pq;
            pq.push({{0, 0}, {0, 0}}); dist[0][0][0] = 0;
            while(!pq.empty()) {
                pi a = pq.top(); pq.pop();
                if(a.ff.ff != dist[a.ss.ff][a.ss.ss][a.ff.ss] || vis[a.ss.ff][a.ss.ss][a.ff.ss]) continue;
                vis[a.ss.ff][a.ss.ss][a.ff.ss] = 1;
                for(int l = 0; l < 4; l++) {
                    int x = a.ss.ff + nx[l], y = a.ss.ss + ny[l];
                    if(x >= 0 && x < n && y >= 0 && y < n) {
                        int len = a.ff.ff + t;
                        int k = a.ff.ss + 1; k %= 3;
                        if((a.ff.ss + 1) % 3 == 0) len += grid[x][y];
                        if(dist[x][y][k] < len || vis[x][y][k]) continue;
                        dist[x][y][k] = len; pq.push({{len, k}, {x, y}});
                    }
                }
            }
            int res = 1000000007;
            for(int l = 0; l < 3; l++) res = min(res, dist[n - 1][n - 1][l]);
            cout << res << "\n";
        }






