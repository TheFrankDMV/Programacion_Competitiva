// ICPC GPMX 2026 Repechaje - E "Expected Snaps"
// https://codeforces.com/gym/106710/problem/E

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MOD = 998244353;

ll binpow(ll a, ll b, ll mod = MOD) {
    ll ret = 1;
    while (b) {
        if (b & 1) ret = (ret * a) % mod;
        a = (a * a) % mod;
        b /= 2;
    }
    return ret;
}
ll inv(ll a) {
    return binpow(a, MOD - 2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, k;
    cin >> n >> k;
    vll inverse(k);
    for (int i = 1; i < k; i++) inverse[i] = inv(i);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll len = binpow(2, i), prob = 1;
        for (int j = 1; j < k; j++) {
            prob = (prob * (len + j)) % MOD;
            prob = (prob * inverse[j]) % MOD;
        }

        ll exp = binpow(2, i, MOD - 1);
        prob = (prob * inv(binpow(k, exp))) % MOD;
        
        ans = (ans + (1 - prob) + MOD) % MOD;
    }

    cout << ans << "\n";
}
