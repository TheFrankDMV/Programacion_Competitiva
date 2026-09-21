// Codeforces Round 1122 (Div. 3) - D "Falling Concrete"
// https://codeforces.com/contest/2266/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

void solve() {
    ll n;
    cin >> n;
    vll A(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    
    vll B(n);
    for (int i = 0; i < n; i++) B[i] = A[i] - i;
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());

    ll ans = 0;
    for (int i = 0; i < (ll)B.size(); i++) {
        ll j = i + 1;
        while (j < (ll)B.size() && B[j] == B[j - 1] + 1) j++;
        ans = max(ans, j-i);
        i = j - 1;
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
