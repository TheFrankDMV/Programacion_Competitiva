// ICPC CODEFEM 2026 - H "Enough Cupcakes?"
// https://codeforces.com/gym/106718/problem/H

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, c;
    cin >> n >> c;
    vll A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    ll sum = accumulate(A.begin(), A.end(), 0);
    cout << (sum <= c ? "YES" : "NO") << " " << abs(c - sum) << "\n";
}
