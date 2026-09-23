// ICPC CODEFEM 2026 - C "Gym Sis"
// https://codeforces.com/gym/106718/problem/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll INF = 1e18;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, z;
    cin >> n >> z;
    vll K(n), D(n), X(n);
    for (int i = 0; i < n; i++) {
        cin >> K[i] >> D[i] >> X[i];
    }

    vector<vll> dp(n);
    for (int i = 0; i < n; i++) dp[i].assign(D[i] + 1, 0);

    for (int i = 1; i <= z; i++) {
        vector<vll> new_dp(n);
        for (int j = 0; j < n; j++) new_dp[j].assign(D[j] + 1, -INF);

        vll maxi(n, -INF);
        for (int j = 0; j < n; j++) {
            for (int k = 0; k <= D[j]; k++) {
                ll &val = new_dp[j][min(D[j], ll(k + 1))];
                ll aura = K[j] + (k == D[j] ? -X[j] : 0);

                maxi[j] = max(maxi[j], dp[j][k]);
                val = max(val, dp[j][k] + aura);
            }
        }

        vll pref(n, -INF), suff(n, -INF);
        pref[0] = maxi[0];
        for (int j = 1; j < n; j++) {
            pref[j] = max(pref[j - 1], maxi[j]);
        }
        suff[n - 1] = maxi[n - 1];
        for (int j = n - 2; j >= 0; j--) {
            suff[j] = max(suff[j + 1], maxi[j]);
        }

        for (int j = 0; j < n; j++) {
            ll l = (j == 0 ? -INF : pref[j - 1]);
            ll r = (j == n - 1 ? -INF : suff[j + 1]);

            new_dp[j][1] = max(new_dp[j][1], max(l, r) + K[j]);
            new_dp[j][0] = max(new_dp[j][0], max({l, r, maxi[j]}));
        }

        swap(dp, new_dp);
    }

    ll ans = -INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= D[i]; j++) {
            ans = max(ans, dp[i][j]);
        }
    }

    cout << ans << "\n";
}
