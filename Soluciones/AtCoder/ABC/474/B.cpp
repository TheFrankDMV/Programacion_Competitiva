// AtCoder ABC 474 - B "Exit Order"
// https://atcoder.jp/contests/abc474/tasks/abc474_b

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vll P(n);
    for (int i = 0; i < n; i++) cin >> P[i];

    for (int l = 0; l < n; l += 10) {
        ll r = min(n - 1, ll(l + 9));
        vll A(r - l + 1);
        iota(A.begin(), A.end(), l + 1);
        
        vll B;
        for (int i = l; i <= r; i++) B.push_back(P[i]);
        sort(B.begin(), B.end());

        if (A != B) {
            cout << "No\n";
            return 0;
        }
    }

    cout << "Yes\n";
}
