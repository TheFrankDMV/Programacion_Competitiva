// Codeforces Round 1122 (Div. 3) - F "MEX Replacement"
// https://codeforces.com/contest/2266/problem/F

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll LOG = 60;
const ll INF = 1e18;

void solve() {
    ll n;
    cin >> n;
    vll X(n), Y(n);
    for (int i = 0; i < n; i++) cin >> X[i] >> Y[i];

    ll maxi = 0, cnt_extra = 0;
    vll cnt(n + LOG, 0);
    for (int i = 0; i < n; i++) {
        maxi = max(maxi, X[i]);
        if (X[i] >= n + LOG) cnt_extra += Y[i];
        else cnt[X[i]] = Y[i];
    }

    auto check = [&](ll k) {
        if (cnt[k]) return true;

        ll tot = cnt_extra, needed = 1;
        for (int i = k + 1; i < n + LOG; i++) {
            tot += cnt[i];
        }
        for (int i = k - 1; i >= 1; i--) {
            if (cnt[i] >= needed) {
                tot += cnt[i] - needed;
            } else {
                needed += needed - cnt[i];
            }

            if (needed >= INF) return false;
        }

        tot += cnt[0];
        return tot >= needed;
    };

    ll lx = 0, rx = n + LOG - 1;
    while (lx < rx) {
        ll mx = (lx + rx + 1) / 2;
        if (check(mx)) lx = mx;
        else rx = mx - 1;
    }

    ll ans = max(maxi, lx);
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}
