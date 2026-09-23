// AtCoder ABC 472 - G "Cascading Grid"
// https://atcoder.jp/contests/abc472/tasks/abc472_g

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll INF = 1e18;

struct MaxFlow {
    ll n;
    vector<vll> cap, g, g_orig;
    vll from;
    MaxFlow(ll n) : n(n), cap(n, vll(n, 0)), g(n), g_orig(n), from(n) {}

    void add_edge(ll u, ll v, ll c) {
        g[u].push_back(v);
        g[v].push_back(u);
        g_orig[u].push_back(v);
        cap[u][v] += c;
    }

    bool bfs(ll s, ll t) {
        fill(from.begin(), from.end(), -1);
        queue<ll> q;
        q.push(s);
        from[s] = s;
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            for (auto v : g[u]) {
                if (cap[u][v] > 0 && from[v] == -1) {
                    from[v]= u;
                    q.push(v);
                    if (v == t) return true;
                }
            }
        }
        return false;
    }
    ll maxflow(ll s, ll t) {
        ll flow = 0;
        while (bfs(s, t)) {
            ll pushed = INF;
            for (ll cur = t; cur != s; cur = from[cur]) {
                pushed = min(pushed, cap[from[cur]][cur]);
            }
            flow += pushed;
            for (ll cur = t; cur != s; cur = from[cur]) {
                cap[from[cur]][cur] -= pushed;
                cap[cur][from[cur]] += pushed;
            }
        }
        return flow;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    ll curID = 1;
    vector<vll> ID(n, vll(m, -1));
    vll W;
    W.push_back(0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#' || ID[i][j] != -1) continue;

            ll tot = 0, ptr = j;
            while (ptr < m && grid[i][ptr] != '#') {
                ID[i][ptr] = curID;
                tot += (grid[i][ptr] == '+' ? 1 : -1);
                ptr++;
            }

            W.push_back(tot);
            curID++;
        }
    }

    MaxFlow mf(curID + 1); 
    ll sum = 0;
    for (int i = 1; i < curID; i++) {
        if (W[i] > 0) {
            mf.add_edge(0, i, W[i]);
            sum += W[i];
        } else mf.add_edge(i, curID, -W[i]);
    }

    set<pair<ll, ll>> edges;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            ll u = ID[i][j], v = ID[i + 1][j];
            if (u == -1 || v == -1) continue;

            if (!edges.count({v, u})) {
                mf.add_edge(v, u, INF);
                edges.insert({v, u});
            }
        }
    }

    cout << sum - mf.maxflow(0, curID) << "\n"; 
}
