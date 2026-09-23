// AtCoder ABC 472 - B "Break a Stick"
// https://atcoder.jp/contests/abc472/tasks/abc472_b

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vll A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    ll sum = accumulate(A.begin(), A.end(), 0ll);
    ll ans = sum, cur = 0;
    for (int i = 0; i < n; i++) {
        cur += A[i];
        ans = min(ans, abs(cur - (sum - cur)));
    }

    cout << ans << "\n";
}
