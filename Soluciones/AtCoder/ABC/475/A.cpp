// AtCoder ABC 475 - A "mnclr"
// https://atcoder.jp/contests/abc475/tasks/abc475_a

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    string s;
    cin >> s;

    for (int i = 0; i < ll(s.size()); i++) {
        cout << s[i];
        if (i + 1 != ll(s.size())) cout << "o";
    }
    cout << "\n";
}
