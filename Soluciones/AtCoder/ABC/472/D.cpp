// AtCoder ABC 472 - D "Bomber Mad"
// https://atcoder.jp/contests/abc472/tasks/abc472_d

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;

const ll INF = 1e18;
const ll dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, m, k;
    cin >> n >> m >> k;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    vll cntRow(n, 0), cntCol(m, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') {
                cntRow[i]++; cntCol[j]++;
            }
        }
    }

    vector<vll> dis(n, vll(m, INF));
    queue<pll> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (cntRow[i] == 0 && cntCol[j] == 0) {
                q.push({i, j});
                dis[i][j] = 0;
            }
        }
    }

    ll ans = 0;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        ans++;
        if (dis[x][y] == k) continue;

        for (int i = 0; i < 4; i++) {
            ll nx = x + dx[i], ny = y + dy[i];
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (grid[nx][ny] == '#' || dis[nx][ny] != INF) continue;

            dis[nx][ny] = dis[x][y] + 1;
            q.push({nx, ny});
        }
    }

    cout << ans << "\n";
}
