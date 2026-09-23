// AtCoder ABC 471 - E "Sum of Square of Sum"
// https://atcoder.jp/contests/abc471/tasks/abc471_e

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 2e5 + 5;
const ll MOD = 998244353;

ll binpow(ll a, ll b) {
    ll ret = 1;
    while (b > 0) {
        if (b & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        b /= 2;
    }
    return ret;
}
ll inv(ll a) {
    return binpow(a, MOD - 2);
}

vll fact(MAX_N), inv_fact(MAX_N);

void setup() {
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    inv_fact[MAX_N - 1] = inv(fact[MAX_N - 1]);
    for (int i = MAX_N - 2; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
    }
}
ll binom(ll a, ll b) {
    if (a < b || b < 0) return 0;
    return ((fact[a] * inv_fact[b]) % MOD * inv_fact[a - b]) % MOD; 
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    setup();

    ll n, k;
    cin >> n >> k;
    vll A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + (binom(n - 1, k - 1) * A[i]) % MOD * A[i]) % MOD;
    }

    if (k >= 2) {
        ll sum = accumulate(A.begin(), A.end(), 0ll) % MOD;
        for (int i = 0; i < n; i++) {
            ans = (ans + (binom(n - 2, k - 2) * A[i]) % MOD * (sum - A[i] + MOD)) % MOD;
        }
    }

    cout << ans << "\n";
}
