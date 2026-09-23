// ICPC CODEFEM 2026 - L "Coding in Stitches"
// https://codeforces.com/gym/106718/problem/L

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll INF = 1e18;
const vector<string> patterns = {"pgr", "byyb", "wwgyw", "bwwbwb", "prpb", "prrb", "rrggr", "pywb", "vpggpv", "gpbrywvpg"};
const vll beauty = {3, 5, 7, 8, 10, 12, 14, 17, 20, 25};

pair<vll, vector<string>> parse(string s) {
    ll n = s.size();
    vll offset;
    vector<string> ret;

    for (int l = 0; l < n; l++) {
        if (s[l] == ' ') continue;

        ll r = l;
        while (r < n && s[r] != ' ') r++;

        ret.push_back(s.substr(l, r - l));
        offset.push_back(l);
        l = r;
    }

    return {offset, ret};
}

ll get_distance(string s, string t) {
    if (s.size() != t.size()) return INF;

    ll n = s.size(), ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] != t[i]) ans++;
    }
    
    return ans;
}
ll get_different(string s, string t) {
    ll n = s.size();
    for (int i = 0; i < n; i++) {
        if (s[i] != t[i]) return i;
    }
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    string b; ll x;
    getline(cin, b);
    cin >> x;
    auto [offset, A] = parse(b);

    vll pos, val;
    for (int i = 0; i < (ll)A.size(); i++) {
        string s = A[i];

        bool flag = false;
        for (auto p : patterns) {
            if (s == p) flag = true;
        }
        if (flag) continue;

        ll id = -1;
        for (int i = 0; i < ll(patterns.size()); i++) {
            ll dis = get_distance(s, patterns[i]);
            if (dis == 1) id = i;
        }
        if (id == -1) continue;

        ll id_pos = get_different(s, patterns[id]);
        pos.push_back(offset[i] + id_pos);
        val.push_back(beauty[id]);
    }

    ll n = pos.size();
    vll dp(n + 1, 0);
    for (int r = 1, l = 1; r <= n; r++) {
        while (l < r && pos[r - 1] - pos[l - 1] >= x) l++;

        dp[r] = max(dp[r - 1], dp[l - 1] + val[r - 1]);
    }

    cout << dp[n] << "\n";
}
