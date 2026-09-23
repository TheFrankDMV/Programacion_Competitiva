// ICPC CODEFEM 2026 - E "Lizard"
// https://codeforces.com/gym/106718/problem/E

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll INF = 1e18;
const ll dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, m, k, h, sx, sy;
    cin >> n >> m >> k >> h >> sx >> sy;

    priority_queue<array<ll, 3>> pq;
    vector<vll> vis(n + 1, vll(m + 1, -INF));
    for (int i = 0; i < k; i++) {
        ll x, y, f;
        cin >> x >> y >> f;

        pq.push({f, x, y});
        vis[x][y] = f;
    }

    while (!pq.empty()) {
        auto [f, x, y] = pq.top(); pq.pop();
        
        if (f == 0 || f < vis[x][y]) continue;

        for (int i = 0; i < 4; i++) {
            ll nx = x + dx[i], ny = y + dy[i];
            
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (vis[nx][ny] >= f - 1) continue;

            vis[nx][ny] = f - 1;
            pq.push({f - 1, nx, ny});
        }
    }
    
    vector<vector<bool>> isSafe(n + 1, vector<bool>(m + 1, false));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            isSafe[i][j] = (vis[i][j] == -INF);
        }
    }

    vector<vector<bool>> isTarget(n + 1, vector<bool>(m + 1, false));
    for (int i = 0; i < h; i++) {
        ll x, y;
        cin >> x >> y;
        isTarget[x][y] = true;
    }

    if (!isSafe[sx][sy]) {
        cout << "-1 -1\n";
        return 0;
    }

    queue<pair<ll, ll>> q;
    vector<vll> dis(n + 1, vll(m + 1, INF));
    q.push({sx, sy});
    dis[sx][sy] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            ll nx = x + dx[i], ny = y + dy[i];
            
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (!isSafe[nx][ny] || dis[nx][ny] != INF) continue;

            dis[nx][ny] = dis[x][y] + 1;
            q.push({nx, ny});
        }
    }

    ll bst_x = -1, bst_y = -1, mini = INF;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (isTarget[i][j] && dis[i][j] < mini) {
                bst_x = i;
                bst_y = j;
                mini = dis[i][j];
            }
        }
    }

    cout << bst_x << " " << bst_y << "\n";
}
