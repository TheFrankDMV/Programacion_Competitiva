// AtCoder ABC 472 - C "On a Diet"
// https://atcoder.jp/contests/abc472/tasks/abc472_c

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, m, k;
    cin >> n >> m >> k;

    vll val(n, 0);
    ll cur = 0;
    for (int i = 0; i < n; i++) {
        if (i >= m) cur -= val[i - m];

        ll a;
        cin >> a;
        cur += a;

        if (cur <= k) {
            cout << "Yes\n";
            val[i] = a;
        } else {
            cout << "No\n";
            cur -= a;
        }
    }
}
