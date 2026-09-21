// AtCoder ABC 475 - B "Change"
// https://atcoder.jp/contests/abc475/tasks/abc475_b

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;

    ll x = 0, y = 0, z = 0;
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        a = ((-a) % 1000 + 1000) % 1000;

        z += a/100;
        a %= 100;

        y += a/10;
        a %= 10;

        x += a;
    }

    cout << x << " " << y << " " << z << "\n";
}
