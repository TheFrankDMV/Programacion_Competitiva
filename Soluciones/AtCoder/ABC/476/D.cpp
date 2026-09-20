// AtCoder ABC 476 - D "Automat"
// https://atcoder.jp/contests/abc476/tasks/abc476_d

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, m, k, x, y;
    cin >> n >> m >> k >> x >> y;
    vll A(n + 1, 0), B(m + 1, 0);
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= m; i++) cin >> B[i];

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    vll psum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        psum[i] = psum[i - 1] + A[i];
    }

    ll ans = 0;
    for (int i = 0; i <= m; i++) {
        if (y < (B[i] + k - 1) / k) break;

        y -= (B[i] + k - 1) / k;
        x += (-B[i] % k + k) % k;

        ll lx = 0, rx = n;
        while (lx < rx) {
            ll mid = (lx + rx + 1) / 2; 
            if (psum[mid] <= x + y * k) lx = mid;
            else rx = mid - 1;
        }

        ans = max(ans, i + lx);
    }

    cout << ans << "\n";
}
