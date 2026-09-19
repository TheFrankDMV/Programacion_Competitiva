// ICPC GPMX 2026 Repechaje - C "Costly Roads"
// https://codeforces.com/gym/106710/problem/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 2e5 + 5;

struct Edge {
    ll v, a, b;
};

vector<Edge> g[MAX_N]; 
vll sz(MAX_N, 0), res(MAX_N, 0);
ll n, ans = 0;

void dfs_init(ll u, ll p) {
    sz[u] = 1;
    for (auto [v, a, b] : g[u]) {
        if (v == p) continue;
        dfs_init(v, u);
        sz[u] += sz[v];
        ans += sz[v] * a;
    }
}

void dfs_ans(ll u, ll p) {
    res[u] = ans;
    for (auto [v, a, b] : g[u]) {
        if (v == p) continue;
        ans += ((n - sz[v]) * b) - (sz[v] * a);
        dfs_ans(v, u);
        ans -= ((n - sz[v]) * b) - (sz[v] * a);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        ll u, v, a, b;
        cin >> u >> v >> a >> b;
        g[u].push_back({v, a, b});
        g[v].push_back({u, b, a});
    }

    dfs_init(1, 0);
    dfs_ans(1, 0);

    for (int i = 1; i <= n; i++) cout << res[i] << " ";
    cout << "\n";
}
