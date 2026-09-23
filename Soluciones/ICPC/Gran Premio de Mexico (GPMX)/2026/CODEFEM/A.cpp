// ICPC CODEFEM 2026 - A "Ladies Brunch"
// https://codeforces.com/gym/106718/problem/A

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

struct LazySegtree {
    vll tree, lazy;
    ll sz;
    LazySegtree(ll n) {
        sz = 1;
        while (sz < n) sz *= 2;
        tree.assign(2 * sz, 0);
        lazy.assign(2 * sz, 0);
    }

    void apply(ll delta, ll x, ll lx, ll rx) {
        tree[x] += (rx - lx) * delta;
        lazy[x] += delta;
    }
    void push(ll x, ll lx, ll rx) {
        if (rx - lx == 1 || lazy[x] == 0) return;

        ll m = (lx + rx) / 2;
        apply(lazy[x], 2 * x + 1, lx, m);
        apply(lazy[x], 2 * x + 2, m, rx);
        lazy[x] = 0;
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

    ll n, m;
    cin >> n >> m;

    map<string, ll> ID;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        ID[s] = i;
    }
    
    map<string, ll> cost;
    for (int i = 0; i < m; i++) {
        string s; ll p;
        cin >> s >> p;
        cost[s] = p;
    }

    ll q;
    LazySegtree st(n);
    cin >> q;
    for (int i = 0; i < q; i++) {
        ll op;
        cin >> op;

        if (op == 1) {
            string s1, s2;
            cin >> s1 >> s2;

            ll id = ID[s1], cnt = cost[s2];
            st.update(id, id + 1, cnt);
        } else if (op == 2) {
            ll l, r; string s;
            cin >> l >> r >> s;

            ll cnt = cost[s];
            if (l <= r) st.update(l, r + 1, cnt);
            else {
                st.update(l, n, cnt);
                st.update(0, r + 1, cnt);
            }
        } else {
            string s;
            cin >> s;
            
            ll id = ID[s];
            cout << st.query(id, id + 1) << "\n";
        }
    }
}
