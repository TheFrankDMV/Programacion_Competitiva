// AtCoder ABC 472 - A "A"
// https://atcoder.jp/contests/abc472/tasks/abc472_a

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    string s;
    cin >> s;

    for (auto &c : s) {
        if (c != 'A') c = '.';
    }
    
    cout << s << "\n";
}
