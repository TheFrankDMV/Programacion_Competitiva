// AtCoder ABC 475 - F "Rectangle Filling"
// https://atcoder.jp/contests/abc475/tasks/abc475_f

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll INF = 1e18;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, m;
    cin >> n >> m;
    vector<vll> grid(n, vll(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            grid[i][j] = (c == '.' ? 1 : 0);
        }
    }

    if (n > m) {
        vector<vll> new_grid(m, vll(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                new_grid[j][(n - 1) -i] = grid[i][j];
            }
        }

        swap(grid, new_grid);
        swap(n, m);
    }

    ll ans = 1;
    for (int d = 0; d < n; d++) {
        vll valid(m, false);

        for (int u = d; u < n; u++) {
            vll curValid;
            ll miniD = INF, miniU = INF, ptr = 0;

            for (int j = m - 1; j >= 0; j--) {
                valid[j] |= grid[u][j];
                if (grid[d][j]) miniD = j;
                if (grid[u][j]) miniU = j;

                if (valid[j]) {
                    curValid.push_back(j);
                    while (ptr < ll(curValid.size()) && curValid[ptr] >= max(miniD, miniU)) {
                        ptr++;
                    }

                    ans += ptr;
                }
            }
        }
    }

    cout << ans << "\n";
}
