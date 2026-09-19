// ICPC GPMX 2026 Repechaje - D "Disco Elysium"
// https://codeforces.com/gym/106710/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, k;
    cin >> n >> k;
    vll A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    ll tot = 0;
    vector<bool> vis(n + 1, false);
    vll B;
    for (int i = 0; i < n; i++) {
        if (A[i] > n || vis[A[i]]) tot++;
        else {
            vis[A[i]] = true;
            B.push_back(A[i]);
        }
    }

    ll ans = 0;
    while (vis[ans]) ans++;
    for (int i = 0; i < tot && k > 0; i++) {
        vis[ans] = true;
        k--;
        while (vis[ans]) ans++;
    }

    sort(B.begin(), B.end());
    for (int i = ll(B.size()) - 1; i >= 0 && k > 0; i--) {
        if (B[i] < ans) break;
        
        vis[B[i]] = false;
        vis[ans] = true;
        k--;
        while (vis[ans]) ans++;
    }

    cout << ans << "\n";
}
