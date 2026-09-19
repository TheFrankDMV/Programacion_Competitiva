// ICPC GPMX 2026 Repechaje - F "Following the Mentor"
// https://codeforces.com/gym/106710/problem/F

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 1e5 + 5;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Treap {
    ll sz, val, sumVal, lazyVal, szNodes, w;
    ll depth, sumDepth, lazyDepth;
    bool isLeft;
    Treap *l, *r, *p;

    Treap(ll v, ll d, bool left) {
        sz = 1;
        val = sumVal = (left ? v : 0);
        depth = sumDepth = (left ? d : 0);
        szNodes = (left ? 1 : 0);
        isLeft = left;
        lazyVal = lazyDepth = 0;
        w = rng();
        l = r = p = nullptr;
    }
};

ll get_sz(Treap *t) {
    return (t ? t->sz : 0);
}
ll get_sz_nodes(Treap *t) {
    return (t ? t->szNodes : 0);
}
ll get_sum_val(Treap *t) {
    return (t ? t->sumVal : 0);
}
ll get_sum_depth(Treap *t) {
    return (t ? t->sumDepth : 0);
}

void apply_val(Treap *t, ll delta) {
    if (!t) return;

    t->lazyVal += delta;
    if (t->isLeft) t->val += delta;
    t->sumVal += delta * t->szNodes;
}
void apply_depth(Treap *t, ll delta) {
    if (!t) return;

    t->lazyDepth += delta;
    if (t->isLeft) t->depth += delta;
    t->sumDepth += delta * t->szNodes;
}
void push(Treap *t) {
    if (!t) return;

    if (t->lazyVal) {
        apply_val(t->l, t->lazyVal);
        apply_val(t->r, t->lazyVal);
        t->lazyVal = 0;
    }

    if (t->lazyDepth) {
        apply_depth(t->l, t->lazyDepth);
        apply_depth(t->r, t->lazyDepth);
        t->lazyDepth = 0;
    }
}
void update(Treap *t) {
    if (!t) return;

    t->sz = get_sz(t->l) + get_sz(t->r) + 1;
    t->szNodes = get_sz_nodes(t->l) + get_sz_nodes(t->r) + (t->isLeft ? 1 : 0);
    t->sumVal = get_sum_val(t->l) + get_sum_val(t->r) + (t->isLeft ? t->val : 0);
    t->sumDepth = get_sum_depth(t->l) + get_sum_depth(t->r) + (t->isLeft ? t->depth : 0);

    if (t->l) t->l->p = t;
    if (t->r) t->r->p = t;
}

pair<Treap*, Treap*> split(Treap *t, ll k) {
    if (!t) return {nullptr, nullptr};

    push(t);
    if (get_sz(t->l) >=k) {
        auto b = split(t->l, k);
        t->l = b.second;
        update(t);

        if (b.first) b.first->p = nullptr;
        if (t) t->p = nullptr;

        return {b.first, t};
    } else {
        auto b = split(t->r, k - get_sz(t->l) - 1);
        t->r = b.first;
        update(t);

        if (t) t->p = nullptr;
        if (b.second) b.second->p = nullptr;

        return {t, b.second};
    }
}

Treap* merge(Treap *a, Treap *b) {
    if (!a || !b) return (a ? a : b);
   
    push(a);
    push(b);
    if (a->w > b->w) {
        a->r = merge(a->r, b);
        update(a);

        a->p = nullptr;

        return a;
    } else {
        b->l = merge(a, b->l);
        update(b);

        b->p = nullptr;

        return b;
    }
}

ll get_rank(Treap *t) {
    ll ret = get_sz(t->l) +1;
    while (t->p) {
        if (t == t->p->r) {
            ret += get_sz(t->p->l) + 1;
        }
        t = t->p;
    }
    return ret;
}
ll get_actual_depth(Treap *t) {
    vector<Treap*> path;
    Treap *cur = t;
    while (cur) {
        path.push_back(cur);
        cur = cur->p;
    }

    for (int i = ll(path.size() - 1); i >= 0; i--) {
        push(path[i]);
    }

    return t->depth;
}

vector<Treap*> nodes (2 * MAX_N + 1, nullptr), seq;
vll g[MAX_N], A(MAX_N);
ll n;

void dfs(ll u, ll depth) {
    nodes[u] = new Treap(A[u], depth, true);
    seq.push_back(nodes[u]);

    for (auto v : g[u]) dfs(v, depth + 1);

    nodes[u + n] = new Treap(0, 0, false);
    seq.push_back(nodes[u + n]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 2; i <= n; i++) {
        ll p;
        cin >> p;
        g[p].push_back(i);
    }

    dfs(1, 0);
    Treap* root = nullptr;
    for (auto x : seq) root = merge(root, x);

    for (int i = 0; i < q; i++) {
        ll op;
        cin >> op;

        if (op == 1) {
            ll u, v;
            cin >> u >> v;
            if (v == u) continue;

            ll ru1 = get_rank(nodes[u]), ru2 = get_rank(nodes[u + n]);
            ll rv1 = get_rank(nodes[v]);
            if (ru1 <= rv1 && rv1 <= ru2) continue;

            ll depthU = get_actual_depth(nodes[u]), depthV = get_actual_depth(nodes[v]);
            ll delta = depthV + 1 - depthU;
            auto [T1, temp] = split(root, ru1 - 1);
            auto [T2, T3] = split(temp, ru2 - ru1 + 1);

            apply_depth(T2, delta);
            root = merge(T1, T3);

            ll rv2 = get_rank(nodes[v + n]);
            auto [Tleft, Tright] = split(root, rv2 - 1);
            root = merge(merge(Tleft, T2), Tright);
        } else if (op == 2) {
            ll u, x;
            cin >> u >> x;

            ll ru1 = get_rank(nodes[u]), ru2 = get_rank(nodes[u + n]);
            auto [T1, temp] = split(root, ru1 - 1);
            auto [T2, T3] = split(temp, ru2 - ru1 + 1);

            apply_val(T2, x);
            root = merge(merge(T1, T2), T3);
        } else if (op == 3) {
            ll u;
            cin >> u;

            ll ru1 = get_rank(nodes[u]), ru2 = get_rank(nodes[u + n]);
            auto [T1, temp] = split(root, ru1 - 1);
            auto [T2, T3] = split(temp, ru2 - ru1 + 1);

            cout << T2->sumVal << "\n";
            root = merge(merge(T1, T2), T3);
        } else {
            ll u;
            cin >> u;

            ll depthU = get_actual_depth(nodes[u]);
            ll ru1 = get_rank(nodes[u]), ru2 = get_rank(nodes[u + n]);
            auto [T1, temp] = split(root, ru1 - 1);
            auto [T2, T3] = split(temp, ru2 - ru1 + 1);

            ll ans = T2->sumDepth - T2->szNodes * depthU;
            cout << ans << "\n";
            root = merge(merge(T1, T2), T3);
        }
    }
}
