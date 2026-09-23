// ICPC CODEFEM 2026 - K "JajaScript"
// https://codeforces.com/gym/106718/problem/K

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

struct SuffixArray {
    vll sa, lcp; string text;
    SuffixArray(string &s, ll lim = 256) {
        text = s;
        ll n = s.size() + 1, k = 0, a, b;
        vll x(s.begin(), s.end()), y(n), ws(max(n, lim));
        x.push_back(0); 
        sa = lcp = y;
        iota(sa.begin(), sa.end(), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j;
            iota(y.begin(), y.end(), n - j);
            for (int i = 0; i < n; i++) {
                if (sa[i] >= j) y[p++] = sa[i] - j;
            }
            fill(ws.begin(), ws.end(), 0);
            for (int i = 0; i < n; i++) ws[x[i]]++;
            for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
            for (int i = n; i--; ) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1; x[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                a = sa[i - 1];
                b = sa[i];
                x[b] = (y[a] == y[b] && y[a + j] == y[b + j] ? p - 1 : p++);
            }
        }
        for (int i = 0, j; i < n - 1; lcp[x[i++]] = k) {
            for (k && k--, j = sa[x[i] - 1]; s[i + k] == s[j + k]; k++);
        }
    }
    ll count(string pat) {
        if (pat.size() > text.size()) return 0;

        auto L = lower_bound(sa.begin() + 1, sa.end(), pat, [&](int id, string s) {
            return text.substr(id, s.size()) < s;
        });
        auto R = upper_bound(sa.begin() + 1, sa.end(), pat, [&](string s, int id) {
            return s < text.substr(id, s.size());
        });

        return ll(R - L);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    string s;
    cin >> s;
    SuffixArray sa(s);

    ll n, ans1 = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string a, b; ll p;
        cin >> a >> b >> p;
        
        ans1 += sa.count(a) * sa.count(b) * p;
    }

    ll m, ans2 = 0;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string a, b; ll p;
        cin >> a >> b >> p;

        ans2 += sa.count(a) * sa.count(b) * p;
    }

    cout << (ans1 == ans2 ? "Empate" : (ans1 > ans2 ? "Ada" : "Grace")) << "\n";
    cout << max(ans1, ans2) << "\n";
}
