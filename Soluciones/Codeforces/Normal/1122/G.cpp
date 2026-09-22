// Codeforces Round 1122 (Div. 3) - G "Modular Tree"
// https://codeforces.com/contest/2266/problem/G

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 2e5 + 5;

vll g[MAX_N];
vll A(MAX_N), B(MAX_N), val(MAX_N);
ll ans = 0;

void dfs(ll u, ll p) {
    val[u] = B[u];
    ll sum = 0;

    for (auto v : g[u]) {
        if (v == p) continue;
        
        dfs(v, u);
        sum += A[v];
        if (val[v] != B[v]) {
            val[u] = __gcd(val[u], val[v]);
        }
    }

    val[u] = __gcd(val[u], sum);
    ans += A[u] + ((B[u] - A[u] - 1) / val[u]) * val[u];
}

void solve() {
    ll n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= n; i++) cin >> B[i];

    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ans = 0;
    dfs(1, 0);

    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}
