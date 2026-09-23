// ICPC CODEFEM 2026 - J "8M"
// https://codeforces.com/gym/106718/problem/J

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 2e5 + 5;

struct SCC {
    ll n, cnt_comps;
    vector<vll> g, rev_g, scc_nodes, dag;
    vll order, scc_ID;
    vector<bool> vis;
    SCC(ll n): n(n), cnt_comps(0), g(n), rev_g(n), scc_ID(n, -1), vis(n, false) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        rev_g[v].push_back(u);
    }

    void dfs_order(ll u) {
        vis[u] = true;
        for (auto v: g[u]) {
            if (!vis[v]) dfs_order(v);
        }
        order.push_back(u);
    }
    void dfs_scc(ll u, ll comp) {
        vis[u] = true;
        scc_ID[u] = comp;
        scc_nodes.back().push_back(u);
        for (auto v : rev_g[u]) {
            if (!vis[v]) dfs_scc(v, comp);
        }
    }

    void build() {
        for (int i = 0; i < n; i++) {
            if (!vis[i]) dfs_order(i);
        }
        reverse(order.begin(), order.end());
        fill(vis.begin(), vis.end(), false);
        for (auto u : order) {
            if (!vis[u]) {
                scc_nodes.push_back({});
                dfs_scc(u, cnt_comps);
                cnt_comps++;
            }
        }
        dag.resize(cnt_comps);
        for (int u = 0; u < n; u++) {
            for (auto v : g[u]) {
                if (scc_ID[u] != scc_ID[v]) {
                    dag[scc_ID[u]].push_back(scc_ID[v]);
                }
            }
        }
        for (int i = 0; i < cnt_comps; i++) {
            sort(dag[i].begin(), dag[i].end());
            dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, m;
    cin >> n >> m;

    SCC scc(n);
    for (int i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--; b--;

        scc.add_edge(a, b);
    }

    scc.build();
    if (scc.cnt_comps == 1) {
        cout << "0\n";
        return 0;
    }

    vll inDeg(scc.cnt_comps, 0), outDeg(scc.cnt_comps, 0);
    for (int u = 0; u < scc.cnt_comps; u++) {
        for (auto v : scc.dag[u]) {
            inDeg[v]++;
            outDeg[u]++;
        }
    }

    ll cntIn = 0, cntOut = 0;
    for (int i = 0; i < scc.cnt_comps; i++) {
        if (inDeg[i] == 0) cntIn++;
        if (outDeg[i] == 0) cntOut++;
    }

    cout << max(cntIn, cntOut) << "\n";
}
