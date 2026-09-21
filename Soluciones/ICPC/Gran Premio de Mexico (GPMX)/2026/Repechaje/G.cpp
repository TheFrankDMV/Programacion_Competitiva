// ICPC GPMX 2026 Repechaje - G "Grand Rainbow Railway"
// https://codeforces.com/gym/106710/problem/G

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 150;

vector<pair<ll, ll>> g[MAX_N];
vll path;

bool dfs(ll u, ll target, ll p) {
    if (u == target) return true;

    for (auto [v, id] : g[u]) {
        if (v == p) continue;
        
        path.push_back(id);
        if (dfs(v, target, u)) return true;
        path.pop_back();
    }

    return false;
}

struct Edge {
    ll u, v, c, id;
};

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        edges[i] = {u, v, c, i};
    }

    vector<bool> inAns(m, false);
    ll sz = 0;
    while (sz < n - 1) {
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 0; i < m; i++) {
            if (!inAns[i]) continue;

            g[edges[i].u].push_back({edges[i].v, i});
            g[edges[i].v].push_back({edges[i].u, i});
        }
    
        vector<vll> cycles(m);
        for (int i = 0; i < m; i++) {
            if (inAns[i]) continue;

            path.clear();
            if (dfs(edges[i].u, edges[i].v, 0)) {
                cycles[i] = path;
            }
        }

        vll anc(m, -1);
        vector<bool> isTarget(m, false), vis(m, false);
        queue<ll> q;
        for (int i = 0; i < m; i++) {
            if (inAns[i]) continue;

            if (cycles[i].empty()) {
                q.push(i);
                vis[i] = true;
            }

            bool flag = false;
            for (int j = 0; j < m; j++) {
                if (inAns[j] && edges[j].c == edges[i].c) {
                    flag = true;
                    break;
                }
            }
            if (!flag) isTarget[i] = true;
        }

        vll tempG[m];
        for (int i = 0; i < m; i++) {
            if (inAns[i]) continue;

            for (int j = 0; j < m; j++) {
                if (inAns[j] && edges[j].c == edges[i].c) {
                    tempG[i].push_back(j);
                }
            }

            for (auto j : cycles[i]) {
                tempG[j].push_back(i);
            }
        }

        ll bst = -1;
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            if (isTarget[u]) {
                bst = u;
                break;
            }
            for (auto v : tempG[u]) {
                if (vis[v]) continue;

                vis[v] = true;
                anc[v] = u;
                q.push(v);
            }
        }

        if (bst == -1) {
            cout << "-1\n";
            return 0;
        }

        ll cur = bst;
        while (cur != -1) {
            inAns[cur] = !inAns[cur];
            cur = anc[cur];
        }
        
        sz++;
    }

    for (int i = 0; i < m; i++) {
        if (inAns[i]) cout << i + 1 << " ";
    }
    cout << "\n";
}
