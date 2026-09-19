// ICPC GPMX 2026 Repechaje - K "Kaleidoscopic Talavera"
// https://codeforces.com/gym/106710/problem/K

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

struct Node {
    ll cntComplete, rangeLen, exactLen, usedLen, cntRanges;
    bool left, right;

    Node() {
        cntComplete = rangeLen = exactLen = usedLen = cntRanges = 0;
        left = right = false;
    }

    void calc_leaf() {
        if (cntComplete != 0) {
            cntRanges = 1;
            usedLen = rangeLen;
            left = right = true;
        } else {
            cntRanges = usedLen = 0;
            left = right = false;
        }

        exactLen = (cntComplete == 1 ? rangeLen : 0);
    }
    void calc(Node l, Node r) {
        if (cntComplete >= 2) {
            exactLen = 0;
            usedLen = rangeLen;
            cntRanges = 1;
            left = right = true;
        } else if (cntComplete == 1) {
            exactLen = rangeLen - l.usedLen - r.usedLen;
            usedLen = rangeLen;
            cntRanges = 1;
            left = right =true;
        } else {
            exactLen = l.exactLen + r.exactLen;
            usedLen = l.usedLen + r.usedLen;
            cntRanges = l.cntRanges + r.cntRanges - (l.right && r.left);
            left = l.left;
            right = r.right;
        }
    }
};

struct Segtree {
    vector<Node> tree;
    ll sz;
    Segtree(ll n, vll &A) {
        sz = 1;
        while (sz < n) sz *= 2;
        tree.assign(2 * sz, Node());
        build(0, 0, sz, A);
    }
    
    void build(ll x, ll lx, ll rx, vll &A) {
        if (rx - lx == 1) {
            if (lx + 1 < ll(A.size())) {
                tree[x].rangeLen = A[lx + 1] - A[lx];
            }
            return;
        }

        ll m = (lx + rx) / 2;
        build(2 * x + 1, lx, m, A); 
        build(2 * x + 2, m, rx, A);
        tree[x].rangeLen = tree[2 * x + 1].rangeLen + tree[2 * x + 2].rangeLen;
    }

    void update(ll l, ll r, bool add, ll x, ll lx, ll rx) {
        if (r <= lx || rx <= l) return;
        if (l <= lx && rx <= r) {
            tree[x].cntComplete += (add ? 1 : -1);

            if (rx - lx == 1) tree[x].calc_leaf();
            else tree[x].calc(tree[2 * x + 1], tree[2 * x + 2]);

            return;
        }

        ll m = (lx + rx) / 2;
        update(l, r, add, 2 * x + 1, lx, m);
        update(l, r, add, 2 * x + 2, m, rx);
        tree[x].calc(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void update(ll l, ll r, bool add) {
        update(l, r, add, 0, 0, sz);
    }
};

struct Rect {
    ll x1, y1, x2, y2;

    void rect_swap() {
        swap(x1, y1);
        swap(x2, y2);
    }
};

struct Event {
    ll time, l, r;
    bool add;
};

pair<ll, ll> solve(ll n, vector<Rect> A) {
    vector<Event> events;
    vll v;
    for (int i = 0; i < n; i++) {
        v.push_back(A[i].x1);
        v.push_back(A[i].x2);

        events.push_back({A[i].y1, A[i].x1, A[i].x2, true});
        events.push_back({A[i].y2, A[i].x1, A[i].x2, false});
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    auto compress = [&](ll val) {
        return lower_bound(v.begin(), v.end(), val) - v.begin();
    };

    sort(events.begin(), events.end(), [&](auto a, auto b) {
        return a.time < b.time;
    });
    for (auto &[time, l, r, add] : events) {
        l = compress(l);
        r = compress(r);
    }
    
    ll area = 0, perimeter = 0;
    Segtree st(ll(v.size()), v);
    for (int i = 0; i < 2 * n; i++) {
        st.update(events[i].l, events[i].r, events[i].add);

        if (i + 1 != 2 * n && events[i].time != events[i + 1].time) {
            ll tot = (events[i + 1].time - events[i].time);
            area += tot * st.tree[0].exactLen;
            perimeter += tot * 2 * st.tree[0].cntRanges;
        }
    }

    return {area, perimeter};
} 

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vector<Rect> A(n);
    for (int i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        A[i] = {x1, y1, x2, y2};
    }

    auto [areaX, perimeterX] = solve(n, A);
    for (int i = 0; i < n; i++) A[i].rect_swap();
    auto [areaY, perimeterY] = solve(n, A);

    cout << areaX << " " << (perimeterX + perimeterY) << "\n";
}
