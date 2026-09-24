// AtCoder ABC 470 - G "ΣШX"
// https://atcoder.jp/contests/abc470/tasks/abc470_g

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll INF = 1e18;

struct LazySegtree {
    vll tree, lazy;
    ll sz;
    LazySegtree(ll n) {
        sz = 1;
        while (sz < n) sz *= 2;
        tree.assign(2 * sz, 0);
        lazy.assign(2 * sz, INF);
    }

    void apply(ll delta, ll x, ll lx, ll rx) {
        tree[x] = delta * (rx - lx);
        lazy[x] = delta;
    } 
    void push(ll x, ll lx, ll rx) {
        if (lazy[x] == INF || rx - lx == 1) return;

        ll m = (lx + rx) / 2;
        apply(lazy[x], 2 * x + 1, lx, m);
        apply(lazy[x], 2 * x + 2, m, rx);
        lazy[x] = INF;
    }

    void update(ll l, ll r, ll delta, ll x, ll lx, ll rx) {
        if (rx <= l || r <= lx) return;
        if (l <= lx && rx <= r) {
            apply(delta, x, lx, rx);
            return;
        }

        push(x, lx, rx);

        ll m = (lx + rx) / 2;
        update(l, r, delta, 2 * x + 1, lx, m);
        update(l, r, delta, 2 * x + 2, m, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void update(ll l, ll r, ll delta) {
        update(l, r, delta, 0, 0, sz);
    }

    ll query(ll l, ll r, ll x, ll lx, ll rx) {
        if (rx <= l || r <= lx) return 0;
        if (l <= lx && rx <= r) return tree[x];

        push(x, lx, rx);

        ll m = (lx + rx) / 2;
        return query(l, r, 2 * x + 1, lx, m) + query(l, r, 2 * x + 2, m, rx);
    }
    ll query(ll l, ll r) {
        return query(l, r, 0, 0, sz);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;

    vll A(n);
    vector<vll> ids(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        ids[A[i]].push_back(i);
    }

    LazySegtree st(n);
    for (int i = 0; i < n; i++) st.update(i, i + 1, i);

    ll ans = 0;
    for (int k = 0; k < n; k++) {
        ids[k].push_back(n);
        ll lst = -1;
        
        for (int i = 0; i < ll(ids[k].size()); i++) {
            ll l = lst + 1, r = ids[k][i];
            ll target = ids[k][i];

            if (l <= min(r, n - 1)) {
                ll lx = l, rx = min(r, n - 1);

                while (lx < rx) {
                    ll m = (lx + rx) / 2;
                    if (st.query(m, m + 1) >= target) rx = m;
                    else lx = m + 1;
                }

                if (st.query(lx, lx + 1) >= target) {
                    st.update(l, lx, target);
                } else st.update(l, rx + 1, target);
            }

            lst = ids[k][i];
        }

        ans += n * n - st.query(0, n);
    }

    cout << ans << "\n";
}
