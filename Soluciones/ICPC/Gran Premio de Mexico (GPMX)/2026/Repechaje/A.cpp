// ICPC GPMX 2026 Repechaje - A "Avatar queries"
// https://codeforces.com/gym/106710/problem/A

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll INF = 1e18;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, q;
    cin >> n >> q;
    vll A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    ll maxi = -INF;
    vll ans(n + 1, -INF);
    for (int i = n - 1; i >= 0; i--) {
        maxi = max(maxi + A[i], A[i]);
        ans[i] = max(ans[i + 1], maxi);
    }

    for (int i = 0; i < q; i++) {
        ll x; 
        cin >> x;
        cout << ans[x] << "\n";
    }
}
