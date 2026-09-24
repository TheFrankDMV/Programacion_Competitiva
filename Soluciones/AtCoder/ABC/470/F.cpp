// AtCoder ABC 470 - F "Googol Swaps"
// https://atcoder.jp/contests/abc470/tasks/abc470_

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 2e5 + 5;
const ll MOD = 998244353;

ll binpow(ll a, ll b) {
    ll ret = 1;
    a %= MOD;
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

vll g[MAX_N], comp;
vector<bool> vis(MAX_N, false);

void dfs(ll u) {
    vis[u] = true;
    comp.push_back(u);
    for (auto v : g[u]) {
        if (!vis[v]) dfs(v);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    setup();

    ll n, m; string s;
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--; b--;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    ll ans = 1;
    bool flag = false;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;

        comp.clear();
        dfs(i);

        ll k = comp.size();
        ans = (ans * fact[k]) % MOD;

        vll freq(26, 0);
        for (auto id : comp) {
            freq[s[id] - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            ans = (ans * inv_fact[freq[i]]) % MOD;
            if (freq[i] >= 2) flag = true;
        }
    }
    
    if (!flag) ans = (ans * inv(2)) % MOD;
    cout << ans << "\n";
}
