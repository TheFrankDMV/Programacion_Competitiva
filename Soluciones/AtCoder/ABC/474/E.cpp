// AtCoder ABC 475 - E "One Time Coupon"
// https://atcoder.jp/contests/abc474/tasks/abc474_e

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

void solve() {
    ll n;
    cin >> n;
    vll A(n), B(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i] >> B[i];
    }

    vll diff(n);
    for (int i = 0; i < n; i++) {
        diff[i] = A[i] - B[i];
    }
    sort(diff.rbegin(), diff.rend());

    ll ans = accumulate(A.begin(), A.end(), 0ll), cur = ans;
    ll mini = *min_element(A.begin(), A.end());
    for (int i = 1; i <= n; i++) {
        cur -= diff[i - 1];

        ll extra = max(0ll, 2 * i - n);
        ans = min(ans, cur + extra * mini);
    }

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
