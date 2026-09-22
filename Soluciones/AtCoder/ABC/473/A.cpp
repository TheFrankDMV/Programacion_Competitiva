// AtCoder ABC 473 - A "Second Half Sum"
// https://atcoder.jp/contests/abc473/tasks/abc473_a

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vll A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    ll ans = 0;
    for (int i = n / 2; i < n; i++) ans += A[i];
    
    cout << ans << "\n";
}
