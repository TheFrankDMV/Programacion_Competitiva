// AtCoder ABC 475 - E "Quiz Competition: Qualifiers"
// https://atcoder.jp/contests/abc475/tasks/abc475_e

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

struct Trie {
    ll sz;
    Trie* childs[2];

    Trie() {
        sz = 0;
        childs[0] = childs[1] = nullptr;
    }
};

ll get_sz(Trie* u) {
    return (u ? u->sz : 0);
}

void add(Trie* u, ll delta, ll depth, vll& s) {
    if (depth == ll(s.size())) {
        u->sz += delta;
        return;
    }
    
    if (!u->childs[s[depth]]) {
        u->childs[s[depth]] = new Trie();
    }

    add(u->childs[s[depth]], delta, depth + 1, s);
    u->sz = get_sz(u->childs[0]) + get_sz(u->childs[1]);
}

ll m;

bool dfs(Trie* u, ll winners, ll depth, vll& s) {
    if (depth == ll(s.size())) return false;

    if (winners + get_sz(u->childs[1]) <= m) {
        if (s[depth] == 1) return true;
        winners += get_sz(u->childs[1]);
        return dfs(u->childs[0], winners, depth + 1, s);
    } else {
        if (s[depth] == 0) return false;
        return dfs(u->childs[1], winners, depth + 1, s);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, k; string t;
    cin >> n >> m >> k >> t;
    vector<vll> s(n, vll(k));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            char c;
            cin >> c;
            s[i][j] = (c == t[j] ? 1 : 0);
        }
    }

    Trie* root = new Trie();
    for (int i = 0; i < n; i++) {
        add(root, 1, 0, s[i]);
    }

    ll q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        
        add(root, -1, 0, s[a]);
        s[a][b] ^= 1;
        add(root, 1, 0, s[a]);

        bool ans = dfs(root, 0, 0, s[a]);
        cout << (ans ? "Yes" : "No") << "\n"; 
    }
}
