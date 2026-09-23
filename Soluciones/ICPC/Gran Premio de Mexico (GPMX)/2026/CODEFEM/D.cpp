// ICPC CODEFEM 2026 - D "Lighting a New Playground"
// https://codeforces.com/gym/106718/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

void solve() {
    ll n, k;
    cin >> n >> k;

    ll ans = (n + k - 1) / k;
    cout << (ans <= 2 ? 0 : ans) << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}
