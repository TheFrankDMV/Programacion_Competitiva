// AtCoder ABC 475 - G "Has Many Divisors"
// https://atcoder.jp/contests/abc475/tasks/abc475_g

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll LIM = 100;

vll primes;

void setup() {
    vector<bool> vis(LIM, false);
    for (int i = 2; i < LIM; i++) {
        if (vis[i]) continue;
        primes.push_back(i);
        for (int j = i; j < LIM; j += i) vis[j] = true;
    }
}

ll n, d, bstDivs, bstVal;

void update_best(ll val, ll divs) {
    if (val % d == 0) return;
    if (divs > bstDivs) {
        bstDivs = divs;
        bstVal = val;
    } else if (divs == bstDivs) {
        bstVal = min(bstVal, val);
    }
}

void dfs(ll id, ll limit, ll curVal, ll curDivs, ll k, ll limit_k) {
    update_best(curVal, curDivs);
    if (id >= ll(primes.size())) return;

    ll p = primes[id], pot = 1;
    if (id == k) {
        for (int i = 0; i <= min(limit, limit_k); i++) {
            if (n / p < pot) break;
            
            if (i != 0) pot *= p;
            if (curVal > n / pot) break;

            dfs(id + 1, limit, curVal * pot, curDivs * (i + 1), k, limit_k);
        }
    } else {
        for (int i = 1; i <= limit; i++) {
            if (n / p < pot) break;

            pot *= p;
            if (curVal > n / pot) break;

            dfs(id + 1, i, curVal * pot, curDivs * (i + 1), k, limit_k);
        }
    }
}

void solve() {
    cin >> n >> d;
    bstDivs = bstVal = 1;

    for (int i = 0; i < ll(primes.size()); i++) {
        ll p = primes[i], vp = 0, tempD = d;
        while (tempD % p == 0) {
            vp++;
            tempD /= p;
        }

        dfs(0, 60, 1, 1, i, vp - 1);
    }

    cout << bstVal << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    setup();

    ll tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}
