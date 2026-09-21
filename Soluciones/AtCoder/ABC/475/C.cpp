// AtCoder ABC 475 - C "Walk the Line"
// https://atcoder.jp/contests/abc475/tasks/abc475_c

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, s, l;
    cin >> n >> s >> l;
    s--;
    vll A(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> A[i];

    ll ans = 0, sumRight = 0;
    for (int i = s; i < n; i++) {
        if (i != s) sumRight += A[i - 1];

        ll sumLeft = 0;
        for (int j = s; j >= 0; j--) {
            if (j != s) sumLeft += A[j];

            if ((2 * sumRight + sumLeft <= l) || (sumRight + 2 * sumLeft <= l)) {
                ans = max(ans, ll(i - j + 1));
            }
        }
    }

    cout << ans << "\n";
}
