// ICPC GPMX 2026 Repechaje - I "Inner Product II"
// https://codeforces.com/gym/106710/problem/I

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 2e5 + 5;

vll g[MAX_N], uf(MAX_N, -1), inDeg(MAX_N, 0);

ll ufind(ll u) {
    if (uf[u] < 0) return u;
    return uf[u] = ufind(uf[u]);
}
void unite(ll u, ll v) {
    u = ufind(u);
    v = ufind(v);
    if (uf[u] > uf[v]) swap(u, v);
    
    for (auto x : g[v]) g[u].push_back(x);
    uf[u] += uf[v]; 
    inDeg[u] += inDeg[v];
    uf[v] = u;
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vll A(n + 1);
    for (int i = 1; i <= n; i++) cin >> A[i];

    for (int i = 0; i < n - 1; i++) {
        ll u, v; char c;
        cin >> u >> v >> c;
        u = ufind(u);
        v = ufind(v);
        
        if (c == '=') unite(u, v);
        else if (c == '<') {
            g[u].push_back(v);
            inDeg[v]++;
        } else {
            g[v].push_back(u);
            inDeg[u]++;
        }
    }

    set<pair<ll, ll>> pq;
    for (int i = 1; i <= n; i++) {
        if (i == ufind(i) && inDeg[i] == 0) {
            pq.insert({inDeg[i], i});
        } 
    }
    
    vll ans(n + 1, 1);
    while (!pq.empty()) {
        auto [deg, u] = *pq.begin();
        pq.erase(pq.begin());
        
        for (auto v : g[u]) {
            v = ufind(v);

            pq.erase({inDeg[v], v});
            inDeg[v]--;
            ans[v] =  max(ans[v], ans[u] + 1);
            pq.insert({inDeg[v], v});
        }
    }
    
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        ans[i] = ans[ufind(i)];
        res += A[i] * ans[i];
    }

    cout << res << "\n";
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
}
