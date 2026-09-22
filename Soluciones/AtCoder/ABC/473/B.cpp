// AtCoder ABC 473 - B "Old Maid"
// https://atcoder.jp/contests/abc473/tasks/abc473_b

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_A = 105;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vll freq(MAX_A, 0);
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        freq[a]++;
    }

    ll ans = 0;
    for (int i = 0; i < MAX_A; i++) {
        if (freq[i] & 1) ans += i;
    }

    cout << ans << "\n";
}
