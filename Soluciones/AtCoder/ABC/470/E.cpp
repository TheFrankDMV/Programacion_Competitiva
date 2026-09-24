// AtCoder ABC 470 - E "Concentration"
// https://atcoder.jp/contests/abc470/tasks/abc470_e

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, l;
    cin >> n >> l;
    vll A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    ld dp[l + 1][n + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    dp[l][0][0] = 1;
    ld ans = 0;
    for (int life = l; life >= 1; life--) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == n) {
                    ans += dp[life][i][j] * j;
                    continue;
                }

                ld tot = 2 * n - i - j;
                ld diff = i - j;

                dp[life][i][j + 1] += (diff / tot) * dp[life][i][j];

                if (tot > diff) {
                    ld prob = (tot - diff) /  (tot * (tot - 1));
                    dp[life][i + 1][j + 1] += prob * dp[life][i][j];
                }

                if (tot > diff) {
                    ld prob1 = ((tot - diff) * diff) / (tot * (tot - 1));
                    ld prob2 = ((tot - diff) * (tot - diff - 2)) / (tot * (tot - 1));

                    if (life == 1) ans += (prob1 + prob2) * dp[life][i][j] * j;
                    else {
                        dp[life - 1][i + 1][j + 1] += prob1 * dp[life][i][j];
                        dp[life - 1][i + 2][j] += prob2 * dp[life][i][j];
                    }
                }
            }
        }
    } 

    ld sum = accumulate(A.begin(), A.end(), ld(0));
    cout << fixed << setprecision(10) << ans * sum / ld(n) << "\n";
}
