// AtCoder ABC 470 - B "Monocolor"
// https://atcoder.jp/contests/abc470/tasks/abc470_b

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vll freq(n + 1);
    for (int i = 0; i < n; i++) {
        ll c;
        cin >> c;
        freq[c]++;
    }

    ll maxi = *max_element(freq.begin(), freq.end());
    cout << n - maxi << "\n";
}
