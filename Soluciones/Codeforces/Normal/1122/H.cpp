// Codeforces Round 1122 (Div. 3) - H "Deque Malfunction"
// https://codeforces.com/contest/2266/problem/H

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;
using vpll = vector<pll>;

const ll INF = 1e18;

struct LazySegtree {
    vll tree;
    vector<bool> lazy;
    ll sz;
    LazySegtree(ll n) {
        sz = 1;
        while (sz < n) sz *= 2;
        tree.assign(2 * sz, -INF);
        lazy.assign(2 * sz, false);
    }

    void apply(ll x) {
        tree[x] = -INF;
        lazy[x] = true;
    }
    void push(ll x, ll lx, ll rx) {
        if (!lazy[x] || rx - lx == 1) return;
        apply(2 * x + 1);
        apply(2 * x + 2);
        lazy[x] = false;
    }
    
    void update_range(ll l, ll r, ll x, ll lx, ll rx) {
        if (rx <= l || r <= lx) return;
        if (l <= lx && rx <= r) {
            apply(x);
            return;
        }
        
        push(x, lx, rx);
        
        ll m = (lx + rx) / 2;
        update_range(l, r, 2 * x + 1, lx, m);
        update_range(l, r, 2 * x + 2, m, rx);
        
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void update_range(ll l, ll r) {
        update_range(l, r, 0, 0, sz);
    }

    void update_point(ll pos, ll delta, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            tree[x] = max(tree[x], delta);
            return;
        }

        push(x, lx, rx);

        ll m = (lx + rx) / 2;
        if (pos < m) update_point(pos, delta, 2 * x + 1, lx, m);
        else update_point(pos, delta, 2 * x + 2, m, rx);
        
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void update_point(ll pos, ll delta) {
        update_point(pos, delta, 0, 0, sz);
    }

    ll query(ll l, ll r, ll x, ll lx, ll rx) {
        if (rx <= l || r <= lx) return -INF;
        if (l <= lx && rx <= r) return tree[x];

        push(x, lx, rx);

        ll m = (lx + rx) / 2;
        return max(query(l, r, 2 * x + 1, lx, m), query(l, r, 2 * x + 2, m, rx));
    }
    ll query(ll l, ll r) {
        return query(l, r, 0, 0, sz);
    } 
};

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vll> pos(n + 1);
    for (int i = 0; i < m; i++) {
        ll b;
        cin >> b;
        pos[b].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        if (pos[i].empty()) {
            cout << "-1\n";
            return;
        }
    }

    LazySegtree dpL(m);
    for (int i = 1; i <= n; i++) {
        vpll ndp;
        for (auto t : pos[i]) {
            if (i == 1) ndp.push_back({t, 1});
            else {
                ll maxi = dpL.query(t + 1, m);
                if (maxi != -INF) ndp.push_back({t, maxi + 1});
            }
        }
    
        ll lstPos = pos[i].back();
        if (lstPos + 1 < m) {
            dpL.update_range(lstPos + 1, m);
        }

        for (auto [a, b] : ndp) {
            dpL.update_point(a, b);
        }
    }

    vll L(m, -INF);
    for (int i = 0; i < m; i++) {
        L[i] = dpL.query(i, i + 1);
    }

    LazySegtree dpR(m);
    for (int i = n; i >= 1; i--) {
        vpll ndp;
        for (auto t : pos[i]) {
            if (i == n) ndp.push_back({t, 1});
            else {
                ll maxi = dpR.query(t + 1, m);
                if (maxi != -INF) ndp.push_back({t, maxi + 1});
            }
        }
    
        ll lstPos = pos[i].back();
        if (lstPos + 1 < m) {
            dpR.update_range(lstPos + 1, m);
        }

        for (auto [a, b] : ndp) {
            dpR.update_point(a, b);
        }
    }

    vll R(m, -INF);
    for (int i = 0; i < m; i++) {
        R[i] = dpR.query(i, i + 1);
    }

    ll ans = INF;
    for (int i = 0; i < m; i++){
        if (L[i] != -INF && R[i] != -INF) {
            ans = min(ans, n - (L[i] + R[i] - 1));
        }
    }
    
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
