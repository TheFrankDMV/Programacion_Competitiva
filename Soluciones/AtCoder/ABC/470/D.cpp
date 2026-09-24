// AtCoder ABC 470 - D "Inverse and Swap"
// https://atcoder.jp/contests/abc470/tasks/abc470_d

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, q;
    cin >> n >> q;

    vector<vll> P(2, vll(n + 1));
    for (int i = 1; i <= n; i++) {
        ll p;
        cin >> p;

        P[0][i] = p;
        P[1][p] = i;
    }

    ll cur = 0;
    for (int i = 0; i < q; i++) {
        ll op;
        cin >> op;

        if (op == 1) {
            ll x, y;
            cin >> x >> y;

            P[cur ^ 1][P[cur][x]] = y;
            P[cur ^ 1][P[cur][y]] = x;
            swap(P[cur][x], P[cur][y]);
        } else cur ^= 1;
    }

    for (int i = 1; i <= n; i++) cout << P[cur][i] << " ";
    cout << "\n";
}
