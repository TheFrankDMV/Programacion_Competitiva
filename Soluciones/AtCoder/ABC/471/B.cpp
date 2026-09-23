// AtCoder ABC 471 - B "Survey Tabulation"
// https://atcoder.jp/contests/abc471/tasks/abc471_b

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;

    ll ans = 0;
    map<string, ll> freq;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        for (auto &c : s) c = tolower(c);
        freq[s]++;

        ans = max(ans, freq[s]);
    }

    cout << ans << "\n";
}
