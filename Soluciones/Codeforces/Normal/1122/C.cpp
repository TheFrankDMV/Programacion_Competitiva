// Codeforces Round 1122 (Div. 3) - C "AND, OR, Sort!"
// https://codeforces.com/contest/2266/problem/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

void solve() {
    ll n; string s;
    cin >> n >> s;
    s = "#" + s;

    vector<vll> pref(2, vll(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        pref[0][i] = pref[0][i - 1] + (s[i] == '0');
        pref[1][i] = pref[1][i - 1] + (s[i] == '1');
    }

    if (s[1] == '1') {
        cout << pref[0][n] << "\n";
        return;
    }

    ll ans = pref[1][n];
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') {
            ans = min(ans, pref[1][i - 1] + (pref[0][n] - pref[0][i - 1]));
        }
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
