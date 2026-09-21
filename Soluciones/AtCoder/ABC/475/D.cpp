// AtCoder ABC 475 - D "Alphametic Prime"
// https://atcoder.jp/contests/abc475/tasks/abc475_d

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll LIM = 1e7;

vll primes;

void setup() {
    vector<bool> vis(LIM, false);
    for (int i = 2; i < LIM; i++) {
        if (vis[i]) continue;
        primes.push_back(i);
        for (int j = i; j < LIM; j += i) {
            vis[j] = true;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    setup();
    
    string s;
    cin >> s;

    for (auto p : primes) {
        string t = to_string(p);
        if (t.size() != s.size()) continue;

        ll n = t.size(); 
        bool flag = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (t[i] == t[j]) {
                    if (s[i] != s[j]) flag = false;
                } else {
                    if (s[i] == s[j]) flag = false;
                }
            }
        }

        if (flag) {
            cout << p << "\n";
            return 0;
        }
    }
    
    cout << "-1\n";
}
