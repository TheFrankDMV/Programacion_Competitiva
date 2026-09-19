// ICPC GPMX 2026 Repechaje - N "Nord's Cairn"
// https://codeforces.com/gym/106710/problem/N

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll LIM = 2e6;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    
    ll l, r;
    cin >> l >> r;

    ll ans = 0;
    for (ll i = 0; i < LIM; i++) {
        ll val = i * (i + 1) / 2;
        ans += (l <= val && val <= r);
    }

    cout << ans << "\n";
}
