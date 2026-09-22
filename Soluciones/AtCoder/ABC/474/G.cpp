// AtCoder ABC 475 - G "LRUD Moving 2"
// https://atcoder.jp/contests/abc474/tasks/abc474_g

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

void solve() {
    ll n, k;
    cin >> n >> k;

    ll max_k = (n * n) / 2;
    ll min_k = n - 1;
    if (n % 2 == 0 || k % 2 == 1 || k < min_k || k > max_k) {
        cout << "No\n";
        return;
    }

    bool transposed = false;
    if (k > (min_k + max_k) / 2) {
        k = (n * n + 2 * n - 3) / 2 - k;
        transposed = true;
    }

    string ans;
    ll delta = k - min_k;
    ll B = delta / (n - 1);
    ll rem = delta % (n - 1);
    ll W = (rem > 0 ? rem + 1 : 0);

    for (int i = 0; i < B; i++) {
        ans += string(n - 1, 'R') + "D" + string(n - 1, 'L') + "D";
    }

    if (W > 0) {
        ans += string(W - 1, 'R') + "D" + string(W - 1, 'L') + "D";
    }

    for (int i = 0; i < n; i++) {
        ll r = (i < W ? 2 * B + 2 : 2 *B);
        ll steps = (n - 1) - r;

        if (i % 2 == 0) ans += string(steps, 'D');
        else ans += string(steps, 'U');

        if (i < n - 1) ans += "R";
    }


    if (transposed) {
        for (auto &c : ans) {
            if (c == 'R') c = 'D';
            else if (c == 'L') c = 'U';
            else if (c == 'D') c = 'R';
            else if (c == 'U') c = 'L';
        }
    }

    cout << "Yes\n" << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}
