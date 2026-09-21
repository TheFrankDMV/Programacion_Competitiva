// Codeforces Round 1122 (Div. 3) - B "Three Piles"
// https://codeforces.com/contest/2266/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

void solve() {
    ll a, b, c;
    cin >> a >> b >> c;

    if (a >= b) cout << a + c - b << "\n";
    else {
        ll diff1 = b - a, diff2 = abs(a + c - b);
        cout << max(diff1, diff2) << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}
