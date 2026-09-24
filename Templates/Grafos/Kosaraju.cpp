/*
 - Descripción: Algoritmo de Kosaraju para comprimir 
   un grafo dirigido en componentes fuertemente conexos (SCC).
 - Construye el grafo condensado (DAG) de SCC sin aristas duplicadas.

 - add_edge(u, v) agrega la arista dirigida u -> v
 - cuando todo el grafo esta agregado se puede usar build()
   para construir el grafo condensado.
   
 - Los nodos devueltos estan en ORDEN TOPOLÓGICO, osea si existe 
   una arista u -> v en el DAG, entonces scc_ID[u] < scc_ID[v].
 - cnt_comps guarda el número total de componentes fuertemente conexas.
 - scc_nodes[i] guarda todos los nodos originales pertenecientes a la componente i.
 - dag[i] lista de adyacencia del DAG condensado.
 
 - Tiempo: O(N + M) si no se usa la eliminacion de aristas duplicadas.
*/

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
