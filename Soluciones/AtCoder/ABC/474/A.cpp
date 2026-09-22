// AtCoder ABC 474 - A "Not X"
// https://atcoder.jp/contests/abc474/tasks/abc474_a

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll x;
    cin >> x;

    cout << (x == 1 ? 2 : 1) << "\n";
}
