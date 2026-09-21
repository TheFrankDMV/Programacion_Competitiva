// AtCoder ABC 476 - G "Increasing Popcount"
// https://atcoder.jp/contests/abc476/tasks/abc476_g

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const int LOG = 60;

ll binom[LOG][LOG];

void setup() {
    for (int i = 0; i < LOG; i++) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; j++) {
            binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
        }
    }
}

ll msb(ll x) {
    for (int i = LOG - 1; i >= 0; i--) {
        if ((x >> i) & 1) return i;
    }
    return -1;
}
ll lsb(ll x) {
    return msb(x & -x);
}

void solve() {
    ll l, r;
    cin >> l >> r;
    r++;

    vll dp(LOG);
    while (l < r) {
        ll sz = min(msb(r - l), lsb(l));
        ll pref = __builtin_popcountll(l);

        for (int i = 0; i <= sz; i ++) {
            dp[pref + i] += binom[sz][i];
        }
        for (int i = LOG - 2; i >=0; i--) {
            dp[i] = max(dp[i], dp[i + 1]);
        }

        l += (1ll << sz);
    }

    cout << dp[0] << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    setup();

    ll tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}
