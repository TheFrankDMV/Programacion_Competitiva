// AtCoder ABC 473 - F "A/AB Insertion"
// https://atcoder.jp/contests/abc473/tasks/abc473_f

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

struct Node {
    ll sum, mn_psum;

    Node(ll val) {
        sum = val;
        mn_psum = min(0ll, val);
    }
};

Node add(Node a, Node b) {
    Node ret(0);

    ret.sum = a.sum + b.sum;
    ret.mn_psum = min(a.mn_psum, a.sum + b.mn_psum);

    return ret;
}

struct Segtree {
    vector<Node> tree;
    ll sz;
    Segtree(ll n) {
        sz = 1;
        while (sz < n) sz *= 2;
        tree.assign(2 * sz, Node(0));
    }

    void update(ll pos, ll delta, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            tree[x] = Node(delta);
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
        if (rx <= l || r <= lx) return Node(0);
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

    ll n; string s;
    cin >> n >> s;

    Segtree st(n);
    for (int i = 0; i < n; i++) {
        st.update(i, (s[i] == 'A' ? 1 : -1));
    }

    ll q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        ll op;
        cin >> op;

        if (op == 1) {
            ll id; char c;
            cin >> id >> c;
            id--;

            st.update(id, (c == 'A' ? 1 : -1));
        } else {
            ll l, r;
            cin >> l >> r;
            l--; r--;

            Node ans = st.query(l, r + 1);
            cout << (ans.mn_psum >= 0 ? "Yes" : "No") << "\n";
        }
    }
}
