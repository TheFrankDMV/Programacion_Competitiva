// AtCoder ABC 473 - D "Coefficient Stair"
// https://atcoder.jp/contests/abc473/tasks/abc473_d

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

ll n, k;

void solve(ll id, ll sum, vll &cur) {
    if (id == n + 1) {
        if (sum != k) return;
        
        for (auto x : cur) cout << x << " ";
        cout << "\n";

        return;
    }

    if (id == n) {
        ll needed = k - sum;
        if (needed % id != 0) return;

        cur.push_back(needed / id);
        solve(n + 1, k, cur);
        cur.pop_back();

        return;
    }

    for (int i = 0; sum + i * id <= k; i++) {
        cur.push_back(i);
        solve(id +1, sum + i * id, cur);
        cur.pop_back();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    cin >> n >> k;

    vll temp;
    solve(1, 0, temp);
}
