// AtCoder ABC 471 - A "Nine or Nein"
// https://atcoder.jp/contests/abc471/tasks/abc471_a

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll a, b;
    cin >> a >> b;
    if (a + b == 9 || a - b == 9 || a * b == 9 || a == b * 9) {
        cout << "Nine\n";
    } else cout << "Nein\n";
}
