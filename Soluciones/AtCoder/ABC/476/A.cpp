// AtCoder ABC 476 - A "Appender"
// https://atcoder.jp/contests/abc476/tasks/abc476_a

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    string s;
    cin >> s;

    if (s.back() == 'e') s += "r";
    else s += "er";

    cout << s << "\n";
}
