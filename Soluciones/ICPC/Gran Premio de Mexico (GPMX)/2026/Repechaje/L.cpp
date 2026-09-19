// ICPC GPMX 2026 Repechaje - L "Ledger of true names"
// https://codeforces.com/gym/106710/problem/L

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

ll check(string a, string b) {
    ll sz = min(a.size(), b.size());
    for (int i = 0; i < sz; i++) {
        if (a[i] != b[i]) return i;
    }
    return sz;
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vector<string> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    ll ans = 0;
    sort(A.begin(), A.end());
    for (int i = 0; i < n - 1; i++) {
        ans = max(ans, check(A[i], A[i + 1]));
    }

    cout << ans << "\n";
}
