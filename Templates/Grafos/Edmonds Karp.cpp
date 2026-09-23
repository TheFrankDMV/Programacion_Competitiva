/*
 - Descripción: Algoritmo de Edmonds-Karp para encontrar el 
   Flujo Máximo (Max Flow) y el Corte Mínimo (Min Cut) en un grafo dirigido.
 - Utiliza una matriz de adyacencia para las capacidades, por lo que 
   el consumo de memoria es O(N^2).

 - add_edge(u, v, c) agrega una arista de u -> v con capacidad c
 - cuando todo el grafo esta agregado se puede usar maxflow(s, t)
 - donde s = source (fuente), t = sink (sumidero), y calculara el flujo máximo.

 - mincut() devuelve las aristas originales que conforman el corte mínimo. 
   Debe llamarse estrictamente DESPUÉS de haber ejecutado maxflow(s, t).

 - Tiempo: O(N * M^2) en el peor de los casos.
*/

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
                    from[v] = u;
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

    vector<pair<ll, ll>> mincut() {
        vector<pair<ll, ll>> cut;
        for (int u = 0; u < n; u++) {
            if (from[u] == -1) continue;
            for (auto v : g_orig[u]) {
                if (from[v] == -1) cut.push_back({u, v});
            }
        }
        return cut;
    }
};
