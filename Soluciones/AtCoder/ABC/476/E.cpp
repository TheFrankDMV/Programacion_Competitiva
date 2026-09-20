// AtCoder ABC 476 - E "Min-Max Swap"
// https://atcoder.jp/contests/abc476/tasks/abc476_e

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;

const ll INF = 1e18;

struct Node {
    ll maxi, mini, posMaxi, posMini;
    Node() {
        maxi = posMaxi = -INF;
        mini = posMini = INF;
    }
};

Node add(Node l, Node r) {
    Node ret;

    tie(ret.maxi, ret.posMaxi) = max(pll{l.maxi, l.posMaxi}, pll{r.maxi, r.posMaxi});
    tie(ret.mini, ret.posMini) = min(pll{l.mini, l.posMini}, pll{r.mini, r.posMini});

    return ret;
}

struct Segtree {
    vector<Node> tree;
    ll sz;
    Segtree(ll n) {
        sz = 1;
        while (sz < n) sz *= 2;
        tree.assign(2 * sz, Node());
    }

    void update(ll pos, ll delta, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            tree[x].maxi = tree[x].mini = delta;
            tree[x].posMaxi = tree[x].posMini = lx;
            return;
        }

        ll m = (lx + rx) / 2;
        if (pos < m) update(pos, delta, 2 * x + 1, lx, m);
        else update(pos, delta, 2 * x + 2, m, rx);

        tree[x] = add(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void update(ll pos, ll delta) {
        update(pos, delta, 0, 0, sz);
    }

    Node query(ll l, ll r, ll x, ll lx, ll rx) {
        if (rx <= l || r <= lx) return Node();
        if (l <= lx && rx <= r) return tree[x];

        ll m = (lx + rx) / 2;
        return add(query(l, r, 2 * x + 1, lx, m), query(l, r, 2 * x + 2, m, rx));
    }
    Node query(ll l, ll r) {
        return query(l, r, 0, 0, sz);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, m;
    cin >> n >> m;
    vll P(n);
    for (int i = 0; i < n; i++) cin >> P[i];

    Segtree st(n);
    for (int i = 0; i < n; i++) st.update(i, P[i]);
    
    for (int i = 0; i < m; i++) {
        ll l, r;
        cin >> l >> r; l--; r--;
        
        Node ret = st.query(l, r + 1);
        swap(P[ret.posMaxi], P[ret.posMini]);

        st.update(ret.posMaxi, P[ret.posMaxi]);
        st.update(ret.posMini, P[ret.posMini]);
    }

    for (int i = 0; i < n; i++) {
        cout << st.query(i, i + 1).maxi << " ";
    }
    cout << "\n";
}
