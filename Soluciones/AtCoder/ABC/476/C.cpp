// AtCoder ABC 476 - C "Third Largest Number"
// https://atcoder.jp/contests/abc476/tasks/abc476_c

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

    vll cur = {A[0], A[1], A[2]};
    sort(cur.rbegin(), cur.rend());
    cout << cur[2] << "\n";

    for (int i = 3; i < n; i++) {
        ll val = A[i];
        for (int j = 0; j < 3; j++) {
            if (val > cur[j]) swap(val, cur[j]);
        }

        cout << cur[2] << "\n";
    }
}
