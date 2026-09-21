// Codeforces Round 1122 (Div. 3) - A "Good Contest"
// https://codeforces.com/contest/2266/problem/A

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

void solve() {
    ll n;
    cin >> n;
    vll A(3);
    for (int i = 0; i < 3; i++) cin >> A[i];

    ll mini = *min_element(A.begin(), A.end());
    cout << n - mini << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}
