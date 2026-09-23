// AtCoder ABC 472 - E "Odd Cycle"
// https://atcoder.jp/contests/abc472/tasks/abc472_e

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 2e5 + 5;

vll g[MAX_N];
vll depth(MAX_N, 0), anc(MAX_N), ans;

bool dfs(ll u, ll p) {
    depth[u] = depth[p] + 1;
    anc[u] = p;

    for (auto v : g[u]) {
        if (depth[v] == 0) {
            if (dfs(v, u)) return true;
        } else if ((depth[u] - depth[v]) % 2 == 0) {
            ll cur = u;

            while (cur != v) {
                ans.push_back(cur);
                cur = anc[cur];
            }
            ans.push_back(v);
            
            return true;
        }
    }

    return false;
}

void solve() {    
    ll n, m;
    cin >> n >> m;

    ans.clear();
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        depth[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    if (!dfs(1, 0)) {
        cout << "-1\n";
        return;
    }

    cout << ans.size() << "\n";
    for (auto u : ans) cout << u << " ";
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll tt;
    cin >> tt;
    while(tt--) {
        solve();
    }
}
