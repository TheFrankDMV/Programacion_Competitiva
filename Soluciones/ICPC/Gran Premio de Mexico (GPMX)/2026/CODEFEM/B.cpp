// ICPC CODEFEM 2026 - B "Emily's Agenda"
// https://codeforces.com/gym/106718/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;
using vpll = vector<pll>;

pll get_hour(string s) {
    return {stoll(s.substr(0, 2)), stoll(s.substr(3, 2))};
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;

    vpll events[24][60];
    vector<vector<bool>> has_future(24, vector<bool>(60, false));
    for (int i = 0; i < n; i++) {
        string s, e;
        cin >> s >> e;

        auto [ax, ay] = get_hour(s);
        auto [bx, by] = get_hour(e);

        if (pll{ax, ay} < pll{bx, by}) {
            events[bx][by].push_back({ax, ay});
        } else has_future[ax][ay] = true;
    }

    ll ans = 0, pst = 0;
    vector<vll> dp(24, vll(60, 0));
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 60; j++) {
            dp[i][j] = pst;

            for (auto [ax, ay] : events[i][j]) {
                dp[i][j] = max(dp[i][j], dp[ax][ay] + 1);
            }
            
            pst = dp[i][j];
            if (has_future[i][j]) ans = max(ans, dp[i][j] + 1);
        }
    }

    ans = max(ans, dp[23][59]);
    cout << ans << "\n";
}
