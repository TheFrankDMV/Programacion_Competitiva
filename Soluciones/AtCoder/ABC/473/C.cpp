// AtCoder ABC 473 - C "Change Schools"
// https://atcoder.jp/contests/abc473/tasks/abc473_c

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, k;
    cin >> n >> k;
    vll freq(k + 1, 0);
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        freq[a]++;
    }

    ll ans = 0, maxi = *max_element(freq.begin(), freq.end());
    for (int i = 1; i <= k; i++) {
        if (freq[i] >= maxi - 1) ans++;
    }

    cout << ans << "\n";
}
