// AtCoder ABC 470 - A "Fizz"
// https://atcoder.jp/contests/abc470/tasks/abc470_a

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0) cout << "Fizz\n";
        else cout << i << "\n";
    }
}
