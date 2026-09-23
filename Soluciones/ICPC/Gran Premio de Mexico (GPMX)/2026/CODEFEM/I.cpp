// ICPC CODEFEM 2026 - I "Fruit Punch"
// https://codeforces.com/gym/106718/problem/I

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 1e5 + 5;
const ll MOD = 122333221;

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

void solve() {
    ll n, k;
    cin >> n >> k;

    cout << binom(n, k) << "\n";
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
