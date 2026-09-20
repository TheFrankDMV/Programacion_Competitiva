// AtCoder ABC 476 - B "Wild Card"
// https://atcoder.jp/contests/abc476/tasks/abc476_b

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n; string s, t;
    cin >> n >> s >> t;

    bool ans = true;
    for (int i = 0; i < n; i++) {
        if (t[i] != '*' && s[i] != t[i]) ans = false;
    }

    cout << (ans ? "Yes": "No") << "\n";
}
