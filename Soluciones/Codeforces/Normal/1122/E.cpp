// Codeforces Round 1122 (Div. 3) - E "Prime Destruction"
// https://codeforces.com/contest/2266/problem/E

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 2e5 + 5;
const ll INF = 1e18;

vll fst_prime(MAX_N, -1);

void setup() {
    for (int i = 2; i < MAX_N; i++) {
        if (fst_prime[i] != -1) continue;
        for (int j = i; j < MAX_N; j += i) {
            fst_prime[j] = i; 
        }
    }
}

void solve() {
    ll n, k;
    cin >> n >> k;
    vll A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    vll dp(n + 1, INF);
    for (int i = 1; i <= n; i++) {
        if (i <= k) {
            dp[i] = 0;
            continue;
        }

        ll val = i;
        while (val != 1) {
            ll p = fst_prime[val];
            dp[i] = min(dp[i], 1 + p * dp[i/p]);

            while (fst_prime[val] == p) val /= p;
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) ans += dp[A[i]];

    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    setup();

    ll tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}
